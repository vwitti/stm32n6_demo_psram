/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : extmem_manager.h
  * @version        : 1.0.0
  * @brief          : Header for external memory manager extmem_manager.c file.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IOSUBSYSTEM_IOSUBSYSTEM_THREAD__H__
#define __IOSUBSYSTEM_IOSUBSYSTEM_THREAD__H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdbool.h"

 // Cycle Time for sensor simulation
#define SENORESIM_CYCLE_TIME		20 // ms Every 20 ms sensor input are simulated

void IoSubSystem_ThreadInit(void);

void IoSubSystem_Simulation_Init(void);
void vSensorCom_SimulateSensorExecute(void);

#if !defined(FORTE_NO_SIMULATOR)

#include <pthread.h>

typedef struct {
  pthread_t thread;
  int use_realtime;         // 0/1
  int rt_priority;          // z.B. 20..80 (SCHED_FIFO)
} sim_thread_t;

int SensorSim_pthread_start(sim_thread_t *ctx, int use_realtime, int rt_priority);
int SensorSim_pthread_stop(sim_thread_t *ctx);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __IOSUBSYSTEM_IOSUBSYSTEM_THREAD__H__ */

