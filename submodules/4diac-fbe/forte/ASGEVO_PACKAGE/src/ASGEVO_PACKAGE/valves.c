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
#include "stm32n6xx.h"
#include "Common/Inc/IoSubSystem/valves.h"
#else
#include "forte/ASGEVO_PACKAGE/asgevo_package_config.h"
#include "forte/ASGEVO_PACKAGE/valves.h"
#if USER_4DIAC_X86_FORTE_TOUCHGFX == 1
#include "forte/ASGEVO_PACKAGE/4diac/kv11_keys.h"
#include "forte/ASGEVO_PACKAGE/4diac/kv11_client.h"
#endif
#endif

static bool valve_lower;
static bool valve_set;
static bool valve_pull;
static bool valve_push;
static bool valve_pull_creep;
static bool valve_baselift_extend;
static bool valve_baselift_retract;
static bool valve_stabcyl_extend;
static bool valve_stabcyl_retract;
static uint16_t counter;

void IoSubSystemValves_Init(void)
{
	printf("IoSubSystemValves_Init: Done\n");
	counter = 0;
	valve_lower = false;
	valve_set = false;
	valve_pull = false;
	valve_push = false;
	valve_pull_creep = false;
	valve_baselift_extend = false;
	valve_baselift_retract = false;
	valve_stabcyl_extend = false;
	valve_stabcyl_retract = false;
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	kv11_add_u32(KV11_ID_VALVE_LOWER, valve_lower);
	kv11_add_u32(KV11_ID_VALVE_SET, valve_set);
	kv11_add_u32(KV11_ID_VALVE_PULL, valve_pull);
	kv11_add_u32(KV11_ID_VALVE_PUSH, valve_push);
	kv11_add_u32(KV11_ID_VALVE_PULL_CREEP, valve_pull_creep);
	kv11_add_u32(KV11_ID_VALVE_BASELIFT_EXT, valve_baselift_extend);
	kv11_add_u32(KV11_ID_VALVE_BASELIFT_RET, valve_baselift_retract);
	kv11_add_u32(KV11_ID_VALVE_STABCYL_EXT, valve_stabcyl_extend);
	kv11_add_u32(KV11_ID_VALVE_STABCYL_RET, valve_stabcyl_retract);
#endif
}

void IoSubSystemValves_Modify(void)
{
	//printf("IoSubSystemValves_Modify: Done\n");

	counter = (counter+1) % 18;
	switch(counter)
	{
	case 0: IoSubSystemValves_SetValve_Lowering(true);  break;
	case 1: IoSubSystemValves_SetValve_Lowering(false);  break;
	case 2: IoSubSystemValves_SetValve_Setting(true);  break;
	case 3: IoSubSystemValves_SetValve_Setting(false);  break;
	case 4: IoSubSystemValves_SetValve_PullShield(true);  break;
	case 5: IoSubSystemValves_SetValve_PullShield(false);  break;
	case 6: IoSubSystemValves_SetValve_PushShield(true);  break;
	case 7: IoSubSystemValves_SetValve_PushShield(false);  break;
	case 8: IoSubSystemValves_SetValve_BaseLiftExtend(true);  break;
	case 9: IoSubSystemValves_SetValve_BaseLiftExtend(false);  break;
	case 10: IoSubSystemValves_SetValve_BaseLiftRetract(true);  break;
	case 11: IoSubSystemValves_SetValve_BaseLiftRetract(false);  break;
	case 12: IoSubSystemValves_SetValve_StabCylExtend(true);  break;
	case 13: IoSubSystemValves_SetValve_StabCylExtend(false);  break;
	case 14: IoSubSystemValves_SetValve_StabCylRetract(true);  break;
	case 15: IoSubSystemValves_SetValve_StabCylRetract(false);  break;
	case 16: IoSubSystemValves_SetValve_PullCreepAdvance(true);  break;
	case 17: IoSubSystemValves_SetValve_PullCreepAdvance(false);  break;
	default: break;
	}
}

bool IoSubSystemValves_GetValve_Lowering()
{
	return valve_lower;
}
bool IoSubSystemValves_GetValve_Setting()
{
	return valve_set;
}

bool IoSubSystemValves_GetValve_PullShield()
{
	return valve_pull;
}

bool IoSubSystemValves_GetValve_PushShield()
{
	//printf("IoSubSystemValves_GetValve_PushShield: %d\n", valve_push);
	return valve_push;
}

bool IoSubSystemValves_GetValve_PullCreepAdvance()
{
	return valve_pull_creep;
}

bool IoSubSystemValves_GetValve_BaseLiftExtend()
{
	return valve_baselift_extend;
}

bool IoSubSystemValves_GetValve_BaseLiftRetract()
{
	return valve_baselift_retract;
}

bool IoSubSystemValves_GetValve_StabCylExtend()
{
	return valve_stabcyl_extend;
}

bool IoSubSystemValves_GetValve_StabCylRetract()
{
	return valve_stabcyl_retract;
}

void IoSubSystemValves_SetValve_Lowering(bool val)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(valve_lower != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_VALVE_LOWER, val);
	}
#endif
	valve_lower = val;
}

void IoSubSystemValves_SetValve_Setting(bool val)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(valve_set != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_VALVE_SET, val);
	}
#endif
	valve_set = val;
}

void IoSubSystemValves_SetValve_PullShield(bool val)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(valve_pull != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_VALVE_PULL, val);
	}
#endif
	valve_pull = val;
}

//uint32_t start_tick;
//uint32_t end_tick;

void IoSubSystemValves_SetValve_PushShield(bool val)
{
#if 0
	if(val == true)
	{
		start_tick = HAL_GetTick();
	}
	if(val == false)
	{
		end_tick = HAL_GetTick();
		printf("diff=%ld\n", end_tick - start_tick);
	}
#endif
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(valve_push != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_VALVE_PUSH, val);
	}
#endif
	valve_push = val;
}

void IoSubSystemValves_SetValve_PullCreepAdvance(bool val)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(valve_pull_creep != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_VALVE_PULL_CREEP, val);
	}
#endif
	valve_pull_creep = val;
}

void IoSubSystemValves_SetValve_BaseLiftExtend(bool val)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(valve_baselift_extend != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_VALVE_BASELIFT_EXT, val);
	}
#endif
	valve_baselift_extend = val;
}

void IoSubSystemValves_SetValve_BaseLiftRetract(bool val)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(valve_baselift_retract != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_VALVE_BASELIFT_RET, val);
	}
#endif
	valve_baselift_retract = val;
}

void IoSubSystemValves_SetValve_StabCylExtend(bool val)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(valve_stabcyl_extend != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_VALVE_STABCYL_EXT, val);
	}
#endif
	valve_stabcyl_extend = val;
}

void IoSubSystemValves_SetValve_StabCylRetract(bool val)
{
#if !defined(FORTE_NO_SIMULATOR) && (USER_4DIAC_X86_FORTE_TOUCHGFX == 1)
	if(valve_stabcyl_retract != val)
	{
		// Send to remote display
		kv11_add_u32(KV11_ID_VALVE_STABCYL_RET, val);
	}
#endif
	valve_stabcyl_retract = val;
}

