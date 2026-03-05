/*
 * asg_evo.h
 *
 *  Created on: Nov 5, 2025
 *      Author: vw
 */

#ifndef TCSGLOBAL_ASG_EVO_H_
#define TCSGLOBAL_ASG_EVO_H_

#include "assert.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ASG_THREAD_MAX_NUM		32	// Maximum number of thread allowed in system

// Priority Scheme (see wiki)
#define PRIO_SAFETY          	1	// EVENT DRIVEN ONLY Ueberwachung von Not-Aus, Sicherheitskreisen
#define PRIO_INPUT_EVENT     	2	// EVENT DRIVEN ONLY Erfassen digitaler und analoger Eingaenge (Sensorik)
#define PRIO_INPUT_TIMESLICE 	3
#define PRIO_CONTROL_EVENT   	4	// EVENT DRIVEN ONLY Steuerungs- und Regelalgorithmen (z. B. PID, Ablaufsteuerung)
#define PRIO_CONTROL_TIMESLICE	5
#define PRIO_COMM_EVENT        	6	// EVENT DRIVEN ONLY Austausch mit Feldbussen (z. B. PROFINET, EtherCAT, CANopen)
#define PRIO_COMM_TIMESLICE		7
#define PRIO_DIAG            	8	// Ueberwachung von Komponenten, Fehlerspeicher, Statusmeldungen
#define PRIO_BACKGROUND      	10  // Speichern von Prozessdaten und Ereignissen (Flash, SD, Netzwerk), Aktualisierung von Displays, Bedienpanel, Webserver, Logging
#define PRIO_IDLE            	11  // gleiche Prioritaet, andere CPU-Zeit

// Default timeslices (shorter timeslices may increase overhead)
#define TIME_SLICE_BACKGROUND	TX_MS_TO_TICK(20)	// [ms]

// Threadx macro to convert ms to ticks
// If we set one tick to a ms, then all system calls, e.g. tx_thread_sleep equals to a ms
#define TX_MS_TO_TICK(x)		(x)
#define TX_TICK_1MS				(1)		// Tick for 1 ms

// STACK HANDLING
#define ASG_THREAD_THRESHOLD_STACK_WARN			(75)		/* [%] Stack nearly full */
#define ASG_THREAD_THRESHOLD_STACK_OVERFLOW		(90)		/* [%] Stack is overflowed */

#ifdef __cplusplus
}
#endif

#endif /* TCSGLOBAL_ASG_EVO_H_ */
