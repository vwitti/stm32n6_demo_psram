/*
 * HalThread.c
 *
 *  Created on: Nov 6, 2025
 *      Author: vw
 */

// Enable defined to trace module (must be above of Syslog/Syslog.h)
//#define TRACE_MODULE

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "stm32n6xx_hal.h"
#if defined(OS_TYPE_THREADX)
#include "threadx/common/inc/tx_api.h"
#endif
#include "SysLayer/HalSystemStop.h"
#include "Common/Inc/Init/hw/coredump.h"
#include "Common/Inc/Init/syscalls.h"

// --------- Datenstruktur für Post-Mortem ----------
typedef struct {
    // gestackter Exception Frame (immer vorhanden)
    uint32_t r0, r1, r2, r3, r12, lr, pc, xpsr;

    // weitere Core-Register (soweit sinnvoll lesbar)
    uint32_t msp, psp, primask, basepri, faultmask, control;

    // Fault-Status (SCB)
    uint32_t cfsr, hfsr, dfsr, afsr, mmfar, bfar, shcsr;

    // Optional: wenn vorhanden/gewünscht (Cortex-M55 hat FP optional; M55 hat auch PSPLIM/MSPLIM)
    uint32_t msplim, psplim;

    // Hinweis, welcher Stack aktiv war
    uint32_t using_psp;

    uint32_t sp;
} exception_dump_t;

volatile exception_dump_t g_exc_dump;

// --------- kleine Helpers ----------
static inline uintptr_t umin(uintptr_t a, uintptr_t b) { return (a < b) ? a : b; }
static inline uintptr_t umax(uintptr_t a, uintptr_t b) { return (a > b) ? a : b; }

static inline int is_aligned4(uintptr_t a) { return (a & 0x3u) == 0; }

// Heuristik: Thumb return address hat Bit0=1, wir vergleichen aber PC ohne Bit0 in Code-Range
static inline int looks_like_code_ptr(uint32_t raw_addr)
{
    // viele Return-Addresses sind Thumb: bit0=1
    if ((raw_addr & 1u) == 0u) return 0;
    raw_addr &= ~1u;

    // Code range bestimmen
    extern uint8_t * _stextcode[];
    extern uint8_t * _etextcode[];
    uint32_t addr_start = (uint32_t) _stextcode;
    uint32_t addr_end   = (uint32_t) _etextcode;

    return (raw_addr >= addr_start) && (raw_addr < addr_end);
}

//#################################################

// Normal printf might call _sbrk, if heap is corrupted no printf will work during exceptions
// so redirect to vsnprintf and write directly to interface
void printf_coredump(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	// delegate to channel print with default channel
	char tmp[80];
	int n = vsnprintf(tmp, sizeof(tmp), fmt, ap);
	va_end(ap);
	if (n < 0) return;
	syscall_HAL_UART_write((uint8_t *)tmp, n);
	syscall_HAL_UART_write((uint8_t *)"\r", 1);
}

static void dump_fault_registers(const exception_dump_t* d)
{
	printf_coredump("\n=== EXCEPTION DUMP ===\n");
	printf_coredump("Stack used : %s\n", d->using_psp ? "PSP" : "MSP");

	printf_coredump("\n-- Stacked frame --\n");
    printf_coredump("R0  = 0x%08lX\n", (unsigned long)d->r0);
    printf_coredump("R1  = 0x%08lX\n", (unsigned long)d->r1);
    printf_coredump("R2  = 0x%08lX\n", (unsigned long)d->r2);
    printf_coredump("R3  = 0x%08lX\n", (unsigned long)d->r3);
    printf_coredump("R12 = 0x%08lX\n", (unsigned long)d->r12);
    printf_coredump("LR  = 0x%08lX\n", (unsigned long)d->lr);
    printf_coredump("PC  = 0x%08lX\n", (unsigned long)d->pc);
    printf_coredump("xPSR= 0x%08lX\n", (unsigned long)d->xpsr);

    printf_coredump("\n-- Core regs --\n");
    printf_coredump("MSP     = 0x%08lX\n", (unsigned long)d->msp);
    printf_coredump("PSP     = 0x%08lX\n", (unsigned long)d->psp);
    printf_coredump("MSPLIM  = 0x%08lX\n", (unsigned long)d->msplim);
    printf_coredump("PSPLIM  = 0x%08lX\n", (unsigned long)d->psplim);
    printf_coredump("PRIMASK = 0x%08lX\n", (unsigned long)d->primask);
    printf_coredump("BASEPRI = 0x%08lX\n", (unsigned long)d->basepri);
    printf_coredump("FAULTMASK=0x%08lX\n", (unsigned long)d->faultmask);
    printf_coredump("CONTROL = 0x%08lX\n", (unsigned long)d->control);

    printf_coredump("\n-- SCB fault status --\n");
    printf_coredump("SHCSR = 0x%08lX\n", (unsigned long)d->shcsr);
    printf_coredump("CFSR  = 0x%08lX\n", (unsigned long)d->cfsr);
    printf_coredump("HFSR  = 0x%08lX\n", (unsigned long)d->hfsr);
    printf_coredump("DFSR  = 0x%08lX\n", (unsigned long)d->dfsr);
    printf_coredump("AFSR  = 0x%08lX\n", (unsigned long)d->afsr);
    printf_coredump("MMFAR = 0x%08lX\n", (unsigned long)d->mmfar);
    printf_coredump("BFAR  = 0x%08lX\n", (unsigned long)d->bfar);

    //printf_coredump("\nCode range: [0x%08lX .. 0x%08lX)\n",
    //       (unsigned long)CODE_START, (unsigned long)CODE_END);
}

// Stack-Scan: druckt alle Wörter, die wie Return Address aussehen.
// scan_words: Anzahl 32-bit Wörter ab sp_start (begrenzt!)
static void dump_return_addresses_from_stack(uint32_t* sp_start, uint32_t scan_words)
{
#if defined(OS_TYPE_THREADX)
	uintptr_t stack_lo;
	uintptr_t stack_hi;
	uintptr_t stack_curr;

	if(g_exc_dump.using_psp == 1)
	{
		printf_coredump("USING PSP Stack pointer\n");
		TX_THREAD *current = tx_thread_identify();
		if(current == NULL)
		{
			printf_coredump("Invalid ThreadX pointer\n");
			return;

			//printf_coredump("STACK AREA: stack_lo=%08X stack_hi=%08X\n", stack_lo, stack_hi);
		}
		//return;
		stack_lo = (uintptr_t) current->tx_thread_stack_start;
		stack_hi = (uintptr_t) current->tx_thread_stack_end;
		stack_curr = (uintptr_t) current->tx_thread_stack_ptr;
	}
	else
	{
		//uintptr_t stack_lo = (uintptr_t)&__StackLimit;
		//uintptr_t stack_hi = (uintptr_t)&__StackTop;

		extern uint8_t * _sstack[];
		extern uint8_t * _estack[];
		stack_lo = (uintptr_t)_sstack;
		stack_hi = (uintptr_t)_estack;
		stack_curr= (uintptr_t)0;
		//uint32_t addr_start = (uint32_t) _stextcode;
		//uint32_t addr_end   = (uint32_t) _etextcode;
	}
	printf_coredump("STACK AREA: stack_lo=%08X stack_hi=%08X stack_curr=%08X\n", stack_lo, stack_hi,stack_curr);
    // Clamp Start
    uintptr_t sp = (uintptr_t)sp_start;
    if (sp < stack_lo) sp = stack_lo;
    if (sp > stack_hi) sp = stack_hi;

    if (!is_aligned4(sp)) sp = (sp + 3u) & ~3u;

    uint32_t* p = (uint32_t*)sp;
    uint32_t* end = (uint32_t*)umin((uintptr_t)p + (uintptr_t)scan_words * 4u, stack_hi);

    printf_coredump("\n-- Stack return-address scan (heuristic) --\n");
    printf_coredump("Scanning SP=0x%08lX .. 0x%08lX (%lu words)\n",
           (unsigned long)(uintptr_t)p,
           (unsigned long)(uintptr_t)end,
           (unsigned long)((uintptr_t)end - (uintptr_t)p)/4u);

    uint32_t found = 0;
    for (; p < end; ++p) {
        uint32_t v = *p;
        if (looks_like_code_ptr(v)) {
            // Print raw (with Thumb bit) and normalized
            printf_coredump("  [SP+0x%04lX] RA=0x%08lX (pc=0x%08lX)\n",
                   (unsigned long)((uintptr_t)p - sp),
                   (unsigned long)v,
                   (unsigned long)(v & ~1u));
            found++;
        }
    }
    printf_coredump("Found %lu potential return addresses.\n", (unsigned long)found);
#endif
}

void coredump_c_printf()
{

    // Ausgabe
    dump_fault_registers((const exception_dump_t*)&g_exc_dump);

    // Stack: wir scannen den Stack, der beim Fault aktiv war (sp)
    // Scan-Länge: z.B. 512 words = 2048 Bytes (anpassen!)
    dump_return_addresses_from_stack((uint32_t *)g_exc_dump.sp, 512);

    // Hängen bleiben
    printf_coredump("\nSystem halted.\n");
    HAL_Thread_SystemStop();
}

void coredump_store_values_c(uint32_t* sp, uint32_t exc_return)
{
    // Stackframe layout: r0,r1,r2,r3,r12,lr,pc,xpsr
    g_exc_dump.r0   = sp[0];
    g_exc_dump.r1   = sp[1];
    g_exc_dump.r2   = sp[2];
    g_exc_dump.r3   = sp[3];
    g_exc_dump.r12  = sp[4];
    g_exc_dump.lr   = sp[5];
    g_exc_dump.pc   = sp[6];
    g_exc_dump.xpsr = sp[7];

    g_exc_dump.using_psp = (exc_return & 0x4u) ? 1u : 0u;

    // Core regs
    g_exc_dump.msp      = __get_MSP();
    g_exc_dump.psp      = __get_PSP();
    g_exc_dump.primask  = __get_PRIMASK();
    g_exc_dump.basepri  = __get_BASEPRI();
    g_exc_dump.faultmask= __get_FAULTMASK();
    g_exc_dump.control  = __get_CONTROL();

#if defined(__ARM_ARCH_8M_MAIN__) || defined(__ARM_ARCH_8M_BASE__)
    // MSPLIM/PSPLIM exist on Armv8-M
    g_exc_dump.msplim = __get_MSPLIM();
    g_exc_dump.psplim = __get_PSPLIM();
#else
    g_exc_dump.msplim = 0;
    g_exc_dump.psplim = 0;
#endif

    // SCB fault regs
    g_exc_dump.shcsr = SCB->SHCSR;
    g_exc_dump.cfsr  = SCB->CFSR;
    g_exc_dump.hfsr  = SCB->HFSR;
    g_exc_dump.dfsr  = SCB->DFSR;
    g_exc_dump.afsr  = SCB->AFSR;
    g_exc_dump.mmfar = SCB->MMFAR;
    g_exc_dump.bfar  = SCB->BFAR;

    g_exc_dump.sp    = (uint32_t) sp;

}



