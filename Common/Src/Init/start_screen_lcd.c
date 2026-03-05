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
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "tcsglobal/asg_evo.h"
#include "tcsglobal/system_constants.h"
#include "tcs/FSBL_Assets/generated/FSBL_assets.h"
#include "Utils/Sys_BuildInfo.h"
#include "stm32n6xx_hal.h"
#include "STM32N6570-DK/stm32n6570_discovery.h"
#include "STM32N6570-DK/stm32n6570_discovery_lcd.h"
#include "SysLog/Syslog.h"
#include "Utilities/STM32N6/lcd/stm32_lcd.h"
#include "Common/Inc/Init/start_screen_lcd.h"
#include "Common/Inc/Init/app_threadx.h"
#if defined(PROG_TYPE_APPLI)
#include "Common/Inc/Init/app_filex.h"
#endif

#define TEXT_MESSAGE_X_AXIS		(10)
#define TEXT_MESSAGE_Y_AXIS		(74)
#define TEXT_LINES_ROLLOVER     (20)		// Rollover in screen and start from top
#define TEXT_BUFFER_SIZE		(80)

#if PROJECT_OS_USE_TOUCHGFX_LIB == 0
static uint32_t y_text_row = TEXT_MESSAGE_Y_AXIS;
static uint32_t num_lines;
#endif
static uint32_t x_size;
static uint32_t y_size;
static bool init_threadx = false;
static bool init_lcd = false;
static TX_MUTEX lock_screen;

void StartScreenLcd_init_threadx(void)
{
	UINT s;

	s = tx_mutex_create(&lock_screen, (CHAR*)"lock_screen", TX_INHERIT);
	if (s == TX_SUCCESS)
	{
		init_threadx = true;
	}
}

// Very simple module to show a start screen
void StartScreenLcd_init(uint8_t screen_id)
{
	char text[40];

	/* Setup Display */
	BSP_LCD_Init(DISCORVERY_GRAPHIC_LIB_INSTANCE, LCD_ORIENTATION_LANDSCAPE);
	UTIL_LCD_SetFuncDriver(&LCD_Driver);

	/* Draw init screen */
	BSP_LCD_GetXSize(0, &x_size);
	BSP_LCD_GetYSize(0, &y_size);

	/* Clear the LCD */
	UTIL_LCD_SetFont(&UTIL_LCD_DEFAULT_FONT);
	UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLUE);
	UTIL_LCD_Clear(UTIL_LCD_COLOR_BLUE);
	//UTIL_LCD_DrawLine(0, 95, x_size, 95, UTIL_LCD_COLOR_WHITE);
	UTIL_LCD_FillRect(x_size - 320, 0, 320, 74, UTIL_LCD_COLOR_WHITE);

	/* Set the LCD Text Color */
	UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);

	/* Display LCD messages */
	UTIL_LCD_SetFont(&Font24);
	switch(screen_id)
	{
	case START_SCREEN_ID_FSBL:
	case START_SCREEN_ID_APPLI:
		snprintf(text, sizeof(text), "%s", PROJECT_BUILD_NAME);
		UTIL_LCD_DisplayStringAt(30, 20, (uint8_t *) text, LEFT_MODE);
		break;
	default:
		UTIL_LCD_DisplayStringAt(30, 20, (uint8_t *)"PROGRAM START", LEFT_MODE);
		break;
	}

	UTIL_LCD_SetFont(&Font12);
	UTIL_LCD_DisplayStringAt(0, y_size - 20, (uint8_t *)"Copyright (c) Tiefenbach GmbH 2025", CENTER_MODE);
	init_lcd = true;
}

void StartScreenLcd_WriteLine(const char* fmt, ...)
{
	char text[TEXT_BUFFER_SIZE];
	size_t len;

	/* Setup String with spaces and terminate */
	memset(text, ' ', sizeof(text));
	text[sizeof(text) - 1]=0;

    va_list ap;
    va_start(ap, fmt);
	vsnprintf(text, sizeof(text), fmt, ap);
    va_end(ap);

    /* Replace termin character by space */
    len = strlen(text);
    text[len]=' ';

    if(init_threadx == true) {
    	tx_mutex_get(&lock_screen, TX_WAIT_FOREVER);
    }

#if PROJECT_OS_USE_TOUCHGFX_LIB == 0
    if(init_lcd == true)
    {
    	num_lines++;
    	if((num_lines % TEXT_LINES_ROLLOVER) == 0) {  // Start drawing from top
    		y_text_row = TEXT_MESSAGE_Y_AXIS;
    	}
    	UTIL_LCD_SetFont(&Font16);
    	if(y_text_row < y_size)
    	{
    		UTIL_LCD_DisplayStringAt(TEXT_MESSAGE_X_AXIS, y_text_row, (uint8_t *) text, LEFT_MODE);
    		y_text_row += 20;
    	}
    }
#endif
	Log_Printf(LOG_LEVEL_INFO, "%s", text);
	printf("%s\n", text);

	if(init_threadx == true) tx_mutex_put(&lock_screen);
}

void StartScreenLcd_DumpVersionInfo(void)
{
	StartScreenLcd_WriteLine("Program: %s", SysLayer_BuildProgramName_GET());
	StartScreenLcd_WriteLine("Version: %s.%s.%s %s %s %s", SysLayer_BuildVersion_Major_GET(), SysLayer_BuildVersion_Minor_GET(), SysLayer_BuildVersion_Patch_GET(), SysLayer_BuildDate_GET(), SysLayer_BuildTime_GET(), SysLayer_BuildType_GET());
	StartScreenLcd_WriteLine("Git    : %s %s", SysLayer_BuildGitHash10_GET(), SysLayer_BuildGitBranch_GET());
}

void StartScreenLcd_DisplayLogo(void)
{
#if defined(PROG_TYPE_FSBL)
    uint32_t x_size;
    BSP_LCD_GetXSize(0, &x_size);
    UTIL_LCD_DrawBitmap(x_size - 300, 0, (uint8_t *)(XSPI_FLASH_PHY_ADDR(XSPI_OFFSET_FSBL_ASSETS + logo_tcs_OFFSET)));
#endif
#if defined(PROG_TYPE_APPLI)
    uint8_t * bmp = malloc(0x11000);
    if(bmp != NULL)
    {
        uint32_t num_read;
        MX_Filex_read_to_buffer(PATH_FILE_LOGO_TCS_BMP, bmp, 0x11000, &num_read);
        // NOTE: need wait here otherwise we get an excpetion
        // DONT KNOW WHY, what the race condition is
        tx_thread_sleep(TX_MS_TO_TICK(50));
#if defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
        /* Clean DCache starting from a 32 byte aligned address in 32 byte granularity */
        SCB_CleanDCache_by_Addr((void *)bmp, 0x11000);
#endif /* __DCACHE_PRESENT */
        uint32_t x_size;
        BSP_LCD_GetXSize(0, &x_size);
        UTIL_LCD_DrawBitmap(x_size - 300, 0, (uint8_t *)bmp);
        free(bmp);
    }
#endif
}

