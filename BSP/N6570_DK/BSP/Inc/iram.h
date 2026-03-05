/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __ASGEVO_BSP_N6570_DK_IRAM_H__
#define __ASGEVO_BSP_N6570_DK_IRAM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"


// Handling of internal RAMs
void Enable_NPU_RAM_ForCore(void);
void Enable_AXICACHE_RAM_ForCore(void);
void Enable_VENCRAM_ForCore(void);

#ifdef __cplusplus
}
#endif

#endif /* __ASGEVO_BSP_N6570_DK_IRAM_H__ */

