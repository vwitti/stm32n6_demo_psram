/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_filex.c
  * @author  MCD Application Team
  * @brief   FileX applicative file
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "tcsglobal/asg_evo.h"
#include "BSP/Inc/sd.h"
#include "Common/Inc/Init/app_filex.h"
#include "Common/Inc/Init/error_handler.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Message content*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Buffer for FileX FX_MEDIA sector cache. */
ALIGN_32BYTES (uint32_t fx_sd_media_memory[FX_STM32_SD_DEFAULT_SECTOR_SIZE / sizeof(uint32_t)]);

/* Define FileX global data structures.  */
FX_MEDIA        sdio_disk;

/* Private function prototypes -----------------------------------------------*/

static UINT SD_IsDetected(uint32_t Instance);

FX_MEDIA *  MX_FileX_GetMedia_MassStorage(void)
{
	return &sdio_disk;
}

/**
  * @brief  Application FileX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT MX_FileX_Init(VOID *memory_ptr)
{
  /* Initialize FileX.  */
  fx_system_initialize();

  return FX_SUCCESS;
}

UINT MX_FileX_Init_SD_Card(VOID *memory_ptr)
{
	  UINT ret;

	  /* Open the SD disk driver */
	  ret =  fx_media_open(&sdio_disk, FX_SD_VOLUME_NAME, fx_stm32_sd_driver, (VOID *)FX_NULL, (VOID *) fx_sd_media_memory, sizeof(fx_sd_media_memory));
	  /* Check the media open sd_status */
	  if (ret != FX_SUCCESS)
	  {
	    printf("Cant open DS-Card media driver\n");
	  }

	  if(SD_IsDetected(FX_STM32_SD_INSTANCE) == HAL_OK)
	  {
		  printf("SD-Card is inserted!!\n");
	  }

	  return ret;
}

/**
 * @brief  Detects if SD card is correctly plugged in the memory slot or not.
 * @param Instance  SD Instance
 * @retval Returns if SD is detected or not
 */
static UINT SD_IsDetected(uint32_t Instance)
{
  UINT ret;

  if(Instance > 1)
  {
    ret = HAL_ERROR;
  }
  else
  {
    /* Check SD card detect pin */
    if (HAL_GPIO_ReadPin(SD_DETECT_GPIO_Port, SD_DETECT_Pin) == GPIO_PIN_SET)
    {
      ret = HAL_ERROR;
    }
    else
    {
      ret = HAL_OK;
    }
  }

  return ret;
}

static ULONG last_time;

/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  ULONG curr = tx_time_get();

  //printf("c=%ld l=%ld\n", curr, last_time);

  if((curr  - last_time) > 100)
  {
	  if(GPIO_Pin == SD_DETECT_Pin)
	  {
		  // ....
	  }
  }

  last_time = curr;
  return;
}

