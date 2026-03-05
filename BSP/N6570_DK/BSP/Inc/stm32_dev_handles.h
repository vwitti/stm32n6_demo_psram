/**
  ******************************************************************************
  * @file    stm32_extmem_conf.h
  * @author  GPM Application Team
  * @brief   Header configuration for extmem module
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
#ifndef __ASGEVO_BSP_N6570_DK_DEV_HANDLES_H__
#define __ASGEVO_BSP_N6570_DK_DEV_HANDLES_H__

#ifdef __cplusplus
extern "C" {
#endif

// If NULL there is no USART Debug Handle
UART_HandleTypeDef * DebugUsartHandle_get(void);


#ifdef __cplusplus
}
#endif

#endif /* __ASGEVO_BSP_N6570_DK_DEV_HANDLES_H__ */
