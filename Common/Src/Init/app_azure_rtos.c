/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_azure_rtos.c
  * @author  MCD Application Team
  * @brief   app_azure_rtos application implementation file
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
#include "tcsglobal/asg_evo.h"
#include "stm32n6xx_hal.h"
#include "SysLog/Syslog.h"
#include "BSP/Config/Middleware/middleware_config.h"
#include "Common/Inc/Init/error_handler.h"
#include "Common/Inc/Init/app_threadx.h"
#include "Common/Inc/Init/app_netxduo.h"
#include "TouchGFX/App/app_touchgfx.h"
#include "Inc/main.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#if (USE_STATIC_ALLOCATION == 1)

__ALIGN_BEGIN static UCHAR tx_byte_pool_buffer[TX_APP_MEM_POOL_SIZE] __ALIGN_END;
static TX_BYTE_POOL tx_app_byte_pool;

// Buffer for touch GFX
#if PROJECT_OS_USE_TOUCHGFX_LIB == 1
__ALIGN_BEGIN static UCHAR touchgfx_byte_pool_buffer[TOUCHGFX_APP_MEM_POOL_SIZE] __ALIGN_END;
static TX_BYTE_POOL touchgfx_app_byte_pool;
#endif

#if PROJECT_OS_FILESYSTEM == 1
__ALIGN_BEGIN static UCHAR fx_byte_pool_buffer[FX_APP_MEM_POOL_SIZE] __ALIGN_END;
static TX_BYTE_POOL fx_app_byte_pool;
#endif

__attribute__((section(".NetXPoolSection")))
__ALIGN_BEGIN static UCHAR nx_byte_pool_buffer[NX_APP_MEM_POOL_SIZE] __ALIGN_END;
static TX_BYTE_POOL nx_app_byte_pool;

#endif

/* Private function prototypes -----------------------------------------------*/

TX_BYTE_POOL * NX_GetBytePoolDesc(void)
{
	return &nx_app_byte_pool;
}

#if PROJECT_OS_FILESYSTEM == 1
TX_BYTE_POOL * FX_GetBytePoolDesc(void)
{
	return &fx_app_byte_pool;
}
#endif

/**
  * @brief  Define the initial system.
  * @param  first_unused_memory : Pointer to the first unused memory
  * @retval None
  */
VOID tx_application_define(VOID *first_unused_memory)
{
  /* USER CODE BEGIN  tx_application_define_1*/

  /* USER CODE END  tx_application_define_1 */
#if (USE_STATIC_ALLOCATION == 1)



	  UINT status = TX_SUCCESS;
	  VOID *memory_ptr;

		////////////////////////////////// THREADX /////////////////////////////////////
		status = tx_byte_pool_create(&tx_app_byte_pool, "ThreadX_Pool", tx_byte_pool_buffer, TX_APP_MEM_POOL_SIZE);
	    if(status != TX_SUCCESS)
	    {
	    	Error_Handler("Threadx: No memory pool");
	    }

	    ////////////////////////////////// TOUCHGFX  /////////////////////////////////////
#if PROJECT_OS_USE_TOUCHGFX_LIB == 1
	    status = tx_byte_pool_create(&touchgfx_app_byte_pool, "TouchGFX App memory pool", touchgfx_byte_pool_buffer, TOUCHGFX_APP_MEM_POOL_SIZE);
		if(status != TX_SUCCESS)
		{
			Error_Handler("TouchGFX: No memory pool");
		}
#endif

#if PROJECT_OS_FILESYSTEM == 1
	    //////////////////////////////////// FILEX //////////////////////////////////////
	    status = tx_byte_pool_create(&fx_app_byte_pool, "FileX_Pool", fx_byte_pool_buffer, FX_APP_MEM_POOL_SIZE);
		if(status != TX_SUCCESS)
		{
			Error_Handler("FileX: No memory pool");
		}
#endif
	    ////////////////////////////////// NETXDUO STACK /////////////////////////////////////
	    status = tx_byte_pool_create(&nx_app_byte_pool, "NetXDuo_Pool", nx_byte_pool_buffer, NX_APP_MEM_POOL_SIZE);
	    if(status != TX_SUCCESS)
	    {
	    	Error_Handler("NetXDuo: No memory pool");
	    }


	    // Call init for ThreadX Kernel
	    memory_ptr = (VOID *)&tx_app_byte_pool;
	    status = App_ThreadX_Init(memory_ptr);
	    if (status != TX_SUCCESS)
	    {
	    	Error_Handler("ThreadX: Kernel Init fail");
	    }

#if PROJECT_OS_USE_TOUCHGFX_LIB == 1
	    // Call init for touchGFX
	    memory_ptr = (VOID *)&touchgfx_app_byte_pool;
	    status = MX_TouchGFX_Init(memory_ptr);
	    if (status != TX_SUCCESS)
	    {
	    	Error_Handler("TouchGFX: Stack Init fail");
	    }
#endif

	    // MUST BE BEFORE NetXduo it self
	    status = MX_NetXDuo_Init(&nx_app_byte_pool);
	    if(status != TX_SUCCESS)
	    {
	    	Error_Handler("NetXDuo: Stack Init fail");
	    }

#else
/*
 * Using dynamic memory allocation requires to apply some changes to the linker file.
 * ThreadX needs to pass a pointer to the first free memory location in RAM to the tx_application_define() function,
 * using the "first_unused_memory" argument.
 * This require changes in the linker files to expose this memory location.
 * For EWARM add the following section into the .icf file:
     place in RAM_region    { last section FREE_MEM };
 * For MDK-ARM
     - either define the RW_IRAM1 region in the ".sct" file
     - or modify the line below in "tx_initialize_low_level.S to match the memory region being used
        LDR r1, =|Image$$RW_IRAM1$$ZI$$Limit|

 * For STM32CubeIDE add the following section into the .ld file:
     ._threadx_heap :
       {
          . = ALIGN(8);
          __RAM_segment_used_end__ = .;
          . = . + 64K;
          . = ALIGN(8);
        } >RAM_D1 AT> RAM_D1
    * The simplest way to provide memory for ThreadX is to define a new section, see ._threadx_heap above.
    * In the example above the ThreadX heap size is set to 64KBytes.
    * The ._threadx_heap must be located between the .bss and the ._user_heap_stack sections in the linker script.
    * Caution: Make sure that ThreadX does not need more than the provided heap memory (64KBytes in this example).
    * Read more in STM32CubeIDE User Guide, chapter: "Linker script".

 * The "tx_initialize_low_level.S" should be also modified to enable the "USE_DYNAMIC_MEMORY_ALLOCATION" flag.
 */

  /* USER CODE BEGIN DYNAMIC_MEM_ALLOC */
  (void)first_unused_memory;
  /* USER CODE END DYNAMIC_MEM_ALLOC */
#endif

}

UINT App_ThreadX_GetPoolInfo(teThreadXPoolId id, tsThreadXPoolInfo * info)
{
	UINT ret = TX_NO_INSTANCE;
	VOID *memory;
	char *name;
	ULONG available;
	ULONG fragments;
	ULONG num_suspended;
	TX_THREAD *   tx_thread_susp;

	if(info == NULL)
	{
		return TX_NO_INSTANCE;
	}
	switch(id)
	{
	case eThreadXPoolId_Kernel:
		memory = &tx_app_byte_pool;
		info->size = TX_APP_MEM_POOL_SIZE;
		break;
	case eThreadXPoolId_NetXDuo:
		info->size = NX_APP_MEM_POOL_SIZE;
		memory = &nx_app_byte_pool;
		break;
#if PROJECT_OS_FILESYSTEM == 1
	case eThreadXPoolId_FileX:
		info->size = FX_APP_MEM_POOL_SIZE;
		memory = &fx_app_byte_pool;
		break;
#endif
	default:
		return TX_NO_INSTANCE;
	}

	ret = tx_byte_pool_info_get(memory, &name, &available, &fragments, &tx_thread_susp, &num_suspended, NULL);
	if(ret == TX_SUCCESS)
	{
		info->name = name;
		info->free = available;
		info->fragments = fragments;
		info->tx_thread = tx_thread_susp;
		info->susp = num_suspended;
		//Log_Printf(LOG_LEVEL_DEBUG, "Pool:%15s, Size:%8lX, Free:%8lX, Frag:%4d, THREAD:%08X, Susp:%2d", info->name, info->size, info->free, info->fragments, info->tx_thread, info->susp);
		printf("Pool:%15s, Size:%8lX, Free:%8lX, Frag:%4ld, THREAD:%p, Susp:%2ld\n", info->name, info->size, info->free, info->fragments, info->tx_thread, info->susp);
	}
	return ret;
}


