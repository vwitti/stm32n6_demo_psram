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
#ifndef __IOSUBSYSTEM_VALVES__H__
#define __IOSUBSYSTEM_VALVES__H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdbool.h"
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

void IoSubSystemValves_Init(void);
void IoSubSystemValves_Modify(void);

bool IoSubSystemValves_GetValve_Lowering();
bool IoSubSystemValves_GetValve_Setting();
bool IoSubSystemValves_GetValve_PullShield();
bool IoSubSystemValves_GetValve_PushShield();
bool IoSubSystemValves_GetValve_PullCreepAdvance();
bool IoSubSystemValves_GetValve_BaseLiftExtend();
bool IoSubSystemValves_GetValve_BaseLiftRetract();
bool IoSubSystemValves_GetValve_StabCylExtend();
bool IoSubSystemValves_GetValve_StabCylRetract();

void IoSubSystemValves_SetValve_Lowering(bool val);
void IoSubSystemValves_SetValve_Setting(bool val);
void IoSubSystemValves_SetValve_PullShield(bool val);
void IoSubSystemValves_SetValve_PushShield(bool val);
void IoSubSystemValves_SetValve_PullCreepAdvance(bool val);
void IoSubSystemValves_SetValve_BaseLiftExtend(bool val);
void IoSubSystemValves_SetValve_BaseLiftRetract(bool val);
void IoSubSystemValves_SetValve_StabCylExtend(bool val);
void IoSubSystemValves_SetValve_StabCylRetract(bool val);


#ifdef __cplusplus
}
#endif

#endif /* __IOSUBSYSTEM_VALVES__H__ */

