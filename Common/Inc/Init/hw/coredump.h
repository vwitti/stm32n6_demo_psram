/*
 * HalThread.h
 *
 *  Created on: Nov 6, 2025
 *      Author: vw
 */

#ifndef COMMON_SYSLAYER_COREDUMP_H_
#define COMMON_SYSLAYER_COREDUMP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

void printf_coredump(const char* fmt, ...);
void coredump_c_printf(void);
void coredump_store_values_c(uint32_t* sp, uint32_t exc_return);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_SYSLAYER_COREDUMP_H_ */
