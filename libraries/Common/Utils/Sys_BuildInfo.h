/*
 * HalBoard.h
 *
 *  Created on: Nov 5, 2025
 *      Author: vw
 */

#ifndef COMMON_UTILS_SYS_BUILDINFO_H_
#define COMMON_UTILS_SYS_BUILDINFO_H_

#ifdef __cplusplus
extern "C" {
#endif

char * SysLayer_BuildType_GET(void);
char * SysLayer_BuildProgramName_GET(void);
char * SysLayer_BuildVersion_Major_GET(void);
char * SysLayer_BuildVersion_Minor_GET(void);
char * SysLayer_BuildVersion_Patch_GET(void);
char * SysLayer_BuildDate_GET(void);
char * SysLayer_BuildTime_GET(void);
char * SysLayer_BuildGitHash10_GET(void);
char * SysLayer_BuildGitBranch_GET(void);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_UTILS_SYS_BUILDINFO_H_ */
