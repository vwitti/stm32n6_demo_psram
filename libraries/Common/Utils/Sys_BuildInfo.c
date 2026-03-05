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

char * SysLayer_BuildType_GET(void)
{
#if defined(DEBUG)
	return "DEBUG";
#else
	return "RELEASE";
#endif
}

char * SysLayer_BuildProgramName_GET(void)
{
	return PROJECT_BUILD_NAME;
}

char * SysLayer_BuildVersion_Major_GET(void)
{
	return BUILD_VERSION_MAJOR;
}

char * SysLayer_BuildVersion_Minor_GET(void)
{
	return BUILD_VERSION_MINOR;
}

char * SysLayer_BuildVersion_Patch_GET(void)
{
	return BUILD_VERSION_PATCH;
}

char * SysLayer_BuildDate_GET(void)
{
	return BUILD_INFO_DATE;
}

char * SysLayer_BuildTime_GET(void)
{
	return BUILD_INFO_TIME;
}

char * SysLayer_BuildGitHash10_GET(void)
{
	return BUILD_INFO_GIT_HASH_FIRST10;
}

char * SysLayer_BuildGitBranch_GET(void)
{
	return BUILD_INFO_GIT_BRANCH;
}
