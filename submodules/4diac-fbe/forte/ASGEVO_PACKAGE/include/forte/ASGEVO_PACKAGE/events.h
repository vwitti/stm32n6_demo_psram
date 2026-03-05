/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : extmem_manager.h
  * @version        : 1.0.0
  * @brief          : Header for external memory manager extmem_manager.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#ifndef __IOSUBSYSTEM_EVENTS__H__
#define __IOSUBSYSTEM_EVENTS__H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdbool.h"
#include "stdint.h"
/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN VARIABLES */

/* USER CODE END VARIABLES */

void IoSubSystemEvents_Init(void);
void IoSubSystemEvents_Modify(void);

bool IoSubSystemEvents_Get_DoLAS();
bool IoSubSystemEvents_Get_DoPUSH();
bool IoSubSystemEvents_Get_LAS_Prewarn();
uint16_t IoSubSystemEvents_Get_LAS_Error();

void IoSubSystemEvents_Set_DoLAS(bool val);
void IoSubSystemEvents_Set_DoPUSH(bool val);
void IoSubSystemEvents_Set_LAS_Prewarn(bool val);
void IoSubSystemEvents_Set_LAS_Error(uint16_t errcode);

#ifdef __cplusplus
}
#endif

#endif /* __IOSUBSYSTEM_EVENTS__H__ */

