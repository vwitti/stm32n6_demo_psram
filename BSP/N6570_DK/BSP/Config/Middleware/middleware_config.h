
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_azure_rtos_config.h
  * @author  MCD Application Team
  * @brief   app_azure_rtos config header file
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
#ifndef BSP_N6570_DK_CONFIG_MIDDLEWARE_CONFIG_H
#define BSP_N6570_DK_CONFIG_MIDDLEWARE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#if defined(PROG_TYPE_FSBL)
	#include "BSP/FSBL/middleware_config.h"
#endif

#if defined(PROG_TYPE_APPLI)
	#include "BSP/APPLI/middleware_config.h"
#endif

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* BSP_N6570_DK_CONFIG_MIDDLEWARE_CONFIG_H */
