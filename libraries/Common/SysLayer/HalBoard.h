/*
 * HalBoard.h
 *
 *  Created on: Nov 5, 2025
 *      Author: vw
 */

#ifndef COMMON_SYSLAYER_HALBOARD_H_
#define COMMON_SYSLAYER_HALBOARD_H_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void HAL_Board_Led_ERR(bool on);
void HAL_Board_Led_RUN(bool on);
uint32_t HAL_Board_Debug_UART_Write(void* handle, const uint8_t* data, uint32_t len, uint32_t timeout_ticks);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_SYSLAYER_HALBOARD_H_ */
