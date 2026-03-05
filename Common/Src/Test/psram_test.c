
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
#include "stm32n6xx_hal.h"
#include "Common/Inc/Test/psram_test.h"
#include "AsgAssert/AsgAssert.h"

#define PSRAM_SIZE		0x2000000 // 32 MB
uint32_t seed_lfsr;

#define LFSR32_MASK 0xD0000001u  // taps 32,31,29,1 (maximal period) :contentReference[oaicite:1]{index=1}

// Liefert nächsten 32-bit Wert; seed/state darf NICHT 0 sein (sonst bleibt LFSR stehen).
static uint32_t lfsr32_next(uint32_t *state)
{
    uint32_t x = *state;
    uint32_t lsb = x & 1u;           // output bit
    x >>= 1;                         // shift
    x ^= (0u - lsb) & LFSR32_MASK;    // wenn lsb==1 -> XOR Maske, sonst 0
    *state = x;
    return x;
}

static inline void mem_barrier(void){ __asm volatile("" ::: "memory"); }

int mem_fill_verify_u32(volatile uint32_t* base, size_t bytes, uint32_t seed)
{
    size_t words = bytes / 4;

    seed_lfsr=seed;
    for (size_t i = 0; i < words; i++) base[i] = lfsr32_next(&seed_lfsr); //pattern;
    mem_barrier();
    seed_lfsr=seed;
    for (size_t i = 0; i < words; i++) {
        if (base[i] != /*pattern*/lfsr32_next(&seed_lfsr))
        {
        	return (int)i; // Fehlerindex
        }
    }
    return -1; // ok
}

int pseudo_rand_pattern(uint32_t seed)
{
    uint32_t s = seed; // beliebiger non-zero Seed (deterministisch)
    for (int i = 0; i < 20; ++i) {
        uint32_t r = lfsr32_next(&s);
        printf("%08lX\n", r);
    }
    return 0;
}

bool fsbl_psram_test(void)
{
	int res;
	volatile uint32_t* base = (volatile uint32_t*) XSPI1_BASE;

	uint32_t clk_xspi;

	// XSPI2 -- FLASH
	clk_xspi = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI2);
	printf("clk_xspi1:Flash: clk=%ld Hz\n", clk_xspi);
	ASG_ASSERT(clk_xspi == 200000000);

	// XSPI1 -- PSRAM
	clk_xspi = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI1);
	printf("clk_xspi1:PSRAM: clk=%ld Hz\n", clk_xspi);
	ASG_ASSERT(clk_xspi == 200000000);

	//pseudo_rand_pattern(0x12345678);

	//res = mem_fill_verify_u32(base, 20, 0x12345678); // ok
	//res = mem_fill_verify_u32(base, 200, 0x12345678); // ok
	//res = mem_fill_verify_u32(base, 2000, 0x12345678); // ok
	//res = mem_fill_verify_u32(base, 20000, 0x12345678); //ok
	//res = mem_fill_verify_u32(base, 200000, 0x12345678); //ok
	//res = mem_fill_verify_u32(base, 2000000, 0x12345678); //ok
	res = mem_fill_verify_u32(base, PSRAM_SIZE, 0x12345678); //ok
	printf("demo_psram_test = %d\n", res);
	if(res == -1)
	{
		return true;
	}
	return false;
}

bool fsbl_psram_test_forever(void)
{
	int res;
	volatile uint32_t* base = (volatile uint32_t*) XSPI1_BASE;

	uint32_t clk_xspi;
	size_t size;
	uint32_t seed;
	uint32_t run, good, bad;

	// XSPI2 -- FLASH
	clk_xspi = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI2);
	printf("clk_xspi1:Flash: clk=%ld Hz\n", clk_xspi);
	ASG_ASSERT(clk_xspi == 200000000);

	// XSPI1 -- PSRAM
	clk_xspi = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI1);
	printf("clk_xspi1:PSRAM: clk=%ld Hz\n", clk_xspi);
	ASG_ASSERT(clk_xspi == 200000000);

	run=0;
	good=0;
	bad=0;

	for(;;)
	{
		seed = HAL_GetTick() * HAL_GetTick();
		pseudo_rand_pattern(seed);

		size = PSRAM_SIZE;
		res = mem_fill_verify_u32(base, size, seed); //ok
		if(res == -1)
		{
			good++;
			//return true;
		}
		else
		{
			bad++;
		}
		run++;
		printf("RUN: %ld GOOD=%ld, BAD=%ld SEED=%08lX\n", run, good, bad, seed);
	}
}
