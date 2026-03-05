
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
#include "stm32n6xx_hal.h"
#include "tcsglobal/asg_evo.h"
#include "Common/Inc/Test/perf_test.h"
#include "Common/Inc/Init/app_threadx.h"
#include "Common/Inc/Init/start_screen_lcd.h"
#include "AsgAssert/AsgAssert.h"

/* calculation of pi follows
600Mhz Debug
PID: HAL_TICKS: 265 // pi double
PIN: HAL_TICKS: 254 // pi integer

600Mhz Release
PID: HAL_TICKS: 195 // pi double
PIN: HAL_TICKS: 153 // pi integer

800Mhz Debug
PID: HAL_TICKS:199  // pi double
PIN: HAL_TICKS:190  // pi integer

800Mhz Release
PID: HAL_TICKS: 146  // pi double
PIN: HAL_TICKS: 114  // pi integer
*/

#define PERF_600_DEBUG_PID		265
#define PERF_600_DEBUG_PIN		254

#define PERF_600_RELEASE_PID	195
#define PERF_600_RELEASE_PIN	153

#define PERF_800_DEBUG_PID		199
#define PERF_800_DEBUG_PIN		190

#define PERF_800_RELEASE_PID	146
#define PERF_800_RELEASE_PIN	114

#define SCALE 1000000ULL   // 6 Nachkommastellen

#define RUNS_DOUBLE		1500000
#define RUNS_INTEGER	360000

static uint64_t atan_inv_uint(uint32_t inv, uint32_t terms)
{
    // berechnet atan(1/inv) * SCALE als uint64
    // arctan(z) = z - z^3/3 + z^5/5 - ...
    // z = 1/inv

    uint64_t z = SCALE / inv;           // z in fixed point
    uint64_t z2 = (z * z) / SCALE;      // z^2 in fixed point

    uint64_t term = z;
    int sign = 1;
    uint64_t sum = 0;

    for (uint32_t k = 1; k <= (2 * terms - 1); k += 2)
    {
        uint64_t add = term / k;

        if (sign > 0) sum += add;
        else          sum -= add;

        // term *= z^2  (für nächsten ungeraden Exponenten)
        term = (term * z2) / SCALE;
        sign = -sign;
    }

    return sum;
}

uint32_t pi_uint32_scaled(uint32_t terms)
{
    uint64_t a = atan_inv_uint(5, terms);
    uint64_t b = atan_inv_uint(239, terms);

    // pi = 16*a - 4*b
    uint64_t pi_scaled = 16ULL * a - 4ULL * b;

    return (uint32_t)pi_scaled; // passt locker in uint32 bei SCALE=1e6
}


/* Private user code ---------------------------------------------------------*/
void perf_info_cyccnt_enable(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void perf_info_cyccnt_disable(void)
{
    CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
}


uint32_t perf_info_cyccnt_run(uint32_t cnt)
{
	uint32_t cnt_end;

	cnt_end = DWT->CYCCNT;
	return cnt_end;
}

#define PERF_M_PI     3.14159265358979
#define PERF_M_PIf    3.14159265358979f
#define PERF_M_PI_eps 1.0e-5

double pi_leibniz_double(uint32_t n)
{
    double sum = 0.0;
    for (uint32_t k = 0; k < n; k++)
    {
        double term = 1.0 / (2.0 * (double)k + 1.0);
        if (k & 1) term = -term;
        sum += term;
    }
    return 4.0 * sum;
}

#define TICK_CHECK_PERIOD		100 // ms
#define CPU_EXPECTED_TICKS		(((STM32N6570_CPU_CLOCK * 1000000) / 1000) * TICK_CHECK_PERIOD)

#if defined(DEBUG)
#if STM32N6570_CPU_CLOCK == 600
#define PERF_EXP_PID			PERF_600_DEBUG_PID
#define PERF_EXP_PIN			PERF_600_DEBUG_PIN
#endif
#if STM32N6570_CPU_CLOCK == 800
#define PERF_EXP_PID			PERF_800_DEBUG_PID
#define PERF_EXP_PIN			PERF_800_DEBUG_PIN
#endif
#else
#if STM32N6570_CPU_CLOCK == 600
#define PERF_EXP_PID			PERF_600_RELEASE_PID
#define PERF_EXP_PIN			PERF_600_RELEASE_PIN
#endif
#if STM32N6570_CPU_CLOCK == 800
#define PERF_EXP_PID			PERF_800_RELEASE_PID
#define PERF_EXP_PIN			PERF_800_RELEASE_PIN
#endif
#endif

/* define tolerance +/- 5% */
#define PERF_EXP_PID_MIN		((PERF_EXP_PID * 95) / 100)
#define PERF_EXP_PID_MAX		((PERF_EXP_PID * 105) / 100)
#define PERF_EXP_PIN_MIN		((PERF_EXP_PIN * 95) / 100)
#define PERF_EXP_PIN_MAX		((PERF_EXP_PIN * 105) / 100)
#define CPU_EXPECTED_TICKS_MIN	((CPU_EXPECTED_TICKS / 100) * 95)
#define CPU_EXPECTED_TICKS_MAX	((CPU_EXPECTED_TICKS / 100) * 105)

void fsbl_perf_test(void)
{
	uint32_t cpu_ticks;
	uint32_t hal_tick_start;
	uint32_t hal_tick_end;
	uint32_t hal_ticks;
	bool ok=true;

	perf_info_cyccnt_enable();

	uint32_t start = perf_info_cyccnt_run(0);
	tx_thread_sleep(TX_MS_TO_TICK(TICK_CHECK_PERIOD));
	uint32_t end = perf_info_cyccnt_run(0);
	cpu_ticks = end -start;
	//StartScreenLcd_WriteLine("Clock Checks: 100ms Ticks:  %ld (Exp:%ld)", cpu_ticks, CPU_EXPECTED_TICKS);
	printf("CYCCNT:%ld\n", cpu_ticks);
	if((cpu_ticks < CPU_EXPECTED_TICKS_MIN) || (cpu_ticks > CPU_EXPECTED_TICKS_MAX))
	{
		ok = false;
	}

    hal_tick_start = HAL_GetTick();
    start = DWT->CYCCNT;
    uint32_t pi6 = pi_uint32_scaled(RUNS_INTEGER);
    end = DWT->CYCCNT;
    hal_tick_end = HAL_GetTick();
    hal_ticks = hal_tick_end - hal_tick_start;
    cpu_ticks = end -start;
	if((hal_ticks < PERF_EXP_PIN_MIN) || (hal_ticks > PERF_EXP_PIN_MAX))
	{
		ok = false;
	}

    printf("pi * 1e6 = %lu\r\n", (unsigned long)pi6);
    //StartScreenLcd_WriteLine("PerfCheck PIN: Ticks:  %ld (Exp:%ld)", hal_ticks, PERF_EXP_PIN);
    printf("PIN: HAL_TICKS:%ld CYCCNT:%ld\n", hal_ticks, cpu_ticks);

    hal_tick_start = HAL_GetTick();
    start = DWT->CYCCNT;
    double pid = pi_leibniz_double(RUNS_DOUBLE);
    end = DWT->CYCCNT;
    hal_tick_end = HAL_GetTick();
    hal_ticks = hal_tick_end - hal_tick_start;
    cpu_ticks = end -start;
	if((hal_ticks < PERF_EXP_PID_MIN) || (hal_ticks > PERF_EXP_PID_MAX))
	{
		ok = false;
	}
    //StartScreenLcd_WriteLine("PerfCheck PID: Ticks:  %ld (Exp:%ld)", hal_ticks, PERF_EXP_PID);
    printf("PID: HAL_TICKS:%ld CYCCNT:%ld\n", hal_ticks, cpu_ticks);
    //printf("pi float  = %.7f     pi double = %.15f\n", pif, pid);
    double diff_double = PERF_M_PI - pid;
    if(abs(diff_double) > PERF_M_PI_eps)
    {
    	ok = false;
    }
    printf("PerfCheck PID: Accuracy: pidiff = %.15f\n", diff_double);

    if(ok == true)
    {
    	StartScreenLcd_WriteLine("PerfCheck: All ok!");
    }
    else
    {
    	StartScreenLcd_WriteLine("PerfCheck: !!! ERROR !!!");
    }
    ASG_ASSERT(ok == true);

    //perf_info_cyccnt_disable();
}
