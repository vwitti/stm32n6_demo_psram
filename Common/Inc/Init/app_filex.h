
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_filex.h
  * @author  MCD Application Team
  * @brief   FileX applicative header file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __COMMON_INIT_APP_FILEX_H__
#define __COMMON_INIT_APP_FILEX_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tcsglobal/status_codes.h"
#include "fx_api.h"
#if defined(BOARD_TYPE_N6570_DK)
#include "BSP/Inc/fx_stm32_sd_driver.h"
#endif
#if defined(BOARD_TYPE_ASG_EVO)
#include "BSP/Inc/fx_stm32_mmc_driver.h"
#endif
#if defined (PROG_TYPE_APPLI)
#include "BSP/Inc/fx_stm32_xspi_memmapped_driver.h"
#include "BSP/Inc/fx_stm32_psram_memmapped_driver.h"
#endif
#if defined (PROG_TYPE_FSBL)
#include "BSP/Inc/fx_stm32_xspi_direct_driver.h"
#include "BSP/Inc/fx_stm32_psram_memmapped_driver.h"
#endif
/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
UINT MX_FileX_Init(VOID *memory_ptr);
UINT MX_FileX_Init_SD_Card(VOID *memory_ptr);
UINT MX_FileX_Init_ROM_DISK(VOID *memory_ptr);
TX_BYTE_POOL * FX_GetBytePoolDesc(void);
FX_MEDIA *  MX_FileX_GetMedia_MassStorage();
FX_MEDIA *  MX_FileX_GetMedia_RamDisk();
FX_MEDIA *  MX_FileX_GetMedia_TcsRomDisk(void);
UINT MX_FileX_Init_ROM_DISK_MM(VOID *memory_ptr);
UINT MX_Filex_read_to_buffer(CHAR *path, UCHAR *buffer, ULONG buffer_size, ULONG *out_file_size);
UINT MX_Filex_Get_Size(CHAR *path, ULONG * file_size);
UINT MX_FileX_Init_PSRAM_DISK(VOID *memory_ptr);
UINT MX_FileX_Init_PSRAM_DISK_MM(VOID *memory_ptr);
teStatus MX_FileX_Eval_Path(const char * path, FX_MEDIA ** media, char * filename, size_t filename_size);
FX_MEDIA * MX_FileX_Get_Media(const char * path);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* mount pathes */
#define PATH_SEPARATOR		"/"
#define PATH_MOUNT_MAX		(3)				// maximum length of mount path
#define PATH_TCSROMFS		"rom"			// TCSROM Disk in flash
#define PATH_MMC			"mmc"           // SD-Card or eMMC disk
#define PATH_RAMDISK        "rd"            // RAM Disk on PSRAM
#define PATH_USB            "usb"           // USB storage

#define FTP_DOWNLOAD_PATH		PATH_RAMDISK	// Path where files from FTP Server are stored
#define MX_File_FtpDownload		MX_FileX_GetMedia_RamDisk

#define FILEX_FILENAME_SIZE		(80)		// Default filename size

#define PATH_FILE_LOGO_TCS_BMP		PATH_SEPARATOR PATH_TCSROMFS PATH_SEPARATOR "logo_tcs.bmp"
#define PATH_FILE_TCSROM_FS_CRC32	PATH_SEPARATOR PATH_TCSROMFS PATH_SEPARATOR "tcsromfs.crc"
#define PATH_FILE_TOUCHGFX_CRC32	PATH_SEPARATOR PATH_TCSROMFS PATH_SEPARATOR "touchgfx.crc"
#define PATH_FILE_IP_CONFIG_FILE	PATH_SEPARATOR PATH_TCSROMFS PATH_SEPARATOR USER_IP_CONFIG_FILE

/* Main thread Name */
#ifndef FX_APP_THREAD_NAME
  #define FX_APP_THREAD_NAME "FileX app thread"
#endif

/* Main thread time slice */
#ifndef FX_APP_THREAD_TIME_SLICE
  #define FX_APP_THREAD_TIME_SLICE TIME_SLICE_BACKGROUND
#endif

/* Main thread auto start */
#ifndef FX_APP_THREAD_AUTO_START
  #define FX_APP_THREAD_AUTO_START TX_AUTO_START
#endif

/* Main thread preemption threshold */
#ifndef FX_APP_PREEMPTION_THRESHOLD
  #define FX_APP_PREEMPTION_THRESHOLD FX_APP_THREAD_PRIO
#endif

/* fx sd volume name */
#ifndef FX_SD_VOLUME_NAME
  #define FX_SD_VOLUME_NAME "SD_DISK"
#endif

/* fx eMMC volume name */
#ifndef FX_EMMC_VOLUME_NAME
  #define FX_EMMC_VOLUME_NAME "EMMC_DISK"
#endif

/* fx sd number of FATs */
//#ifndef FX_SD_NUMBER_OF_FATS
//  #define FX_SD_NUMBER_OF_FATS                1
//#endif

/* fx sd Hidden sectors */
//#ifndef FX_SD_HIDDEN_SECTORS
//  #define FX_SD_HIDDEN_SECTORS               0
//#endif

#ifdef __cplusplus
}
#endif
#endif /* __COMMON_INIT_APP_FILEX_H__ */
