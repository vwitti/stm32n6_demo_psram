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
#include <stdint.h>
#if defined(FORTE_NO_SIMULATOR)
#include "Common/Inc/IoSubSystem/sensors.h"
#else
#include "forte/ASGEVO_PACKAGE/asgevo_package_config.h"
#include "forte/ASGEVO_PACKAGE/sensors.h"
#if USER_4DIAC_X86_FORTE_TOUCHGFX == 1
#include "forte/ASGEVO_PACKAGE/4diac/kv11_keys.h"
#include "forte/ASGEVO_PACKAGE/4diac/kv11_client.h"
#endif
#endif

// Sensor Values
static uint16_t pressure_leg_left;
static uint16_t pressure_leg_right;
static uint16_t ramstroke;

void IoSubSystemSensor_Init(void)
{
	printf("IoSubSystemSensor_Init: Done\n");
	pressure_leg_left  = 500; // bar
	pressure_leg_right = 500;
	ramstroke          = 90;
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	kv11_add_u32(KV11_ID_SENSOR_PRESSURE_LEG_LEFT, pressure_leg_left);
	kv11_add_u32(KV11_ID_SENSOR_PRESSURE_LEG_RIGHT, pressure_leg_right);
	kv11_add_u32(KV11_ID_SENSOR_RAM_STROKE, ramstroke);
#endif
}

void IoSubSystemSensor_Modify(void)
{
	//printf("IoSubSystemSensor_Modify: Done\n");

	if(pressure_leg_left > 20)
	{
		pressure_leg_left--;
	}
	if(pressure_leg_right > 20)
	{
		pressure_leg_right--;
	}
	if(ramstroke > 0)
	{
		ramstroke--;
	}
}

uint16_t IoSubSystemSensor_GetPressureLeft()
{
	return pressure_leg_left;
}

uint16_t IoSubSystemSensor_GetPressureRight()
{
	return pressure_leg_right;
}

uint16_t IoSubSystemSensor_GetRamStroke()
{
	return ramstroke;
}

void IoSubSystemSensor_SetPressureLeft(uint16_t val)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(pressure_leg_left != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_SENSOR_PRESSURE_LEG_LEFT, val);
	}
#endif
	pressure_leg_left = val;
}

void IoSubSystemSensor_SetPressureRight(uint16_t val)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(pressure_leg_right != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_SENSOR_PRESSURE_LEG_RIGHT, val);
	}
#endif
	pressure_leg_right = val;
}

void IoSubSystemSensor_SetRamStroke(uint16_t val)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(ramstroke != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_SENSOR_RAM_STROKE, val);
	}
#endif
	ramstroke = val;
}
