
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
#ifndef __COMMON_UPDATE_FIRMWARE_UPDATE_H__
#define __COMMON_UPDATE_FIRMWARE_UPDATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

//define pathes for downloaded files
#define  LOCAL_PATH_UPDATE_LIST  	PATH_SEPARATOR FTP_DOWNLOAD_PATH PATH_SEPARATOR FILE_NAME_UPDATE_LIST

teStatus Update_CheckFtpServer(void);		// Open a connection to FTP Server
teStatus Update_CloseFtpServer(void);

teStatus Update_Check_FSBL_Bootloader(bool * is_update_needed);
teStatus Update_FSBL_Bootloader(void);

teStatus Update_Check_FSBL_Application(bool * is_update_needed);
teStatus Update_APPLI_Application(void);

teStatus Update_Check_TCSROMFS(bool * is_update_needed);
teStatus Update_TCSROMFS(void);

teStatus Update_Check_TOUCHGFX_Assets(bool * is_update_needed);
teStatus Update_TOUCHGFX_Assets(void);

#ifdef __cplusplus
}
#endif
#endif /* __COMMON_UPDATE_FIRMWARE_UPDATE_H__ */
