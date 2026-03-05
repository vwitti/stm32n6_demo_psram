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
#ifndef __COMMON_INIT_SYSCALLS_H
#define __COMMON_INIT_SYSCALLS_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#if PROJECT_OS_FILESYSTEM == 1

/* Middleware Includes */
#include "tx_api.h"
#include "fx_api.h"
UINT filex_newlib_init(void);
#endif // PROJECT_OS_FILESYSTEM
void syscall_HAL_UART_write(uint8_t * data, uint16_t len);
void syscall_HAL_UART_read(uint8_t * data);
int  syscall_close_socket(int fd);

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_INIT_SYSCALLS_H */
