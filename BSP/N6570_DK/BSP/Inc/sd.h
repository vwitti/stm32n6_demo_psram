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
#ifndef __ASGEVO_BSP_N6570_DK_SD_H__
#define __ASGEVO_BSP_N6570_DK_SD_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"

#define SD_DETECT_Pin       GPIO_PIN_12
#define SD_DETECT_GPIO_Port GPION
#define SD_DETECT_EXTI_IRQn EXTI12_IRQn

extern SD_HandleTypeDef hsd2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */
void MX_SDMMC2_SD_Init(void);
void MX_SDMMC2_SD_Pins(void);

#ifdef __cplusplus
}
#endif

#endif /* __ASGEVO_BSP_N6570_DK_SD_H__ */

