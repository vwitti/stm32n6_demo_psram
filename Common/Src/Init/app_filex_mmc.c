/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_filex_mmc.c
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
#include "BSP/Inc/mmc.h"
#include "Common/Inc/Init/app_filex.h"
#include "Common/Inc/Init/error_handler.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Message content*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Buffer for FileX FX_MEDIA sector cache. */
ALIGN_32BYTES (uint32_t fx_mmc_media_memory[FX_STM32_MMC_DEFAULT_SECTOR_SIZE / sizeof(uint32_t)]);
/* Define FileX global data structures.  */
FX_MEDIA        emmc_disk;

/* Private function prototypes -----------------------------------------------*/

FX_MEDIA *  MX_FileX_GetMedia_MassStorage(void)
{
	return &emmc_disk;
}


/**
  * @brief  Application FileX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT MX_FileX_Init(VOID *memory_ptr)
{
  UINT ret = FX_SUCCESS;

  /* Initialize FileX.  */
  fx_system_initialize();

  /* Open the SD disk driver */
  ret =  fx_media_open(&emmc_disk, FX_EMMC_VOLUME_NAME, fx_stm32_mmc_driver, (VOID *)FX_NULL, (VOID *) fx_mmc_media_memory, sizeof(fx_mmc_media_memory));

  /* Check the media open sd_status */
  if (ret != FX_SUCCESS)
  {
    printf("Can open media\n");
  }

  return ret;
}
