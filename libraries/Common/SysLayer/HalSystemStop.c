/*
 * HalThread.c
 *
 *  Created on: Nov 6, 2025
 *      Author: vw
 */

// Enable defined to trace module (must be above of Syslog/Syslog.h)
//#define TRACE_MODULE

#include "stm32n6xx_hal.h"
#include "HalBoard.h"

// Should be called from the highest priority task
void HAL_Thread_SystemStop(void)
{
	while(1)
	{
	uint32_t cnt=0;
	HAL_Board_Led_ERR(true);
	for(int i=0; i< 5000000;i++) {		cnt++;	}
	HAL_Board_Led_ERR(false);
	for(int i=0; i< 10000000;i++) {		cnt++;	}
	}
}
