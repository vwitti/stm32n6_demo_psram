/**
  ******************************************************************************
  * @file    main.c
  * @author  GPM Application Team
  * @brief   Main program body through the HAL API
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ASGEVO_COMMON_INIT_START_SCREEN_LCD_H__
#define __ASGEVO_COMMON_INIT_START_SCREEN_LCD_H__

#ifdef __cplusplus
extern "C" {
#endif

// What to show
#define START_SCREEN_ID_FSBL		(1)
#define START_SCREEN_ID_APPLI		(2)

/* Exported functions prototypes ---------------------------------------------*/
void StartScreenLcd_DumpVersionInfo(void);
void StartScreenLcd_init(uint8_t screen_id);
void StartScreenLcd_init_threadx(void);
void StartScreenLcd_WriteLine(const char* fmt, ...);
void StartScreenLcd_DisplayLogo(void);

#ifdef __cplusplus
}
#endif

#endif /* __ASGEVO_COMMON_INIT_START_SCREEN_LCD_H__ */
