/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include <string.h>
#include <stdio.h>
#include "stm32n6xx_hal.h"
#include "BSP/Inc/gpio.h"
#include "Common/Inc/Init/hw/system_clocks.h"
#include "Common/Inc/Init/error_handler.h"

// SEE: CubeMX Project tcs/CubeMX/ClockLayout/ASG-EVO_ClockConfiguration

/* Private includes ----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#if STM32N6570_CPU_CLOCK != 600 && \
	STM32N6570_CPU_CLOCK != 800
#error "Invalid CPU clock selection. Cant configure other values"
#endif

/* Private variables ---------------------------------------------------------*/

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init_EnableClockOverdrive(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin Output Level */

#if STM32N6570_CPU_CLOCK == 600
  HAL_GPIO_WritePin(VDDCORE_OVERDRIVE_GPIO_Port, VDDCORE_OVERDRIVE_Pin, GPIO_PIN_RESET);
#endif
#if STM32N6570_CPU_CLOCK == 800
  HAL_GPIO_WritePin(VDDCORE_OVERDRIVE_GPIO_Port, VDDCORE_OVERDRIVE_Pin, GPIO_PIN_SET);
#endif

  /*Configure GPIO pin : VDDCORE_OVERDRIVE_Pin */
  GPIO_InitStruct.Pin = VDDCORE_OVERDRIVE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(VDDCORE_OVERDRIVE_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the System Power Supply
  */
  if (HAL_PWREx_ConfigSupply(PWR_EXTERNAL_SOURCE_SUPPLY) != HAL_OK)
  {
	  Error_Handler_NoPrintf();
  }

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE0) != HAL_OK)
  {
	  Error_Handler_NoPrintf();
  }

  /* Enable HSI */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL1.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
	  Error_Handler_NoPrintf();
  }

  /* Wait HSE stabilization time before its selection as PLL source. */
  //HAL_Delay(HSE_STARTUP_TIMEOUT);
  for(int i=0;i<500000;i++) {

  }

  /** Initializes TIMPRE when TIM is used as Systick Clock Source
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_TIM;
  PeriphClkInitStruct.TIMPresSelection = RCC_TIMPRES_DIV1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
	  Error_Handler_NoPrintf();
  }

  /** Get current CPU/System buses clocks configuration and if necessary switch
 to intermediate HSI clock to ensure target clock can be set
  */
  HAL_RCC_GetClockConfig(&RCC_ClkInitStruct);
  if ((RCC_ClkInitStruct.CPUCLKSource == RCC_CPUCLKSOURCE_IC1) ||
     (RCC_ClkInitStruct.SYSCLKSource == RCC_SYSCLKSOURCE_IC2_IC6_IC11))
  {
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_CPUCLK | RCC_CLOCKTYPE_SYSCLK);
    RCC_ClkInitStruct.CPUCLKSource = RCC_CPUCLKSOURCE_HSI;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
    {
      /* Initialization Error */
    	Error_Handler_NoPrintf();
    }
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL1.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL1.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL1.PLLM = 6;
  RCC_OscInitStruct.PLL1.PLLN = 100;
  RCC_OscInitStruct.PLL1.PLLFractional = 0;
  RCC_OscInitStruct.PLL1.PLLP1 = 1;
  RCC_OscInitStruct.PLL1.PLLP2 = 1;
  RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL2.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL2.PLLM = 4;
  RCC_OscInitStruct.PLL2.PLLN = 100;
  RCC_OscInitStruct.PLL2.PLLFractional = 0;
  RCC_OscInitStruct.PLL2.PLLP1 = 2;
  RCC_OscInitStruct.PLL2.PLLP2 = 1;
  RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL3.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL3.PLLM = 6;
  RCC_OscInitStruct.PLL3.PLLN = 225;
  RCC_OscInitStruct.PLL3.PLLFractional = 0;
  RCC_OscInitStruct.PLL3.PLLP1 = 2;
  RCC_OscInitStruct.PLL3.PLLP2 = 1;
  RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL4.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL4.PLLM = 6;
  RCC_OscInitStruct.PLL4.PLLN = 250;
  RCC_OscInitStruct.PLL4.PLLFractional = 0;
  RCC_OscInitStruct.PLL4.PLLP1 = 2;
  RCC_OscInitStruct.PLL4.PLLP2 = 1;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
	  Error_Handler_NoPrintf();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_CPUCLK|RCC_CLOCKTYPE_HCLK
                              |RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2|RCC_CLOCKTYPE_PCLK5
                              |RCC_CLOCKTYPE_PCLK4;
  RCC_ClkInitStruct.CPUCLKSource = RCC_CPUCLKSOURCE_IC1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_IC2_IC6_IC11;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;
  RCC_ClkInitStruct.APB5CLKDivider = RCC_APB5_DIV1;
#if STM32N6570_CPU_CLOCK == 600
  RCC_ClkInitStruct.IC1Selection.ClockSelection = RCC_ICCLKSOURCE_PLL2;
#endif
#if STM32N6570_CPU_CLOCK == 800
  RCC_ClkInitStruct.IC1Selection.ClockSelection = RCC_ICCLKSOURCE_PLL1;
#endif
  RCC_ClkInitStruct.IC1Selection.ClockDivider = 1;
  RCC_ClkInitStruct.IC2Selection.ClockSelection = RCC_ICCLKSOURCE_PLL1;
  RCC_ClkInitStruct.IC2Selection.ClockDivider = 2;
  RCC_ClkInitStruct.IC6Selection.ClockSelection = RCC_ICCLKSOURCE_PLL4;
  RCC_ClkInitStruct.IC6Selection.ClockDivider = 1;
  RCC_ClkInitStruct.IC11Selection.ClockSelection = RCC_ICCLKSOURCE_PLL3;
  RCC_ClkInitStruct.IC11Selection.ClockDivider = 1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
  {
	  Error_Handler_NoPrintf();
  }
}

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Init(void)
{
	MX_GPIO_Init_EnableClockOverdrive();
	SystemClock_Config();
}

void SystemClock_Dump(void)
{
	uint32_t clk;

	clk = HAL_RCC_GetCpuClockFreq();
	printf("CPU   : %10ld Hz\n", clk);
	clk = HAL_RCC_GetSysClockFreq();
	printf("SYS   : %10ld Hz\n", clk);
	clk = HAL_RCC_GetNPUClockFreq();
	printf("NPU   : %10ld Hz\n", clk);
	clk = HAL_RCC_GetNPURAMSClockFreq();
	printf("NPURAM: %10ld Hz\n", clk);
	clk = HAL_RCC_GetHCLKFreq();
	printf("HCLK  : %10ld Hz\n", clk);
	clk = HAL_RCC_GetPCLK1Freq();
	printf("PCLK1 : %10ld Hz\n", clk);
	clk = HAL_RCC_GetPCLK2Freq();
	printf("PCLK2 : %10ld Hz\n", clk);
	clk = HAL_RCC_GetPCLK4Freq();
	printf("PCLK4 : %10ld Hz\n", clk);
	clk = HAL_RCC_GetPCLK5Freq();
	printf("PCLK5 : %10ld Hz\n", clk);

	clk = HAL_RCCEx_GetPLL1CLKFreq();
	printf("PLL1  : %10ld Hz\n", clk);
	clk = HAL_RCCEx_GetPLL2CLKFreq();
	printf("PLL2  : %10ld Hz\n", clk);
	clk = HAL_RCCEx_GetPLL3CLKFreq();
	printf("PLL3  : %10ld Hz\n", clk);
	clk = HAL_RCCEx_GetPLL4CLKFreq();
	printf("PLL4  : %10ld Hz\n", clk);
	clk = HAL_RCCEx_GetTIMGFreq();

	printf("TIM   : %10ld Hz\n", clk);
	clk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_ETH1);
	printf("ETH1  : %10ld Hz\n", clk);
	clk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_LTDC);
	printf("LTDC  : %10ld Hz\n", clk);
	clk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_USART1);
	printf("USART1: %10ld Hz\n", clk);
	clk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_USART2);
	printf("USART2: %10ld Hz\n", clk);
	clk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI1);
	printf("XSPI1 : %10ld Hz\n", clk);
	clk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI2);
	printf("XSPI2 : %10ld Hz\n", clk);
	clk = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_XSPI3);
	printf("XSPI3 : %10ld Hz\n", clk);
}
