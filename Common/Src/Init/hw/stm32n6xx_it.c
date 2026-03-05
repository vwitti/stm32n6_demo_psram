/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32n6xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include "stm32n6xx_hal.h"
/* Private includes ----------------------------------------------------------*/
#include "Common/Inc/Init/hw/stm32n6xx_it.h"

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/

// --------- NMI_Handler (Non maskable interrupt) handler wrapper (naked) ----------
// Holt den richtigen SP (MSP/PSP) aus EXC_RETURN in LR und ruft C-Funktion.
__attribute__((naked)) void NMI_Handler(void)
{
    __asm volatile(
        "tst lr, #4              \n" // EXC_RETURN bit2: 0=MSP, 1=PSP
        "ite eq                  \n"
        "mrseq r0, msp           \n" // r0 = sp
        "mrsne r0, psp           \n"
        "mov   r1, lr            \n" // r1 = exc_return
        "b nmi_dump_c      \n"
    );
}

// --------- HardFault handler wrapper (naked) ----------
// Holt den richtigen SP (MSP/PSP) aus EXC_RETURN in LR und ruft C-Funktion.
__attribute__((naked)) void HardFault_Handler(void)
{
    __asm volatile(
        "tst lr, #4              \n" // EXC_RETURN bit2: 0=MSP, 1=PSP
        "ite eq                  \n"
        "mrseq r0, msp           \n" // r0 = sp
        "mrsne r0, psp           \n"
        "mov   r1, lr            \n" // r1 = exc_return
        "b hardfault_dump_c      \n"
    );
}

// --------- MemManage_Handler (Memory management fault) wrapper (naked) ----------
// Holt den richtigen SP (MSP/PSP) aus EXC_RETURN in LR und ruft C-Funktion.
__attribute__((naked)) void MemManage_Handler(void)
{
    __asm volatile(
        "tst lr, #4              \n" // EXC_RETURN bit2: 0=MSP, 1=PSP
        "ite eq                  \n"
        "mrseq r0, msp           \n" // r0 = sp
        "mrsne r0, psp           \n"
        "mov   r1, lr            \n" // r1 = exc_return
        "b memmange_dump_c      \n"
    );
}

// --------- BusFault_Handler (Prefetch fault, memory access fault) wrapper (naked) ----------
// Holt den richtigen SP (MSP/PSP) aus EXC_RETURN in LR und ruft C-Funktion.
__attribute__((naked)) void BusFault_Handler(void)
{
    __asm volatile(
        "tst lr, #4              \n" // EXC_RETURN bit2: 0=MSP, 1=PSP
        "ite eq                  \n"
        "mrseq r0, msp           \n" // r0 = sp
        "mrsne r0, psp           \n"
        "mov   r1, lr            \n" // r1 = exc_return
        "b busfault_dump_c      \n"
    );
}

// --------- UsageFault_Handler (Undefined instruction or illegal state) wrapper (naked) ----------
// Holt den richtigen SP (MSP/PSP) aus EXC_RETURN in LR und ruft C-Funktion.
__attribute__((naked)) void UsageFault_Handler(void)
{
    __asm volatile(
        "tst lr, #4              \n" // EXC_RETURN bit2: 0=MSP, 1=PSP
        "ite eq                  \n"
        "mrseq r0, msp           \n" // r0 = sp
        "mrsne r0, psp           \n"
        "mov   r1, lr            \n" // r1 = exc_return
        "b usagefault_dump_c      \n"
    );
}

// --------- SecureFault_Handler (Secure problems) wrapper (naked) ----------
// Holt den richtigen SP (MSP/PSP) aus EXC_RETURN in LR und ruft C-Funktion.
__attribute__((naked)) void SecureFault_Handler(void)
{
    __asm volatile(
        "tst lr, #4              \n" // EXC_RETURN bit2: 0=MSP, 1=PSP
        "ite eq                  \n"
        "mrseq r0, msp           \n" // r0 = sp
        "mrsne r0, psp           \n"
        "mov   r1, lr            \n" // r1 = exc_return
        "b securefault_dump_c      \n"
    );
}



#if 0 // This function is implemented by init code of threadx RTOS

// --------- SVC_Handler (System service call via SWI instruction) wrapper (naked) ----------
// Holt den richtigen SP (MSP/PSP) aus EXC_RETURN in LR und ruft C-Funktion.
__attribute__((naked)) void SVC_Handler(void)
{
    __asm volatile(
        "tst lr, #4              \n" // EXC_RETURN bit2: 0=MSP, 1=PSP
        "ite eq                  \n"
        "mrseq r0, msp           \n" // r0 = sp
        "mrsne r0, psp           \n"
        "mov   r1, lr            \n" // r1 = exc_return
        "b svchandler_dump_c      \n"
    );
}

#endif

// --------- DebugMon_Handler (Debug monitor) wrapper (naked) ----------
// Holt den richtigen SP (MSP/PSP) aus EXC_RETURN in LR und ruft C-Funktion.
__attribute__((naked)) void DebugMon_Handler(void)
{
    __asm volatile(
        "tst lr, #4              \n" // EXC_RETURN bit2: 0=MSP, 1=PSP
        "ite eq                  \n"
        "mrseq r0, msp           \n" // r0 = sp
        "mrsne r0, psp           \n"
        "mov   r1, lr            \n" // r1 = exc_return
        "b debugmon_dump_c      \n"
    );
}

#if 0 // This function is implemented by init code of threadx RTOS

// --------- PendSV_Handler (Pendable request for system service) wrapper (naked) ----------
// Holt den richtigen SP (MSP/PSP) aus EXC_RETURN in LR und ruft C-Funktion.
__attribute__((naked)) void PendSV_Handler(void)
{
    __asm volatile(
        "tst lr, #4              \n" // EXC_RETURN bit2: 0=MSP, 1=PSP
        "ite eq                  \n"
        "mrseq r0, msp           \n" // r0 = sp
        "mrsne r0, psp           \n"
        "mov   r1, lr            \n" // r1 = exc_return
        "b pendsv_handler_dump_c      \n"
    );
}

#endif

void SysTick_Handler(void)
{
  HAL_IncTick();
#if defined(OS_TYPE_THREADX)
  // We first increment the HAL Tick so all STM32 HAL functions works as expected,
  // second step we call the ThreadX Systemtick Handler
  extern void SysTick_Handler_Threadx(void);
  SysTick_Handler_Threadx();
#endif
}

