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
#include "BSP/Inc/eth.h"
#include "Common/Inc/Init/error_handler.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

ETH_HandleTypeDef heth;

ETH_DMADescTypeDef DMARxDscrTab[ETH_DMA_RX_CH_CNT][ETH_RX_DESC_CNT] __attribute__((section(".RxDecripSection"))); /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef DMATxDscrTab[ETH_DMA_TX_CH_CNT][ETH_TX_DESC_CNT] __attribute__((section(".TxDecripSection")));   /* Ethernet Tx DMA Descriptors */


/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
void MX_ETH_Init(void)
{
  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH1;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE0;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x10;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RGMII_MODE;

  for (int ch = 0; ch < ETH_DMA_CH_CNT; ch++)
  {
    heth.Init.TxDesc[ch] = DMATxDscrTab[ch];
    heth.Init.RxDesc[ch] = DMARxDscrTab[ch];
  }

  heth.Init.RxBuffLen = 1536;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler("MX_ETH_Init: failed!");
  }

  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */
}

/**
* @brief ETH MSP Initialization
* This function configures the hardware resources used in this example
* @param heth: ETH handle pointer
* @retval None
*/
void HAL_ETH_MspInit(ETH_HandleTypeDef *heth)
{
  GPIO_InitTypeDef GPIO_Init;
  GPIO_DelayTypeDef delay_conf;
  /* Prevent unused argument(s) compilation warning */
  UNUSED(heth);
  /* USER CODE BEGIN ETH_MspInit 0 */

  /* USER CODE END ETH_MspInit 0 */
    /* Peripheral clock enable */
  __HAL_RCC_ETH1MAC_CLK_ENABLE();
  __HAL_RCC_ETH1TX_CLK_ENABLE();
  __HAL_RCC_ETH1RX_CLK_ENABLE();

  /* Enable GPIOs clocks */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

    /**ETH GPIO Configuration
    PF7      ------> ETH_REF_CLK
    PF4      ------> ETH_MDIO
    PG11     ------> ETH_MDC
    PF10     ------> ETH_CRS_DV
    PF14     ------> ETH_RXD0
    PF15     ------> ETH_RXD1
    PF11     ------> ETH_TX_EN
    PF12     ------> ETH_TXD0
    PF13     ------> ETH_TXD1
    */

  /* PD1,3,12 AF*/
  GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_Init.Mode = GPIO_MODE_AF_PP;
  GPIO_Init.Pull = GPIO_NOPULL;
  GPIO_Init.Alternate = GPIO_AF11_ETH1;
  GPIO_Init.Pin = GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_12;
  HAL_GPIO_Init(GPIOD, &GPIO_Init);

  /* Configure PF2,7~15 AF */
  GPIO_Init.Pin = GPIO_PIN_2  | GPIO_PIN_7  | GPIO_PIN_5  |
                  GPIO_PIN_8  | GPIO_PIN_9  | GPIO_PIN_10 | GPIO_PIN_11 |
                  GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOF, &GPIO_Init);

  delay_conf.Delay = GPIO_DELAY_PS_500;
  delay_conf.Path = GPIO_PATH_IN;
  HAL_GPIO_SetDelay(GPIOF, GPIO_PIN_7, &delay_conf);

  /* Configure PG3,4 AF */
  GPIO_Init.Pin = GPIO_PIN_3 | GPIO_PIN_4;
  HAL_GPIO_Init(GPIOG, &GPIO_Init);

  /* Configure PF0 AF */
  GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;
  GPIO_Init.Pin =  GPIO_PIN_0;
  GPIO_Init.Alternate = GPIO_AF12_ETH1;
  HAL_GPIO_Init(GPIOF, &GPIO_Init);

  HAL_NVIC_SetPriority(ETH1_IRQn, 7, 0);
  HAL_NVIC_EnableIRQ(ETH1_IRQn);
  /* USER CODE BEGIN ETH_MspInit 1 */

  /* USER CODE END ETH_MspInit 1 */
}

/**
* @brief ETH MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param heth: ETH handle pointer
* @retval None
*/
void HAL_ETH_MspDeInit(ETH_HandleTypeDef* heth)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(heth);

  /* USER CODE BEGIN ETH_MspDeInit 0 */

  /* USER CODE END ETH_MspDeInit 0 */
    /* Peripheral clock disable */
  __HAL_RCC_ETH1MAC_CLK_DISABLE();
  __HAL_RCC_ETH1TX_CLK_DISABLE();
  __HAL_RCC_ETH1RX_CLK_DISABLE();

    /**ETH GPIO Configuration
    PF7      ------> ETH_REF_CLK
    PF4      ------> ETH_MDIO
    PG11     ------> ETH_MDC
    PF10     ------> ETH_CRS_DV
    PF14     ------> ETH_RXD0
    PF15     ------> ETH_RXD1
    PF11     ------> ETH_TX_EN
    PF12     ------> ETH_TXD0
    PF13     ------> ETH_TXD1
    */
    HAL_GPIO_DeInit(GPIOF,  GPIO_PIN_4|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_11);

    /* ETH interrupt DeInit */
    HAL_NVIC_DisableIRQ(ETH1_IRQn);
  /* USER CODE BEGIN ETH_MspDeInit 1 */

  /* USER CODE END ETH_MspDeInit 1 */

}

void MX_ETH_Shutdown(void)
{
	HAL_ETH_MspDeInit(&heth);
}

/**
  * @brief This function handles Ethernet global interrupt.
  */
void ETH1_IRQHandler(void)
{
  /* USER CODE BEGIN ETH_IRQn 0 */

  /* USER CODE END ETH_IRQn 0 */
  HAL_ETH_IRQHandler(&heth);
  /* USER CODE BEGIN ETH_IRQn 1 */

  /* USER CODE END ETH_IRQn 1 */
}

