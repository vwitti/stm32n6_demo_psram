/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#ifndef __ASGEVO_BSP_N6570_DK_GPIO_H__
#define __ASGEVO_BSP_N6570_DK_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "stm32n6xx_hal.h"

// Uset LEDs Pins
#define LED_GREEN_Pin GPIO_PIN_1
#define LED_GREEN_GPIO_Port GPIOO
#define LED_RED_Pin GPIO_PIN_10
#define LED_RED_GPIO_Port GPIOG
#define USER_BUTTON_1_Pin GPIO_PIN_13
#define USER_BUTTON_1_GPIO_Port GPIOC

// Clock overdriver pin
#define VDDCORE_OVERDRIVE_Pin GPIO_PIN_4
#define VDDCORE_OVERDRIVE_GPIO_Port GPIOF


#define LCD_BL_Pin GPIO_PIN_6
#define LCD_BL_GPIO_Port GPIOQ



#define LCD_ON_OFF_Pin GPIO_PIN_3
#define LCD_ON_OFF_GPIO_Port GPIOQ
#define TP_IRQ_Pin GPIO_PIN_4
#define TP_IRQ_GPIO_Port GPIOQ
#define TP_IRQ_EXTI_IRQn EXTI4_IRQn
#define LCD_RESET_Pin GPIO_PIN_1
#define LCD_RESET_GPIO_Port GPIOE

#if STM32N6570_TOUCHGFX_ADD_GPIO == 1

#define MCU_ACTIVE_Pin GPIO_PIN_9
#define MCU_ACTIVE_GPIO_Port GPIOE
#define FRAME_RATE_Pin GPIO_PIN_0
#define FRAME_RATE_GPIO_Port GPIOD
#define RENDER_TIME_Pin GPIO_PIN_5
#define RENDER_TIME_GPIO_Port GPIOD
#define VSYNC_FREQ_Pin GPIO_PIN_6
#define VSYNC_FREQ_GPIO_Port GPIOF

#endif
/* USER CODE END Private defines */

void MX_GPIO_Init(void);
void MX_GPIO_Init_Appli(void);

/* Peripherals in "Schematics" */
void UserLed_Red_On();
void UserLed_Red_Off();
void UserLed_Green_On();
void UserLed_Green_Off();
bool UserButton1_Pressed();

#ifdef __cplusplus
}
#endif

#endif /* __ASGEVO_BSP_N6570_DK_GPIO_H__ */

