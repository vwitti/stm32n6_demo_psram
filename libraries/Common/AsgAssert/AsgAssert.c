/*
 * ThreadX Logger Skeleton — Channels + Rotation (10 files)
 * UART + Syslog (UDP, NetX Duo) + FileX sinks
 *
 * NEW:
 *  - Individuelle Log-Kanaele (z. B. "net", "sensor", "ui") mit eigenem Level & Sink-Maske.
 *  - API: Kanal registrieren, Level/Sinks je Kanal setzen, gezielt in Kanal loggen.
 *  - File-Rotation: bis zu 10 Dateien (app.log, app.1.log … app.9.log).
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "threadx/common/inc/tx_api.h"

#include "AsgAssert.h"
#include "SysLayer/HalThread.h"
#include "SysLog/Syslog.h"

void my_assert_fail(const char *expr,
                    const char *file,
                    int line,
                    const char *func)
{
	TX_THREAD* t = tx_thread_identify();
    UINT prio = t->tx_thread_priority;

	Log_Printf(LOG_LEVEL_ERROR, "!!! ASSERTION FAILED !!!");
	Log_Printf(LOG_LEVEL_ERROR, "Thread: %s (%d,%s)", t->tx_thread_name, prio, HAL_Thread_GetPrioString(prio));
	Log_Printf(LOG_LEVEL_ERROR, "%s,%s,%d", file, func, line);
	Log_Printf(LOG_LEVEL_ERROR, "Expression: %s", expr);
#if defined(DEBUG)
	Log_Printf(LOG_LEVEL_ERROR, "!!!  THREAD STOPPED  !!!");
	HAL_Thread_Stop();
	for(;;);
#endif
}
