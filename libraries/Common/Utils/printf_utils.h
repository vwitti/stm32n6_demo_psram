/*
 * ip_utils.h
 *
 *  Created on: Nov 6, 2025
 *      Author: vw
 */

#ifndef COMMON_UTILS_PRINTF_UTILS_H_
#define COMMON_UTILS_PRINTF_UTILS_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void print_hex(const uint8_t *data, size_t len, size_t bytes_per_line);
void print_hex_ascii(const uint8_t *data, size_t len, size_t bytes_per_line);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_UTILS_PRINTF_UTILS_H_ */
