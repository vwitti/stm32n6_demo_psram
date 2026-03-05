/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.h
  * @author  MCD Application Team
  * @brief   ThreadX applicative header file
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
#ifndef __COMMON_TEST_BSD_TCP_ECHO_H
#define __COMMON_TEST_BSD_TCP_ECHO_H

#ifdef __cplusplus
 extern "C" {
#endif

int demo_bsd_tcp_echo_client_main(const char *prog, const char *server_ip, const char *port);
int demo_bsd_tcp_echo_server_main(const char *prog, const char *port);

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_TEST_BSD_TCP_ECHO_H */
