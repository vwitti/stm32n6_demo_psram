/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __ASGEVO_COMMON_INIT_ERROR_HANDLER_H__
#define __ASGEVO_COMMON_INIT_ERROR_HANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler_NoPrintf(void);
void Error_Handler(char *msg);

#ifdef __cplusplus
}
#endif

#endif /* __ASGEVO_COMMON_INIT_ERROR_HANDLER_H__ */
