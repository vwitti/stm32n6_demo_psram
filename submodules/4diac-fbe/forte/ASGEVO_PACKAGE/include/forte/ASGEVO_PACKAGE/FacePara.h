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
#ifndef __IOSUBSYSTEM_PARAMETER_FACE_PARA_H__
#define __IOSUBSYSTEM_PARAMETER_FACE_PARA_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
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
uint16_t Parameter_Face_Get_DepthOfCut();
uint16_t Parameter_Face_Get_LAS_CreepAdvanceMinTarget();
uint16_t Parameter_Face_Get_LAS_CreepAdvanceWindow();
uint16_t Parameter_Face_Get_LAS_Sensorgesteuert();

void Parameter_Face_Set_DepthOfCut(uint16_t val);
void Parameter_Face_Set_LAS_CreepAdvanceMinTarget(uint16_t val);
void Parameter_Face_Set_LAS_CreepAdvanceWindow(uint16_t val);
void Parameter_Face_Set_LAS_Sensorgesteuert(uint16_t val);

#ifdef __cplusplus
}
#endif

#endif /* __IOSUBSYSTEM_PARAMETER_FACE_PARA_H__ */

