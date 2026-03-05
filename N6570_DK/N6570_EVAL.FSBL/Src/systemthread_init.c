/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
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
#include "stdio.h"
#include "tcsglobal/asg_evo.h"
//#include "tcsglobal/status_codes.h"
//#include "tcsglobal/system_constants.h"
#include "STM32N6570-DK/stm32n6570_discovery.h"
#include "STM32N6570-DK/stm32n6570_discovery_lcd.h"
#include "Utilities/STM32N6/lcd/stm32_lcd.h"
//#include "BSP/Inc/eth.h"
//#include "BSP/Inc/xspi.h"
#include "AsgAssert/AsgAssert.h"
#include "SysLayer/HalBoard.h"
#include "SysLayer/HalThread.h"
//#include "SysLog/Syslog.h"
//#include "Utils/Sys_BuildInfo.h"
//#include "Utils/printf_utils.h"
#include "Common/Inc/Init/app_threadx.h"
//#include "Common/Inc/Init/app_netxduo.h"
#include "Common/Inc/Init/app_filex.h"
#include "Common/Inc/Init/start_screen_lcd.h"
#include "Common/Inc/Init/syscalls.h"
#include "Common/Inc/Init/extmem/extmem_manager.h"
//#include "Common/Inc/Update/firmware_update.h"
#include "Common/Inc/Test/psram_test.h"
#include "Common/Inc/Test/perf_test.h"
#include "Inc/systemthreads.h"

/* Private includes ----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
TX_THREAD tx_systeminit_thread;

void ThreadASG_SystemInit(uint32_t arg)
{
	//bool start_app_immediately = false;
	bool res;
	//bool res_mbrvalid;
	//teStatus eStatus_Update_RomFS = eStUpdateFailed;

	printf("FSBL System Init Thread started\n");

	/* Check performance */
	fsbl_perf_test();

	/* Basic services */
	HAL_Thread_Init();
	MX_EXTMEM_MANAGER_Init();		// Need HAL_tick
	EXTMEM_MemoryMappedMode(EXTMEM_SPI_FLASH, EXTMEM_ENABLE);
#if !defined(PSRAM_CONFIG_STM_EXAMPLE_PSRAM_MEM_MAPPED)
	EXTMEM_MemoryMappedMode(EXTMEM_SPI_RAM, EXTMEM_ENABLE);
#endif


	/* Check if internal memories are available */
	res =  MX_EXTMEM_xspi_Info(EXTMEM_SPI_FLASH);
	ASG_ASSERT(res == true);
	res =  MX_EXTMEM_xspi_Info(EXTMEM_SPI_RAM);
	ASG_ASSERT(res == true);

	/* Setup filesystems */
	MX_FileX_Init(FX_GetBytePoolDesc());

    /* Setup RAM Disk */
    StartScreenLcd_WriteLine("Start PSRAM test ...");
	res = fsbl_psram_test();
	ASG_ASSERT(res == true);
	MX_EXTMEM_init_ps_ramfs();

    	// This is our idle task here now, it runs blocking and prevent any task from running with a priority lower
	// then PRIO_IDLE, since we boot the application we should never reach this
	while (1)
	{
		/* While waiting for character from PC side, LED1 is toggling every 100ms */
		HAL_Board_Led_RUN(true);
		HAL_Delay(TX_MS_TO_TICK(800));
		HAL_Board_Led_RUN(false);
		HAL_Delay(TX_MS_TO_TICK(200));
	}
}
