
#include <stdio.h>
#include "tcsglobal/system_constants.h"
#include "BSP/Inc/jpeg.h"
#include "BSP/Inc/hpdma.h"
#include "Common/Inc/Init/error_handler.h"
#include "stm32n6xx_hal.h"

// Handling of internal RAMs
JPEG_HandleTypeDef hjpeg;

/**
  * @brief JPEG Initialization Function
  * @param None
  * @retval None
  */
void MX_JPEG_Init(void)
{

  /* USER CODE BEGIN JPEG_Init 0 */

  /* USER CODE END JPEG_Init 0 */

  /* USER CODE BEGIN JPEG_Init 1 */

  /* USER CODE END JPEG_Init 1 */
  hjpeg.Instance = JPEG;
  if (HAL_JPEG_Init(&hjpeg) != HAL_OK)
  {
    Error_Handler("JPEG");
  }
  /* USER CODE BEGIN JPEG_Init 2 */

  /* USER CODE END JPEG_Init 2 */

}

/**
  * @brief This function handles JPEG global interrupt.
  */
void JPEG_IRQHandler(void)
{
  /* USER CODE BEGIN JPEG_IRQn 0 */

  /* USER CODE END JPEG_IRQn 0 */
  HAL_JPEG_IRQHandler(&hjpeg);
  /* USER CODE BEGIN JPEG_IRQn 1 */

  /* USER CODE END JPEG_IRQn 1 */
}

/**
  * @brief JPEG MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hjpeg: JPEG handle pointer
  * @retval None
  */
void HAL_JPEG_MspInit(JPEG_HandleTypeDef* hjpeg)
{
  DMA_IsolationConfigTypeDef IsolationConfiginput;
  DMA_DataHandlingConfTypeDef DataHandlingConfig;
  if(hjpeg->Instance==JPEG)
  {
    /* USER CODE BEGIN JPEG_MspInit 0 */

    /* USER CODE END JPEG_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_JPEG_CLK_ENABLE();

    /* JPEG DMA Init */
    /* HPDMA1_REQUEST_JPEG_TX Init */
    handle_HPDMA1_Channel1.Instance = HPDMA1_Channel1;
    handle_HPDMA1_Channel1.Init.Request = HPDMA1_REQUEST_JPEG_TX;
    handle_HPDMA1_Channel1.Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
    handle_HPDMA1_Channel1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    handle_HPDMA1_Channel1.Init.SrcInc = DMA_SINC_FIXED;
    handle_HPDMA1_Channel1.Init.DestInc = DMA_DINC_INCREMENTED;
    handle_HPDMA1_Channel1.Init.SrcDataWidth = DMA_SRC_DATAWIDTH_WORD;
    handle_HPDMA1_Channel1.Init.DestDataWidth = DMA_DEST_DATAWIDTH_WORD;
    handle_HPDMA1_Channel1.Init.Priority = DMA_HIGH_PRIORITY;
    handle_HPDMA1_Channel1.Init.SrcBurstLength = 8;
    handle_HPDMA1_Channel1.Init.DestBurstLength = 8;
    handle_HPDMA1_Channel1.Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT1|DMA_DEST_ALLOCATED_PORT0;
    handle_HPDMA1_Channel1.Init.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
    handle_HPDMA1_Channel1.Init.Mode = DMA_NORMAL;
    if (HAL_DMA_Init(&handle_HPDMA1_Channel1) != HAL_OK)
    {
      Error_Handler("MSP_JPEG_1");
    }

    __HAL_LINKDMA(hjpeg, hdmaout, handle_HPDMA1_Channel1);

    IsolationConfiginput.CidFiltering = DMA_ISOLATION_ON;
    IsolationConfiginput.StaticCid = DMA_CHANNEL_STATIC_CID_1;
    if (HAL_DMA_SetIsolationAttributes(&handle_HPDMA1_Channel1, &IsolationConfiginput) != HAL_OK)
    {
      Error_Handler("MSP_JPEG_2");
    }

    /* HPDMA1_REQUEST_JPEG_RX Init */
    handle_HPDMA1_Channel0.Instance = HPDMA1_Channel0;
    handle_HPDMA1_Channel0.Init.Request = HPDMA1_REQUEST_JPEG_RX;
    handle_HPDMA1_Channel0.Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
    handle_HPDMA1_Channel0.Init.Direction = DMA_MEMORY_TO_PERIPH;
    handle_HPDMA1_Channel0.Init.SrcInc = DMA_SINC_INCREMENTED;
    handle_HPDMA1_Channel0.Init.DestInc = DMA_DINC_FIXED;
    handle_HPDMA1_Channel0.Init.SrcDataWidth = DMA_SRC_DATAWIDTH_BYTE;
    handle_HPDMA1_Channel0.Init.DestDataWidth = DMA_DEST_DATAWIDTH_WORD;
    handle_HPDMA1_Channel0.Init.Priority = DMA_HIGH_PRIORITY;
    handle_HPDMA1_Channel0.Init.SrcBurstLength = 8;
    handle_HPDMA1_Channel0.Init.DestBurstLength = 8;
    handle_HPDMA1_Channel0.Init.TransferAllocatedPort = DMA_SRC_ALLOCATED_PORT0|DMA_DEST_ALLOCATED_PORT1;
    handle_HPDMA1_Channel0.Init.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
    handle_HPDMA1_Channel0.Init.Mode = DMA_NORMAL;
    if (HAL_DMA_Init(&handle_HPDMA1_Channel0) != HAL_OK)
    {
      Error_Handler("MSP_JPEG_3");
    }

    DataHandlingConfig.DataExchange = DMA_EXCHANGE_NONE;
    DataHandlingConfig.DataAlignment = DMA_DATA_PACK;
    if (HAL_DMAEx_ConfigDataHandling(&handle_HPDMA1_Channel0, &DataHandlingConfig) != HAL_OK)
    {
      Error_Handler("MSP_JPEG_4");
    }

    __HAL_LINKDMA(hjpeg, hdmain, handle_HPDMA1_Channel0);

    IsolationConfiginput.CidFiltering = DMA_ISOLATION_ON;
    IsolationConfiginput.StaticCid = DMA_CHANNEL_STATIC_CID_1;
    if (HAL_DMA_SetIsolationAttributes(&handle_HPDMA1_Channel0, &IsolationConfiginput) != HAL_OK)
    {
      Error_Handler("MSP_JPEG_5");
    }

    /* JPEG interrupt Init */
    HAL_NVIC_SetPriority(JPEG_IRQn, 8, 0);
    HAL_NVIC_EnableIRQ(JPEG_IRQn);
    /* USER CODE BEGIN JPEG_MspInit 1 */

    /* USER CODE END JPEG_MspInit 1 */

  }

}

/**
  * @brief JPEG MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hjpeg: JPEG handle pointer
  * @retval None
  */
void HAL_JPEG_MspDeInit(JPEG_HandleTypeDef* hjpeg)
{
  if(hjpeg->Instance==JPEG)
  {
    /* USER CODE BEGIN JPEG_MspDeInit 0 */

    /* USER CODE END JPEG_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_JPEG_CLK_DISABLE();

    /* JPEG DMA DeInit */
    HAL_DMA_DeInit(hjpeg->hdmaout);
    HAL_DMA_DeInit(hjpeg->hdmain);

    /* JPEG interrupt DeInit */
    HAL_NVIC_DisableIRQ(JPEG_IRQn);
    /* USER CODE BEGIN JPEG_MspDeInit 1 */

    /* USER CODE END JPEG_MspDeInit 1 */
  }

}
