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
#include "SysLog/Syslog.h"
#include "SysLayer/HalSystemStop.h"
#include "Common/Inc/Init/start_screen_lcd.h"
#include "Common/Inc/Init/app_threadx.h"
#include "Common/Inc/Init/app_filex.h"

#if defined (PROG_TYPE_FSBL)

#include "tcs/FSBL_Assets/generated/FSBL_assets.h"

bool MX_EXTMEM_verify_tcsromfs_mbr(void)
{
	int res;
	const void * addr1 = (const void *) XSPI_FLASH_PHY_ADDR(XSPI_OFFSET_FSBL_ASSETS + romfs4_OFFSET); // MBR to check
	const void * addr2 = (const void *) XSPI_FLASH_PHY_ADDR(XSPI_OFFSET_TCS_ROMFS);                   // Installed MBR

	/* We assume to be in memory mapped mode */
	res = memcmp(addr1, addr2, romfs4_LENGTH);
	if(res == 0)
	{
		printf("TCS-ROMFS: Valid MBR detected.\n");
		return true;
	}
	StartScreenLcd_WriteLine("TCS-ROMFS: Invalid MBR detected!");
	return false;
}

bool MX_EXTMEM_init_tcs_romfs(void)
{
	UINT ret = MX_FileX_Init_ROM_DISK(FX_GetBytePoolDesc());
    if (ret != FX_SUCCESS)
    {
    	StartScreenLcd_WriteLine("TCS-ROMFS: failed to mount (SPI mode)");
    	HAL_Thread_SystemStop();
    }
    StartScreenLcd_WriteLine("TCS-ROMFS: device mounted (SPI mode)");
	return true;
}

#endif

#if defined (PROG_TYPE_APPLI)

bool MX_EXTMEM_init_tcs_romfs(void)
{
	UINT ret = MX_FileX_Init_ROM_DISK_MM(FX_GetBytePoolDesc());
    if (ret != FX_SUCCESS)
    {
    	StartScreenLcd_WriteLine("TCS-ROMFS: failed to mount (Map mode)");
    	HAL_Thread_SystemStop();
    }
    StartScreenLcd_WriteLine("TCS-ROMFS: device mounted (Map mode)");
	return true;
}


#endif



