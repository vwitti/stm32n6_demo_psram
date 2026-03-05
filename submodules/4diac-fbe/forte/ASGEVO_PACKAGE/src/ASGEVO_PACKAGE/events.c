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
#include <stdbool.h>
#include <stdint.h>
#if defined(FORTE_NO_SIMULATOR)
#include "Common/Inc/IoSubSystem/events.h"
#else
#include "forte/ASGEVO_PACKAGE/asgevo_package_config.h"
#include "forte/ASGEVO_PACKAGE/events.h"
#if USER_4DIAC_X86_FORTE_TOUCHGFX == 1
#include "forte/ASGEVO_PACKAGE/4diac/kv11_keys.h"
#include "forte/ASGEVO_PACKAGE/4diac/kv11_client.h"
#endif
#endif

static bool event_do_las;
static bool event_do_push;
static bool event_las_prewarn_active;
static uint16_t event_las_error;
static uint16_t counter;

void IoSubSystemEvents_Init(void)
{
	printf("IoSubSystemEvents_Init: Done\n");
	counter = 0;
	event_do_las = false;
	event_do_push = false;
	event_las_prewarn_active = 0;
	event_las_error = 0;
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	kv11_add_u32(KV11_ID_EVENTS_LAS_PREWARN_ACTIVE, event_las_prewarn_active);
	kv11_add_u32(KV11_ID_EVENTS_LAS_ERROR_CODE, event_las_error);
#endif
}

void IoSubSystemEvents_Modify(void)
{
	//printf("IoSubSystemEvents_Modify: Done\n");

	counter = (counter+1) % 6;
	switch(counter)
	{
	case 0: IoSubSystemEvents_Set_DoLAS(true);  break;
	case 1: IoSubSystemEvents_Set_DoLAS(false);  break;
	case 2: IoSubSystemEvents_Set_DoPUSH(true);  break;
	case 3: IoSubSystemEvents_Set_DoPUSH(false);  break;
	case 4: IoSubSystemEvents_Set_LAS_Prewarn(true);  break;
	case 5: IoSubSystemEvents_Set_LAS_Prewarn(false);  break;
	default: break;
	}
}

bool IoSubSystemEvents_Get_DoLAS()
{
	return event_do_las;
}

bool IoSubSystemEvents_Get_DoPUSH()
{
	return event_do_push;
}

bool IoSubSystemEvents_Get_LAS_Prewarn()
{
	return event_las_prewarn_active;
}

uint16_t IoSubSystemEvents_Get_LAS_Error()
{
	return event_las_error;
}

void IoSubSystemEvents_Set_DoLAS(bool val)
{
	//printf("IoSubSystemEvents_Set_DoLAS: %d\n", val);
	event_do_las = val;
}

void IoSubSystemEvents_Set_DoPUSH(bool val)
{
	//printf("IoSubSystemEvents_Set_DoPUSH: %d\n", val);
	event_do_push = val;
}

void IoSubSystemEvents_Set_LAS_Prewarn(bool val)
{
	//printf("IoSubSystemEvents_Set_LAS_Prewarn: %d\n", val);
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(event_las_prewarn_active != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_EVENTS_LAS_PREWARN_ACTIVE, val);
	}
#endif
	event_las_prewarn_active = val;
}

void IoSubSystemEvents_Set_LAS_Error(uint16_t errcode)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(event_las_error != errcode)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_EVENTS_LAS_ERROR_CODE, errcode);
	}
#endif
	event_las_error = errcode;
}


