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
#ifndef __COMMON_INC_TEST_APPLI_EXCEPTION_STACK_TEST_H
#define __COMMON_INC_TEST_APPLI_EXCEPTION_STACK_TEST_H


#ifdef __cplusplus
 extern "C" {
#endif

void exception_stack_test(void);
void exception_stack_test_level1(void);
void exception_stack_test_level2(void);
void exception_stack_test_level3(void);

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_INC_TEST_APPLI_EXCEPTION_STACK_TEST_H */
