
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
#ifndef BSP_N6570_DK_FSBL_MIDDLEWARE_CONFIG_H
#define BSP_N6570_DK_FSBL_MIDDLEWARE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define USE_STATIC_ALLOCATION                    1			/* Using static memory allocation via threadX Byte memory pools */

#define TX_APP_MEM_POOL_SIZE                     20 * 1024	/* Total memory for Threadx Kernel */

#define FX_APP_MEM_POOL_SIZE                     10 * 1024	/* Total memory for FileX Stack */

#define NX_APP_MEM_POOL_SIZE                     50 * 1024	/* Total memory for NetxDuo Stack */

#define NX_APP_PACKET_NUM_PACKETS				 20			/* Number of packets in default pool */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* BSP_N6570_DK_FSBL_MIDDLEWARE_CONFIG_H */
