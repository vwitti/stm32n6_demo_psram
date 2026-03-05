/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32n6xx_hal_msp.c
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* External functions --------------------------------------------------------*/

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /*
  see RM STM32N6570 ch. 13.3 and 13.4
  •VDDIO2: external power supply for 22 I/Os (PO[5:0] and PP[15:0]), independent from
  any other supply
  •VDDIO3: external power supply for 13 I/Os (PN[12:0]), independent from any other
  supply
  •VDDIO4: external power supply for 10 I/Os (PC[1], PC[12:6], and PH[9,2]), independent
  from any other supply
  •VDDIO5: external power supply for six I/Os (PC[0], PC[5:2], and PE[4]), independent
  from any other supply

  VDDIO2InputIndependent I/O supply 2 (PO[5:0] and PP[15:0]), usually for XSPI1M_P1 (XSPI)
  VDDIO3InputIndependent I/O supply 3 (PN[12:0])., usually for XSPI1M_P2 (XSPI)
  VDDIO4InputIndependent I/O supply 4 (PC[1], PC[12:6] and PH[2,9]), usually for eMMC
  VDDIO5InputIndependent I/O supply 5 (PC[0], PC[5:2] and PE[4]), usually for SD-Card.
  */
  HAL_PWREx_EnableVddIO2();
  HAL_PWREx_ConfigVddIORange(PWR_VDDIO2,PWR_VDDIO_RANGE_1V8);

  HAL_PWREx_EnableVddIO3();
  HAL_PWREx_ConfigVddIORange(PWR_VDDIO3,PWR_VDDIO_RANGE_1V8);

  HAL_PWREx_EnableVddIO4();
  HAL_PWREx_ConfigVddIORange(PWR_VDDIO4,PWR_VDDIO_RANGE_3V3);

  HAL_PWREx_EnableVddIO5();
  HAL_PWREx_ConfigVddIORange(PWR_VDDIO3,PWR_VDDIO_RANGE_1V8);

  /* System interrupt init*/

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
  * @brief  DeInitialize the Global MSP.
  * @retval None
  */
void HAL_MspDeInit(void)
{
}
