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
#ifndef __COMMON_INIT_SYSMEM_H
#define __COMMON_INIT_SYSMEM_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
 uint32_t _get_used_heap(void);
 uint32_t _get_peak_heap(void);
 void     _dump_heap_info(void);

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_INIT_SYSCALLS_H */
