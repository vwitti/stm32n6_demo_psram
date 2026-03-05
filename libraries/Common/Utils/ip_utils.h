/*
 * ip_utils.h
 *
 *  Created on: Nov 6, 2025
 *      Author: vw
 */

#ifndef COMMON_UTILS_IP_UTILS_H_
#define COMMON_UTILS_IP_UTILS_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t ip_utils_convert_ipstr_to_uint32(const char *ip_str);
void ip_utils_convert_uint32_to_ipstr(uint32_t ipaddr, char *ip_str, size_t ip_str_size);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_UTILS_IP_UTILS_H_ */
