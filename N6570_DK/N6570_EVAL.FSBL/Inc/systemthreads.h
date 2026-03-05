/**
  ******************************************************************************
  * @file    app_threadx.h
  * @author  MCD Application Team
  * @brief   ThreadX applicative header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INC_SYSTEMTHREADS_H
#define __INC_SYSTEMTHREADS_H

#ifdef __cplusplus
 extern "C" {
#endif

#define ASG_THREAD_SYSTEMINIT_NAME			"SystemInit_Thread"
#define ASG_THREAD_SYSTEMINIT_PRIO			PRIO_BACKGROUND
#define ASG_THREAD_SYSTEMINIT_TIMESLICE		TIME_SLICE_BACKGROUND
#define ASG_THREAD_SYSTEMINIT_STACKSIZE		3072

#define ASG_THREAD_SYSTEMTEST_NAME			"SystemTest_Thread"
#define ASG_THREAD_SYSTEMTEST_PRIO			PRIO_BACKGROUND
#define ASG_THREAD_SYSTEMTEST_TIMESLICE		TIME_SLICE_BACKGROUND
#define ASG_THREAD_SYSTEMTEST_STACKSIZE		1792

/* Includes ------------------------------------------------------------------*/
 // One of the rare case of extern, needed here for system setup to create context of main task
 extern TX_THREAD tx_systemthread_init;
 void ThreadASG_SystemInit(uint32_t arg);

void BackGroundTestInit(void);
bool BackGroundTestAllInitialTestsDone(void);

#ifdef __cplusplus
}
#endif

 #endif /* __INC_SYSTEMTHREADS_H */
