/**
  ******************************************************************************
  * @file    main.c
  * @author  GPM Application Team
  * @brief   Main program body through the HAL API
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

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "Common/Inc/Init/error_handler.h"

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(char *msg)
{
  /* User can add his own implementation to report the HAL error return state */
  //HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
  printf("Critical error has occurred\n");
  printf("%s\n", msg);
  printf("----------------------------------\n");
}

/* If we come here there is an error in a very early stage, before Debug Console
 * MX_USART2_UART_Init() has been started */
void Error_Handler_NoPrintf(void)
{
	for(;;);
}
