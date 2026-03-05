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
#include "tcsglobal/asg_evo.h"
#include "STM32N6570-DK/stm32n6570_discovery.h"
#include "STM32N6570-DK/stm32n6570_discovery_lcd.h"
#include "threadx/common/inc/tx_api.h"
#include "netxduo/common/inc/nx_api.h"
#include "AsgAssert/AsgAssert.h"
#include "SysLayer/HalBoard.h"
#include "SysLayer/HalThread.h"
#include "SysLayer/HalSystemStop.h"
#include "SysLog/Syslog.h"
#include "Utils/Sys_BuildInfo.h"
#include "Inc/systemthreads.h"
#include "Common/Inc/Init/app_threadx.h"
#include "Common/Inc/Init/app_netxduo.h"
#include "Common/Inc/Init/sysmem.h"

/* Private variables ---------------------------------------------------------*/
static TX_THREAD tx_systemtest_thread;
static char tx_systemtest_thread_stack[ASG_THREAD_SYSTEMTEST_STACKSIZE];
static bool bTestTask_AllInitialTestsDone= false;

static bool SelfCheckASG_TestTask(void);
static void ThreadASG_TestTask(uint32_t thread_input);
static int32_t OTP_Check_High_Speed_XSPI(void);

// Check for correct setting in BSP LCD Driver. This settings are needed to display fonts correct, without DMA it seems to be very slow
static_assert(USE_DMA2D_TO_FILL_RGB_RECT == 1, "Check for correct setting in BSP LCD Driver, see also comments in files");
static_assert(USE_BSP_CPU_CACHE_MAINTENANCE == 1, "Check for correct setting in BSP LCD Driver, see also comments in files");

// We rely on 1 tick per 1 ms, so we check here
static_assert(TX_TIMER_TICKS_PER_SECOND == 1000, "TX_TIMER_TICKS_PER_SECOND is not 1000 (1ms per tick)");
static_assert(NX_IP_PERIODIC_RATE == 1000, "NX_IP_PERIODIC_RATE is not 1000 (1ms per tick)");

extern TX_THREAD tx_systeminit_thread;

/**
  * @brief  User OTP fuse Configuration
  *         The User Option Bytes are configured as follows :
  *            VDDIO_HSLV = 1 (enable the configuration of pads below 2.5V,
  *                            I/O speed otpmization at low-voltage allowed)
  *            XSPI1_HSLV = 1 (enable I/O XSPIM Port 1 high-speed option)
  *            XSPI2_HSLV = 1 (enable I/O XSPIM Port 2 high-speed option)
  *            Other User Option Bytes remain unchanged
  * @retval None
  */
static int32_t OTP_Check_High_Speed_XSPI(void)
{
  #define BSEC_HW_CONFIG_ID        124U
  #define BSEC_HWS_HSLV_VDDIO3     (1U<<15)
  #define BSEC_HWS_HSLV_VDDIO2     (1U<<16)

  uint32_t fuse_id;
  uint32_t bit_mask;
  uint32_t data;
  BSEC_HandleTypeDef sBsecHandler;
  int32_t retr = 0;

  Log_Printf(LOG_LEVEL_INFO, "OTP_Check_High_Speed_XSPI");

  sBsecHandler.Instance = BSEC;

  /* Read current value of fuse */
  fuse_id = BSEC_HW_CONFIG_ID;
  if (HAL_BSEC_OTP_Read(&sBsecHandler, fuse_id, &data) == HAL_OK)
  {
	  //Log_Printf(LOG_LEVEL_INFO, "Fuse: %d %08lX", BSEC_HW_CONFIG_ID, data);
      /* Check if bit has already been set */
      bit_mask = BSEC_HWS_HSLV_VDDIO3 | BSEC_HWS_HSLV_VDDIO2;
      ASG_ASSERT((data & bit_mask) == bit_mask);
  }
  else
  {
    /* Error  : Fuse read unsuccessful */
	Log_Printf(LOG_LEVEL_INFO, "Cant read fuse %d", retr);
    retr = -4;
  }
  return retr;
}

/* Implementation */
void BackGroundTestInit(void)
{
	/* Create other tasks */
	UINT ret = TX_SUCCESS;

	/* Create a testtask for playing around */
	ret = HAL_Thread_Create(&tx_systemtest_thread,
			ASG_THREAD_SYSTEMTEST_NAME,
			  ThreadASG_TestTask,
			  0,
			  tx_systemtest_thread_stack,
			  ASG_THREAD_SYSTEMTEST_STACKSIZE,
			  ASG_THREAD_SYSTEMTEST_PRIO,
			  ASG_THREAD_SYSTEMTEST_PRIO,
			  ASG_THREAD_SYSTEMTEST_TIMESLICE,
			  TX_AUTO_START,
			  SelfCheckASG_TestTask);
	ASG_ASSERT(ret == TX_SUCCESS);
}

bool BackGroundTestAllInitialTestsDone(void)
{
	return bTestTask_AllInitialTestsDone;
}

static void ASG_EVO_SelfCheck(void)
{
	bool ret = true;

	Log_Printf(LOG_LEVEL_INFO, "Running self check!");

	// Idle Part, call stack check for maintask direct here, it is the only task not created by HAL_Thread_Create and it does
	// not have a self check function
	ret &= HAL_Thread_StackCheck(&tx_systeminit_thread);
	ret &= HAL_Thread_CyclicStackCheck();
	ret &= HAL_Thread_CyclicSelfCheck();

	// Check memory pools (ThreadX, NetXDuo and FileX)
	for(teThreadXPoolId iter = eThreadXPoolId_Kernel; iter < eThreadXPoolId_Last; iter++ )
	{
		tsThreadXPoolInfo info;

		UINT txret = txret = App_ThreadX_GetPoolInfo(iter, &info);
		if((txret == TX_SUCCESS) && (info.susp != 0))
		{
			Log_Printf(LOG_LEVEL_WARN, "Pool: %15s, Out of Memory, %d Threads, First: %08X", info.name, info.susp, info.tx_thread);
		}
	}

	// Check NetXDuo Packet Pools
	for(teNetXDuoPacketPoolId iter = teNetXDuoPacketPoolId_Global; iter < teNetXDuoPacketPoolId_Last; iter++ )
	{
		tsNetXDuoPacketPoolInfo info;

		UINT txret = txret = App_NetXDuo_GetPacketPoolInfo(iter, &info);
		if((txret == TX_SUCCESS) && (info.empty_pool_suspensions != 0))
		{
			Log_Printf(LOG_LEVEL_WARN, "Pool: %15s, Out of Packets, Req:%d Susp:%d", info.name, info.empty_pool_requests, info.empty_pool_suspensions);
		}
	}

	// Check Heap Pool
	_dump_heap_info();

	// Stop if self check failed
	if(ret == false)
	{
		Log_Printf(LOG_LEVEL_ERROR, "!!! ERROR: SelfTest failed !!!");
#if defined(DEBUG)
		HAL_Thread_Change_Prio(&tx_systeminit_thread, PRIO_BACKGROUND);
		HAL_Thread_SystemStop();
#endif
	}
}

/**
  * @brief  Function implementing the tx_app_thread_entry thread.
  * @param  thread_input: Hardcoded to 0.
  * @retval None
  */
void ThreadASG_TestTask(uint32_t thread_input)
{
	int32_t res;

	Log_Printf(LOG_LEVEL_INFO, "ThreadASG_TestTask created.");

	// Check only during startup
	res = OTP_Check_High_Speed_XSPI();

	if(res == 0)
	{
		Log_Printf(LOG_LEVEL_INFO, "ThreadASG_TestTask: All Startup tests Done.");
		bTestTask_AllInitialTestsDone = true;
	}

	while (1)
	{
		ASG_EVO_SelfCheck();
		tx_thread_sleep(TX_MS_TO_TICK(20000));
	}
}

static bool SelfCheckASG_TestTask(void)
{
	//Log_Printf(LOG_LEVEL_INFO, "SelfCheckASG_TestTask done.");
	// Do your tests here, return false if tests fails
	return true;
}
