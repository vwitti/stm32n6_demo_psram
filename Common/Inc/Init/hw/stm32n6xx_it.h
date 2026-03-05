/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32n6xx_it.h
  * @brief   This file contains the headers of the interrupt handlers.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INIT_HW_STM32N6XX_IT__H__
#define __INIT_HW_STM32N6XX_IT__H__

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
#include <stdint.h>
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SecureFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

void nmi_dump_c(uint32_t* sp, uint32_t exc_return);
void hardfault_dump_c(uint32_t* sp, uint32_t exc_return);
void memmange_dump_c(uint32_t* sp, uint32_t exc_return);
void busfault_dump_c(uint32_t* sp, uint32_t exc_return);
void usagefault_dump_c(uint32_t* sp, uint32_t exc_return);
void securefault_dump_c(uint32_t* sp, uint32_t exc_return);
void debugmon_dump_c(uint32_t* sp, uint32_t exc_return);

#ifdef __cplusplus
}
#endif

#endif /* __INIT_HW_STM32N6XX_IT__H__ */
