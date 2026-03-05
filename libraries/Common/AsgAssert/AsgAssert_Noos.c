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

#include "AsgAssert.h"
#include "SysLayer/HalBoard.h"

void my_assert_fail(const char *expr,
                    const char *file,
                    int line,
                    const char *func)
{
#if defined(DEBUG)
	HAL_Board_Led_ERR(true);
	for(;;);
#endif
}
