/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.h
  * @author  MCD Application Team
  * @brief   ThreadX applicative header file
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
#ifndef __COMMON_INIT_THREADX_H
#define __COMMON_INIT_THREADX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tx_api.h"

/* Private includes ----------------------------------------------------------*/
typedef enum {
	eThreadXPoolId_Kernel=0,		// MUST BE FIRST AND 0
	eThreadXPoolId_NetXDuo,
	eThreadXPoolId_FileX,
	eThreadXPoolId_Last
} teThreadXPoolId;

/* Exported types ------------------------------------------------------------*/
 typedef struct
 {
	 char *   name;				/* Name of pool */
	 uint32_t size;				/* total size of pool */
     uint32_t free;				/* Number of bytes free in pool */
     uint32_t fragments;		/* Number of memory fragments in pool */
     uint32_t susp;				/* Number of threads suspended (not enough memory) */
     TX_THREAD *   tx_thread;	/* Handle of first suspended thread (not enough memory) */
 }  tsThreadXPoolInfo;

/* Exported constants --------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
UINT App_ThreadX_Init(VOID *memory_ptr);
UINT App_ThreadX_GetPoolInfo(teThreadXPoolId id, tsThreadXPoolInfo * info);
void MX_ThreadX_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_INIT_THREADX_H */
