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
#include "SysLayer/HalSystemStop.h"
#include "Common/Inc/Init/hw/stm32n6xx_it.h"
#include "Common/Inc/Init/hw/coredump.h"

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/

void nmi_dump_c(uint32_t* sp, uint32_t exc_return)
{
	coredump_store_values_c(sp, exc_return);

    // Ausgabe
    printf_coredump("!! NMI FAULT !!\n");
    coredump_c_printf();
    HAL_Thread_SystemStop();
}

void hardfault_dump_c(uint32_t* sp, uint32_t exc_return)
{
	coredump_store_values_c(sp, exc_return);
    // Ausgabe
    printf_coredump("!! HARD FAULT !!\n");
    coredump_c_printf();
    HAL_Thread_SystemStop();
}

void memmange_dump_c(uint32_t* sp, uint32_t exc_return)
{
	coredump_store_values_c(sp, exc_return);
    // Ausgabe
    printf_coredump("!! MEM MANAGE FAULT !!\n");
    coredump_c_printf();
    HAL_Thread_SystemStop();
}

void busfault_dump_c(uint32_t* sp, uint32_t exc_return)
{
	coredump_store_values_c(sp, exc_return);
    // Ausgabe
    printf_coredump("!! BUS FAULT !!\n");
    coredump_c_printf();
    HAL_Thread_SystemStop();
}

void usagefault_dump_c(uint32_t* sp, uint32_t exc_return)
{
	coredump_store_values_c(sp, exc_return);
    // Ausgabe
    printf_coredump("!! USAGE FAULT !!\n");
    coredump_c_printf();
    HAL_Thread_SystemStop();
}

void securefault_dump_c(uint32_t* sp, uint32_t exc_return)
{
	coredump_store_values_c(sp, exc_return);
    // Ausgabe
    printf_coredump("!! SECURE FAULT !!\n");
    coredump_c_printf();
    HAL_Thread_SystemStop();
}

void debugmon_dump_c(uint32_t* sp, uint32_t exc_return)
{
	coredump_store_values_c(sp, exc_return);
    // Ausgabe
    printf_coredump("!! DEBUG MON !!\n");
    coredump_c_printf();
    HAL_Thread_SystemStop();
}
