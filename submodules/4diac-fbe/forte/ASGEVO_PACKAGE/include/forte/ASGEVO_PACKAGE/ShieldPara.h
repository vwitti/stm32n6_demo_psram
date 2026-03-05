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
#ifndef __IOSUBSYSTEM_PARAMETER_SHIELDPARA_H__
#define __IOSUBSYSTEM_PARAMETER_SHIELDPARA_H__

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

#define MAX_NUM_PRESSURE_SENSORS		2
#define SENSOR_LEG_LEFT					0
#define SENSOR_LEG_RIGHT				1
uint16_t Parameter_Shield_Get_LengthRamCylinder();
uint16_t Parameter_Shield_Get_MaxPressureSensor(uint32_t sensor);
uint16_t Parameter_Shield_Get_MaxPressureNSA(uint32_t sensor);

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN VARIABLES */

/* USER CODE END VARIABLES */

#ifdef __cplusplus
}
#endif

#endif /* __IOSUBSYSTEM_PARAMETER_SHIELDPARA_H__ */

