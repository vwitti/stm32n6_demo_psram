/*
 * HalThread.c
 *
 *  Created on: Nov 6, 2025
 *      Author: vw
 */

// Enable defined to trace module (must be above of Syslog/Syslog.h)
//#define TRACE_MODULE

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "stm32n6xx_hal.h"
#include "tcsglobal/asg_evo.h"
#include "threadx/common/inc/tx_api.h"

#include "AsgAssert/AsgAssert.h"
#include "SysLog/Syslog.h"
#include "Utils/TxArray.h"
#include "HalBoard.h"
#include "HalThread.h"

typedef struct
{
	TX_THREAD *tx;						// Pointer to task structure
	tf_selfcheck_function fSelfCheck;	// Pointer to SelfCheck function
} tsTxTaskList;

static TxArray 			tx_ListOfThreads;
static tsTxTaskList		tx_TxTaskList[ASG_THREAD_MAX_NUM];
TRACE(static int log_chan;)

static void HAL_global_stack_error_handler(TX_THREAD *tx)
{
	(void)tx;
	//HAL_Thread_SystemStop();
}

void HAL_Thread_Init(void)
{
	UINT ret;

	/* Register the "HAL_global_stack_error_handler" function with ThreadX
	so that thread stack errors can be handled by the application. */
	tx_thread_stack_error_notify(HAL_global_stack_error_handler);
	/* Create private log channel */
	TRACE(log_chan = Log_ChannelRegister("HALThread",LOG_LEVEL_TRACE, LOG_SINK_UART);)
	/* Create List to hold Task List */
	ret = TxArray_Init(&tx_ListOfThreads, "HAL_TaskList", &tx_TxTaskList, sizeof(tsTxTaskList), ASG_THREAD_MAX_NUM);
	ASG_ASSERT(ret == TX_SUCCESS);
}

void HAL_Thread_Stop(void)
{

	for(;;)
	{
		HAL_Board_Led_ERR(true);
		tx_thread_sleep(TX_MS_TO_TICK(100));
		HAL_Board_Led_ERR(false);
		tx_thread_sleep(TX_MS_TO_TICK(100));
	}
}

char * HAL_Thread_GetPrioString(uint32_t prio)
{
    switch (prio) {
        case PRIO_SAFETY:            return "SAFETY";
        case PRIO_INPUT_EVENT:       return "INPUT_EV";
        case PRIO_INPUT_TIMESLICE:   return "INPUT_TS";
        case PRIO_CONTROL_EVENT:     return "CTRL_EV";
        case PRIO_CONTROL_TIMESLICE: return "CTRL_TS";
        case PRIO_COMM_EVENT:        return "COMM_EV";
        case PRIO_COMM_TIMESLICE:    return "COMM_TS";
        case PRIO_DIAG:              return "DIAG";
        case PRIO_BACKGROUND:        return "BACKGROUND";
        case PRIO_IDLE:              return "IDLE";
    }
    return "???";
}

// This function changes the preemption threshold and the task prio, if only the task prio is changed
// and the preemption threshold is still higher priority it prevents other task from scheduling if threshold
// is used in a wrong manner
void HAL_Thread_Change_Prio(TX_THREAD * tx, uint32_t newprio)
{
	UINT ret;
	UINT old_prio;
	UINT curr_prio;

	tx_thread_info_get(tx, /* name */ NULL, /*state*/ NULL, /*run_count*/ NULL,
	                /*priority*/ &curr_prio, /*preemption_threshold*/ NULL, /*time_slice*/ NULL,
	                /*next_thread*/NULL, /**next_suspended_thread*/NULL);

	if(curr_prio != newprio)
	{
		ret = tx_thread_priority_change(tx, newprio, &old_prio);
		ASG_ASSERT(ret == TX_SUCCESS);
		ret = tx_thread_preemption_change(tx, newprio, &old_prio);
		ASG_ASSERT(ret == TX_SUCCESS);
	}
}

bool HAL_Thread_StackCheck(TX_THREAD * tx)
{
	bool ret = true;
#if defined(TX_ENABLE_STACK_CHECKING)
	ULONG stack_end   = (ULONG) tx->tx_thread_stack_end;
    ULONG stack_size    = tx->tx_thread_stack_size;
    ULONG stack_highest = (ULONG) tx->tx_thread_stack_highest_ptr;
    ULONG used_stack = stack_end - stack_highest;
    ULONG usage_percent = (used_stack * 100) / stack_size;

    TRACE(Log_ChPrintf(log_chan,  LOG_LEVEL_TRACE, "Thread: %s Stack:%lu Used:%lu (%lu%%)", tx->tx_thread_name, stack_size, used_stack, usage_percent);)
    if(usage_percent >= ASG_THREAD_THRESHOLD_STACK_OVERFLOW)
    {
    	Log_Printf(LOG_LEVEL_ERROR, "Thread:%s Stack:%lu Used:%lu (%lu%%) ##OVERFLOW##", tx->tx_thread_name, stack_size, used_stack, usage_percent);
    	ret = false;
    }
    else if(usage_percent >= ASG_THREAD_THRESHOLD_STACK_WARN)
    {
    	Log_Printf(LOG_LEVEL_WARN, "Thread:%s Stack:%lu Used:%lu (%lu%%) WARN", tx->tx_thread_name, stack_size, used_stack, usage_percent);
    }
#endif
    return ret;
}

UINT HAL_Thread_Create(
		TX_THREAD *thread_ptr,
		CHAR *name_ptr,
		VOID (*entry_function)(ULONG entry_input),
		ULONG entry_input,
		VOID *stack_start,
		ULONG stack_size,
		UINT priority,
		UINT preempt_threshold,
		ULONG time_slice,
		UINT auto_start,
		bool (*selfcheck_function)(VOID))
{
	tsTxTaskList elem;

	if(selfcheck_function == NULL) return TX_PTR_ERROR;

	if(TxArray_Count(&tx_ListOfThreads) < ASG_THREAD_MAX_NUM)
	{
		elem.tx         = thread_ptr;
		elem.fSelfCheck = selfcheck_function;

		UINT ret = TxArray_Add(&tx_ListOfThreads, &elem);
		ASG_ASSERT(ret == TX_SUCCESS);
		ret = tx_thread_create(thread_ptr,
				name_ptr,
				entry_function,
				entry_input,
				stack_start,
				stack_size,
				priority,
				preempt_threshold,
				time_slice,
				auto_start);
		ASG_ASSERT(ret == TX_SUCCESS);
		return ret;
	}
	return TX_NO_MEMORY;
}

bool HAL_Thread_CyclicStackCheck()
{
	size_t count = TxArray_Count(&tx_ListOfThreads);
	size_t iter;
	tsTxTaskList elem;
	bool res_stackcheck = true;

	//Log_Printf(LOG_LEVEL_INFO, "HAL_Thread_CyclicStackCheck called.");

	for(iter = 0; iter < count; iter++)
	{
		UINT ret = TxArray_Get(&tx_ListOfThreads, iter, &elem);
		if(ret == TX_SUCCESS)
		{
			res_stackcheck &= HAL_Thread_StackCheck(elem.tx);
		}
	}
	return res_stackcheck;
}

bool HAL_Thread_CyclicSelfCheck()
{
	size_t count = TxArray_Count(&tx_ListOfThreads);
	size_t iter;
	tsTxTaskList elem;
	bool res_selfcheck = true;

	//Log_Printf(LOG_LEVEL_INFO, "HAL_Thread_CyclicSelfCheck called.");

	for(iter = 0; iter < count; iter++)
	{
		UINT ret = TxArray_Get(&tx_ListOfThreads, iter, &elem);
		if(ret == TX_SUCCESS)
		{
			res_selfcheck &= (elem.fSelfCheck)();
		}
	}
	return res_selfcheck;
}
