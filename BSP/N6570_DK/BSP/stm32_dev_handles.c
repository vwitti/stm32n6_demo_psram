/**
  ******************************************************************************
  * @file    stm32_extmem_conf.c
  * @author  GPM Application Team
  * @brief   Header configuration for extmem module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#include "BSP/Inc/usart.h"

#if STM32N6570_SERIAL_CONSOLE == 1
extern UART_HandleTypeDef huart1;
UART_HandleTypeDef * DebugUsartHandle_get(void)
{
	return &huart1;
}
#endif

#if STM32N6570_SERIAL_CONSOLE == 2
extern UART_HandleTypeDef huart2;
UART_HandleTypeDef * DebugUsartHandle_get(void)
{
	return &huart2;
}
#endif
