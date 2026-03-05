/*
 * HalThread.h
 *
 *  Created on: Nov 6, 2025
 *      Author: vw
 */

#ifndef COMMON_SYSLAYER_HALTHREAD_H_
#define COMMON_SYSLAYER_HALTHREAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "threadx/common/inc/tx_api.h"

typedef bool (*tf_selfcheck_function)(VOID);

void   HAL_Thread_Init(void);
void   HAL_Thread_Stop(void);
char * HAL_Thread_GetPrioString(uint32_t prio);
void   HAL_Thread_Change_Prio(TX_THREAD * tx, uint32_t newprio);
bool   HAL_Thread_StackCheck(TX_THREAD * tx);
bool   HAL_Thread_CyclicStackCheck();
bool   HAL_Thread_CyclicSelfCheck();
UINT   HAL_Thread_Create(TX_THREAD *thread_ptr, CHAR *name_ptr, VOID (*entry_function)(ULONG entry_input), ULONG entry_input,VOID *stack_start,
		ULONG stack_size, UINT priority, UINT preempt_threshold, ULONG time_slice, UINT auto_start, tf_selfcheck_function selfcheck_function);//bool (*selfcheck_function)(VOID));
#ifdef __cplusplus
}
#endif

#endif /* COMMON_SYSLAYER_HALTHREAD_H_ */
