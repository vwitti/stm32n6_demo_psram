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
#ifndef __COMMON_WAIT_FOR_DEBUGGER_H
#define __COMMON_WAIT_FOR_DEBUGGER_H

#include <stdbool.h>

// NOTE: Debugger config is only needed for APPLI, since application is debugger from XSPI flash.
//       FSBL Code is loaded direct into RAM for debugging
#include "DEBUGGER_CONFIG.h"

#ifdef __cplusplus
 extern "C" {
#endif

extern bool sWaitForDebugger;

/* Includes ------------------------------------------------------------------*/
bool wait_for_debugger(bool wait);

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_WAIT_FOR_DEBUGGER_H */
