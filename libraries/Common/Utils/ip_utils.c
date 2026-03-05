
/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include "ip_utils.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

//Chad
uint32_t ip_utils_convert_ipstr_to_uint32(const char *ip_str)
{
    unsigned int b1, b2, b3, b4;

    if (sscanf(ip_str, "%u.%u.%u.%u", &b1, &b2, &b3, &b4) != 4)
        return 0;

    return  (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}

void ip_utils_convert_uint32_to_ipstr(uint32_t ipaddr, char *ip_str, size_t ip_str_size)
{
	snprintf(ip_str, ip_str_size, "%ld.%ld.%ld.%ld", (ipaddr >> 24) & 0xff, (ipaddr >> 16) & 0xff, (ipaddr >> 8) & 0xff, ipaddr & 0xff);
}
