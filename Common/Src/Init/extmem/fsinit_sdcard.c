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
#include <stdbool.h>
#include <string.h>
#include "stm32n6xx_hal.h"
#include "tcsglobal/asg_evo.h"
#include "tcsglobal/status_codes.h"
#include "tcsglobal/system_constants.h"
#include "BSP/Inc/sd.h"
#include "SysLog/Syslog.h"
#include "SysLayer/HalSystemStop.h"
#include "Common/Inc/Init/start_screen_lcd.h"
#include "Common/Inc/Init/app_threadx.h"
#include "Common/Inc/Init/app_filex.h"

bool MX_EXTMEM_init_external_mass_storage(void)
{
	UINT ret;

	/* Setup Filesystem, on Eval Board we assume a SD-Card installed, since ASG-EVO will have a soldered eMMC */
	MX_SDMMC2_SD_Pins();
	MX_SDMMC2_SD_Init();

    //MX_FileX_Init(FX_GetBytePoolDesc());
    ret = MX_FileX_Init_SD_Card(FX_GetBytePoolDesc());
    if (ret != FX_SUCCESS)
    {
    	StartScreenLcd_WriteLine("SD-Card: failed to mount");
    	HAL_Thread_SystemStop();
    }
	StartScreenLcd_WriteLine("SD-Card: device mounted");
	return true;
}

