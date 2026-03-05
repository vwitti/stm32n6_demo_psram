
#include <stdio.h>
#include "tcsglobal/system_constants.h"
#include "BSP/Inc/xspi.h"
#include "Common/Inc/Init/error_handler.h"

XSPI_HandleTypeDef       hxspi1;
XSPI_HandleTypeDef       hxspi2;

#define HSLV_OTP 124
#define VDDIO3_HSLV_MASK (1<<15)

/**
  * @brief XSPI1 Initialization Function
  * @param None
  * @retval None
  */
void MX_XSPI1_Init(void)
{

  /* USER CODE BEGIN XSPI1_Init 0 */

  /* USER CODE END XSPI1_Init 0 */

  XSPIM_CfgTypeDef sXspiManagerCfg = {0};

  /* USER CODE BEGIN XSPI1_Init 1 */

  /* USER CODE END XSPI1_Init 1 */
  /* XSPI1 parameter configuration*/
  hxspi1.Instance = XSPI1;
  hxspi1.Init.FifoThresholdByte = 4;
  hxspi1.Init.MemoryMode = HAL_XSPI_SINGLE_MEM;
  hxspi1.Init.MemoryType = HAL_XSPI_MEMTYPE_APMEM_16BITS;
  hxspi1.Init.MemorySize = HAL_XSPI_SIZE_256MB;
  hxspi1.Init.ChipSelectHighTimeCycle = 5;
  hxspi1.Init.FreeRunningClock = HAL_XSPI_FREERUNCLK_DISABLE;
  hxspi1.Init.ClockMode = HAL_XSPI_CLOCK_MODE_0;
  hxspi1.Init.WrapSize = HAL_XSPI_WRAP_NOT_SUPPORTED;
  hxspi1.Init.ClockPrescaler = 1;
  hxspi1.Init.SampleShifting = HAL_XSPI_SAMPLE_SHIFT_NONE;
  hxspi1.Init.DelayHoldQuarterCycle = HAL_XSPI_DHQC_DISABLE;
  hxspi1.Init.ChipSelectBoundary = HAL_XSPI_BONDARYOF_16KB;
  hxspi1.Init.MaxTran = 0;
  hxspi1.Init.Refresh = 0;
  hxspi1.Init.MemorySelect = HAL_XSPI_CSSEL_NCS1;
  if (HAL_XSPI_Init(&hxspi1) != HAL_OK)
  {
    Error_Handler("MX_XSPI1_Init: 1");
  }
  sXspiManagerCfg.nCSOverride = HAL_XSPI_CSSEL_OVR_NCS1;
  sXspiManagerCfg.IOPort = HAL_XSPIM_IOPORT_1;
  sXspiManagerCfg.Req2AckTime = 1;
  if (HAL_XSPIM_Config(&hxspi1, &sXspiManagerCfg, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler("MX_XSPI1_Init: 2");
  }
  /* USER CODE BEGIN XSPI1_Init 2 */

  /* USER CODE END XSPI1_Init 2 */

}

/**
  * @brief XSPI2 Initialization Function
  * @param None
  * @retval None
  */
void MX_XSPI2_Init(void)
{

	  /* USER CODE BEGIN XSPI2_Init 0 */

	  /* USER CODE END XSPI2_Init 0 */

	  XSPIM_CfgTypeDef sXspiManagerCfg = {0};

	  /* USER CODE BEGIN XSPI2_Init 1 */

	  /* USER CODE END XSPI2_Init 1 */
	  /* XSPI2 parameter configuration*/
	  hxspi2.Instance = XSPI2;
	  hxspi2.Init.FifoThresholdByte = 4;
	  hxspi2.Init.MemoryMode = HAL_XSPI_SINGLE_MEM;
	  hxspi2.Init.MemoryType = HAL_XSPI_MEMTYPE_MACRONIX;
	  hxspi2.Init.MemorySize = HAL_XSPI_SIZE_1GB;
	  hxspi2.Init.ChipSelectHighTimeCycle = 2;
	  hxspi2.Init.FreeRunningClock = HAL_XSPI_FREERUNCLK_DISABLE;
	  hxspi2.Init.ClockMode = HAL_XSPI_CLOCK_MODE_0;
	  hxspi2.Init.WrapSize = HAL_XSPI_WRAP_NOT_SUPPORTED;
	  hxspi2.Init.ClockPrescaler = 0;
	  hxspi2.Init.SampleShifting = HAL_XSPI_SAMPLE_SHIFT_NONE;
	  hxspi2.Init.DelayHoldQuarterCycle = HAL_XSPI_DHQC_ENABLE;
	  hxspi2.Init.ChipSelectBoundary = HAL_XSPI_BONDARYOF_NONE;
	  hxspi2.Init.MaxTran = 0;
	  hxspi2.Init.Refresh = 0;
	  hxspi2.Init.MemorySelect = HAL_XSPI_CSSEL_NCS1;
	  if (HAL_XSPI_Init(&hxspi2) != HAL_OK)
	  {
	    Error_Handler("MX_XSPI2_Init: 1");
	  }
	  sXspiManagerCfg.nCSOverride = HAL_XSPI_CSSEL_OVR_NCS1;
	  sXspiManagerCfg.IOPort = HAL_XSPIM_IOPORT_2;
	  sXspiManagerCfg.Req2AckTime = 1;
	  if (HAL_XSPIM_Config(&hxspi2, &sXspiManagerCfg, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	  {
	    Error_Handler("MX_XSPI2_Init: 2");
	  }
	  /* USER CODE BEGIN XSPI2_Init 2 */

	  /* USER CODE END XSPI2_Init 2 */

}

/**
  * @brief XSPI MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hxspi: XSPI handle pointer
  * @retval None
  */
void HAL_XSPI_MspInit(XSPI_HandleTypeDef *hxspi)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

	  __HAL_RCC_XSPIM_CLK_ENABLE();

	  if(hxspi->Instance==XSPI1)
	  {

	  /** Initializes the peripherals clock
	  */
	    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_XSPI1;
	    PeriphClkInitStruct.Xspi1ClockSelection = RCC_XSPI1CLKSOURCE_HCLK;
	    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	    {
	      Error_Handler("HAL_XSPI_MspInit: 1");
	    }

	    /* Peripheral clock enable */
	    __HAL_RCC_XSPI1_CLK_ENABLE();

	    __HAL_RCC_GPIOP_CLK_ENABLE();
	    __HAL_RCC_GPIOO_CLK_ENABLE();
	    /**XSPI1 GPIO Configuration
	    PP7     ------> XSPIM_P1_IO7
	    PP6     ------> XSPIM_P1_IO6
	    PP0     ------> XSPIM_P1_IO0
	    PP4     ------> XSPIM_P1_IO4
	    PP1     ------> XSPIM_P1_IO1
	    PP15     ------> XSPIM_P1_IO15
	    PP5     ------> XSPIM_P1_IO5
	    PP12     ------> XSPIM_P1_IO12
	    PP3     ------> XSPIM_P1_IO3
	    PP2     ------> XSPIM_P1_IO2
	    PP13     ------> XSPIM_P1_IO13
	    PO2     ------> XSPIM_P1_DQS0
	    PP11     ------> XSPIM_P1_IO11
	    PP8     ------> XSPIM_P1_IO8
	    PP14     ------> XSPIM_P1_IO14
	    PO3     ------> XSPIM_P1_DQS1
	    PO0     ------> XSPIM_P1_NCS1
	    PP9     ------> XSPIM_P1_IO9
	    PP10     ------> XSPIM_P1_IO10
	    PO4     ------> XSPIM_P1_CLK
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_0|GPIO_PIN_4
	                          |GPIO_PIN_1|GPIO_PIN_15|GPIO_PIN_5|GPIO_PIN_12
	                          |GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_13|GPIO_PIN_11
	                          |GPIO_PIN_8|GPIO_PIN_14|GPIO_PIN_9|GPIO_PIN_10;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P1;
	    HAL_GPIO_Init(GPIOP, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_0|GPIO_PIN_4;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P1;
	    HAL_GPIO_Init(GPIOO, &GPIO_InitStruct);

	    /* USER CODE BEGIN XSPI1_MspInit 1 */

	    /* USER CODE END XSPI1_MspInit 1 */

	  }

	  if(hxspi->Instance==XSPI2)
	  {
	    /* USER CODE BEGIN XSPI2_MspInit 0 */
	    BSEC_HandleTypeDef hbsec;
	    uint32_t fuse_data = 0;

	    /* Enable BSEC & SYSCFG clocks to ensure BSEC data accesses */
	    __HAL_RCC_BSEC_CLK_ENABLE();

	    hbsec.Instance = BSEC;
	    if (HAL_BSEC_OTP_Read(&hbsec, HSLV_OTP, &fuse_data) != HAL_OK)
	    {
	    	Error_Handler("HAL_XSPI_MspInit: 2");
	    }

	    if (fuse_data & VDDIO3_HSLV_MASK)
	    {
	      /* High speed IO optimization is enabled */

	      /*  Select HCLK clock  */
	      PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_XSPI1;
		  PeriphClkInitStruct.Xspi2ClockSelection = RCC_XSPI1CLKSOURCE_HCLK;
	      if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	      {
	    	  Error_Handler("HAL_XSPI_MspInit: 3");
	      }

	      /* Peripheral clock enable */
	      __HAL_RCC_XSPI2_CLK_ENABLE();

	      __HAL_RCC_GPION_CLK_ENABLE();
	      /**XSPI2 GPIO Configuration
	      PN4     ------> XSPIM_P2_IO2
	      PN6     ------> XSPIM_P2_CLK
	      PN8     ------> XSPIM_P2_IO4
	      PN0     ------> XSPIM_P2_DQS0
	      PN3     ------> XSPIM_P2_IO1
	      PN5     ------> XSPIM_P2_IO3
	      PN1     ------> XSPIM_P2_NCS1
	      PN9     ------> XSPIM_P2_IO5
	      PN2     ------> XSPIM_P2_IO0
	      PN10     ------> XSPIM_P2_IO6
	      PN11     ------> XSPIM_P2_IO7
	      */
	      GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_0
	                            |GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_1|GPIO_PIN_9
	                            |GPIO_PIN_2|GPIO_PIN_10|GPIO_PIN_11;
	      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	      GPIO_InitStruct.Pull = GPIO_NOPULL;
	      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	      GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P2;
	      HAL_GPIO_Init(GPION, &GPIO_InitStruct);
	    }
	    else
	    {
	      /* High speed IO optimization is disabled, lower XSPI clock speed */

	      /*  Select IC3 clock from PLL1 at 50MHz (1200/24) as XSPI2 source */

	    /* USER CODE END XSPI2_MspInit 0 */

	    /** Initializes the peripherals clock
	    */
	    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_XSPI2;
	    PeriphClkInitStruct.Xspi2ClockSelection = RCC_XSPI2CLKSOURCE_IC3;
	    PeriphClkInitStruct.ICSelection[RCC_IC3].ClockSelection = RCC_ICCLKSOURCE_PLL1;
	    PeriphClkInitStruct.ICSelection[RCC_IC3].ClockDivider = 24;
	    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	    {
	    	Error_Handler("HAL_XSPI_MspInit: 4");
	    }

	    /* Peripheral clock enable */
	    __HAL_RCC_XSPI2_CLK_ENABLE();

	    __HAL_RCC_GPION_CLK_ENABLE();
	    /**XSPI2 GPIO Configuration
	    PN4     ------> XSPIM_P2_IO2
	    PN6     ------> XSPIM_P2_CLK
	    PN8     ------> XSPIM_P2_IO4
	    PN0     ------> XSPIM_P2_DQS0
	    PN3     ------> XSPIM_P2_IO1
	    PN5     ------> XSPIM_P2_IO3
	    PN1     ------> XSPIM_P2_NCS1
	    PN9     ------> XSPIM_P2_IO5
	    PN2     ------> XSPIM_P2_IO0
	    PN10     ------> XSPIM_P2_IO6
	    PN11     ------> XSPIM_P2_IO7
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_0
	                          |GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_1|GPIO_PIN_9
	                          |GPIO_PIN_2|GPIO_PIN_10|GPIO_PIN_11;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P2;
	    HAL_GPIO_Init(GPION, &GPIO_InitStruct);

	    /* USER CODE BEGIN XSPI2_MspInit 1 */
	   }
	    /* USER CODE END XSPI2_MspInit 1 */

	  }
}

/**
  * @brief XSPI MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @retval None
  */
void HAL_XSPI_MspDeInit(XSPI_HandleTypeDef *hxspi)
{
	  if(hxspi->Instance==XSPI1)
	  {
	    /* USER CODE BEGIN XSPI1_MspDeInit 0 */

	    /* USER CODE END XSPI1_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_XSPIM_CLK_DISABLE();
	    __HAL_RCC_XSPI1_CLK_DISABLE();

	    /**XSPI1 GPIO Configuration
	    PP7     ------> XSPIM_P1_IO7
	    PP6     ------> XSPIM_P1_IO6
	    PP0     ------> XSPIM_P1_IO0
	    PP4     ------> XSPIM_P1_IO4
	    PP1     ------> XSPIM_P1_IO1
	    PP15     ------> XSPIM_P1_IO15
	    PP5     ------> XSPIM_P1_IO5
	    PP12     ------> XSPIM_P1_IO12
	    PP3     ------> XSPIM_P1_IO3
	    PP2     ------> XSPIM_P1_IO2
	    PP13     ------> XSPIM_P1_IO13
	    PO2     ------> XSPIM_P1_DQS0
	    PP11     ------> XSPIM_P1_IO11
	    PP8     ------> XSPIM_P1_IO8
	    PP14     ------> XSPIM_P1_IO14
	    PO3     ------> XSPIM_P1_DQS1
	    PO0     ------> XSPIM_P1_NCS1
	    PP9     ------> XSPIM_P1_IO9
	    PP10     ------> XSPIM_P1_IO10
	    PO4     ------> XSPIM_P1_CLK
	    */
	    HAL_GPIO_DeInit(GPIOP, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_0|GPIO_PIN_4
	                          |GPIO_PIN_1|GPIO_PIN_15|GPIO_PIN_5|GPIO_PIN_12
	                          |GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_13|GPIO_PIN_11
	                          |GPIO_PIN_8|GPIO_PIN_14|GPIO_PIN_9|GPIO_PIN_10);

	    HAL_GPIO_DeInit(GPIOO, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_0|GPIO_PIN_4);

	    /* USER CODE BEGIN XSPI1_MspDeInit 1 */

	    /* USER CODE END XSPI1_MspDeInit 1 */
	  }

	  if(hxspi->Instance==XSPI2)
	  {
	    /* USER CODE BEGIN XSPI2_MspDeInit 0 */

	    /* USER CODE END XSPI2_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_XSPIM_CLK_DISABLE();
	    __HAL_RCC_XSPI2_CLK_DISABLE();

	    /**XSPI2 GPIO Configuration
	    PN4     ------> XSPIM_P2_IO2
	    PN6     ------> XSPIM_P2_CLK
	    PN8     ------> XSPIM_P2_IO4
	    PN0     ------> XSPIM_P2_DQS0
	    PN3     ------> XSPIM_P2_IO1
	    PN5     ------> XSPIM_P2_IO3
	    PN1     ------> XSPIM_P2_NCS1
	    PN9     ------> XSPIM_P2_IO5
	    PN2     ------> XSPIM_P2_IO0
	    PN10     ------> XSPIM_P2_IO6
	    PN11     ------> XSPIM_P2_IO7
	    */
	    HAL_GPIO_DeInit(GPION, GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_0
	                          |GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_1|GPIO_PIN_9
	                          |GPIO_PIN_2|GPIO_PIN_10|GPIO_PIN_11);

	    /* USER CODE BEGIN XSPI2_MspDeInit 1 */

	    /* USER CODE END XSPI2_MspDeInit 1 */
	  }

}
