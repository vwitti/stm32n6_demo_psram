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
#include "tcsglobal/asg_evo.h"
#include "tcsglobal/status_codes.h"
#include "tcsglobal/system_constants.h"
#include "stm32n6xx_hal.h"
#include "SysLog/Syslog.h"
#include "Common/Inc/Init/start_screen_lcd.h"
#include "Common/Inc/Init/extmem/extmem_manager.h"
#include "extmem_manager.h"

// Override Default Tick init Code, this causes massives issue with ThreadX initialisation
bool MX_EXTMEM_xspi_Info(uint8_t id)
{
#if !defined(PSRAM_CONFIG_STM_EXAMPLE_PSRAM_MEM_MAPPED)
	EXTMEM_DRIVER_CUSTOM_MemInfoTypeDef sMemInfo;
	EXTMEM_StatusTypeDef ret_extmem;
	char text[60];
	char type[10];
	char standard[14];
	uint32_t size;
	uint32_t freq;

	switch(id)
	{
	case EXTMEM_SPI_FLASH:
	case EXTMEM_SPI_RAM:
		ret_extmem = EXTMEM_GetInfo(id, &sMemInfo);
		if(ret_extmem != EXTMEM_OK)
		{
			printf("can read info for memid %d (res=%d)\n", id, ret_extmem);
			return false;
		}
		break;
	default:
		return false;
	}

	switch(sMemInfo.MemType)
	{
	case EXTMEM_CUSTOM_NOR_FLASH:
		strcpy(type, "NOR-FLASH");
		break;
	case EXTMEM_CUSTOM_PSRAM:
		strcpy(type, "PS-RAM");
		break;
	default:
		strcpy(type, "???");
		break;
	}
	switch(sMemInfo.MemStandard)
	{
	case EXTMEM_CUSTOM_STD_MICRON:
		strcpy(standard, "MICRON");
		break;
	case EXTMEM_CUSTOM_STD_MACRONIX:
		strcpy(standard, "MACRONIX");
		break;
	case EXTMEM_CUSTOM_STD_APMEM:
		strcpy(standard, "APMEM");
		break;
	case EXTMEM_CUSTOM_STD_MACRONIX_RAM:
		strcpy(standard, "MACRONIX_RAM");
		break;
	case EXTMEM_CUSTOM_STD_APMEM_16BITS:
		strcpy(standard, "APMEM_16BIT");
		break;
	default:
		strcpy(standard, "???");
		break;
	}
	size = (2 << sMemInfo.MemSize) / 0x100000; // in MB (2 wegen Worte, nicht Bytes)
	freq = sMemInfo.MemRealFreq / 1000000;   // in MHz
	snprintf(text, sizeof(text), "%s,%s, %ld MB, %ld MHz", type, standard, size, freq);
	StartScreenLcd_WriteLine("Detected: %s", text);
#endif
	return true;
}

