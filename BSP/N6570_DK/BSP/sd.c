/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
/* Includes ------------------------------------------------------------------*/
#include "BSP/Inc/sd.h"
#include "Common/Inc/Init/error_handler.h"

#define SD_D0_Pin GPIO_PIN_4
#define SD_D0_GPIO_Port GPIOC
#define SD_D1_Pin GPIO_PIN_5
#define SD_D1_GPIO_Port GPIOC
#define SD_D2_Pin GPIO_PIN_0
#define SD_D2_GPIO_Port GPIOC
#define SD_CK_Pin GPIO_PIN_2
#define SD_CK_GPIO_Port GPIOC
#define SD_D3_Pin GPIO_PIN_4
#define SD_D3_GPIO_Port GPIOE
#define SD_CMD_Pin GPIO_PIN_3
#define SD_CMD_GPIO_Port GPIOC


SD_HandleTypeDef hsd2;

/**
  * @brief SDMMC2 Initialization Function
  * @param None
  * @retval None
  */
void MX_SDMMC2_SD_Init(void)
{
  /* USER CODE END SDMMC2_Init 1 */
  hsd2.Instance = SDMMC2;
  hsd2.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd2.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd2.Init.BusWide = SDMMC_BUS_WIDE_4B;
  hsd2.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd2.Init.ClockDiv = 0;
  if (HAL_SD_Init(&hsd2) != HAL_OK)
  {
	  Error_Handler("MX_SDMMC2_SD_Init: failed!");
  }

}

void MX_SDMMC2_SD_Pins(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPION_CLK_ENABLE();

	/*Configure GPIO pin : SD_DETECT_Pin */
	GPIO_InitStruct.Pin = SD_DETECT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(SD_DETECT_GPIO_Port, &GPIO_InitStruct);

	/*Configure the EXTI line attribute */
	HAL_EXTI_ConfigLineAttributes(EXTI_LINE_12, EXTI_LINE_SEC);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI12_IRQn, 14, 0);
	HAL_NVIC_EnableIRQ(EXTI12_IRQn);
}

/**
* @brief SD MSP Initialization
* This function configures the hardware resources used in this example
* @param hsd: SD handle pointer
* @retval None
*/
void HAL_SD_MspInit(SD_HandleTypeDef* hsd)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
	  if(hsd->Instance==SDMMC2)
	  {
	    /* USER CODE BEGIN SDMMC2_MspInit 0 */

	    /* USER CODE END SDMMC2_MspInit 0 */

	  /** Initializes the peripherals clock
	  */
	    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDMMC2;
	    PeriphClkInitStruct.Sdmmc2ClockSelection = RCC_SDMMC2CLKSOURCE_HCLK;
	    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	    {
	      Error_Handler("HAL_SD_MspInit: cant init clock");
	    }

	    /* Peripheral clock enable */
	    __HAL_RCC_SDMMC2_CLK_ENABLE();

	    __HAL_RCC_GPIOC_CLK_ENABLE();
	    __HAL_RCC_GPIOE_CLK_ENABLE();
	    /**SDMMC2 GPIO Configuration
	    PC4     ------> SDMMC2_D0
	    PC5     ------> SDMMC2_D1
	    PC0     ------> SDMMC2_D2
	    PC2     ------> SDMMC2_CK
	    PE4     ------> SDMMC2_D3
	    PC3     ------> SDMMC2_CMD
	    */
	    GPIO_InitStruct.Pin = SD_D0_Pin|SD_D1_Pin|SD_D2_Pin|SD_CMD_Pin;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	    GPIO_InitStruct.Alternate = GPIO_AF11_SDMMC2;
	    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = SD_CK_Pin;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF11_SDMMC2;
	    HAL_GPIO_Init(SD_CK_GPIO_Port, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = SD_D3_Pin;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	    GPIO_InitStruct.Alternate = GPIO_AF11_SDMMC2;
	    HAL_GPIO_Init(SD_D3_GPIO_Port, &GPIO_InitStruct);

	    /* USER CODE BEGIN SDMMC2_MspInit 1 */

	    /* SDMMC2 interrupt Init */
	    HAL_NVIC_SetPriority(SDMMC2_IRQn, 5, 0);
	    HAL_NVIC_EnableIRQ(SDMMC2_IRQn);
	    /* USER CODE BEGIN SDMMC2_MspInit 1 */

	  }
}

/**
  * @brief  DeInitializes the SD MSP.
  * @param  hsd  SD handle
  * @retval None
  */
void HAL_SD_MspDeInit(SD_HandleTypeDef* hsd)
{
  if(hsd->Instance==SDMMC2)
  {
    /* USER CODE BEGIN SDMMC2_MspDeInit 0 */

    /* USER CODE END SDMMC2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDMMC2_CLK_DISABLE();

    /**SDMMC2 GPIO Configuration
    PC4     ------> SDMMC2_D0
    PC5     ------> SDMMC2_D1
    PC0     ------> SDMMC2_D2
    PC2     ------> SDMMC2_CK
    PE4     ------> SDMMC2_D3
    PC3     ------> SDMMC2_CMD
    */
    HAL_GPIO_DeInit(GPIOC, SD_D0_Pin|SD_D1_Pin|SD_D2_Pin|SD_CK_Pin
                          |SD_CMD_Pin);

    HAL_GPIO_DeInit(SD_D3_GPIO_Port, SD_D3_Pin);

    /* USER CODE BEGIN SDMMC2_MspDeInit 1 */

    /* USER CODE END SDMMC2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
  * @brief This function handles EXTI line12 interrupt.
  */
void EXTI12_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI12_IRQn 0 */

  /* USER CODE END EXTI12_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(SD_DETECT_Pin);
  /* USER CODE BEGIN EXTI12_IRQn 1 */

  /* USER CODE END EXTI12_IRQn 1 */
}

/**
  * @brief This function handles SDMMC2 global interrupt.
  */
void SDMMC2_IRQHandler(void)
{
  /* USER CODE BEGIN SDMMC2_IRQn 0 */

  /* USER CODE END SDMMC2_IRQn 0 */
  HAL_SD_IRQHandler(&hsd2);
  /* USER CODE BEGIN SDMMC2_IRQn 1 */

  /* USER CODE END SDMMC2_IRQn 1 */
}


