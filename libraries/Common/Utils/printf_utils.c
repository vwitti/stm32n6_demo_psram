
/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include "printf_utils.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


// chad
void print_hex(const uint8_t *data, size_t len, size_t bytes_per_line)
{
    if (!data || bytes_per_line == 0) {
        return;
    }

    printf("%08lX\n", (uint32_t) data);
    printf("---------------------------------------------------\n");
    for (size_t i = 0; i < len; i++) {

        // Neue Zeile am Zeilenanfang
        if (i % bytes_per_line == 0) {
            printf("%04X: ", i);
        }

        printf("%02X ", data[i]);

        // Zeilenende
        if ((i + 1) % bytes_per_line == 0) {
            printf("\n");
        }
    }

    // Falls die letzte Zeile nicht voll war → newline
    if (len % bytes_per_line != 0) {
        printf("\n");
    }
}

// chad
void print_hex_ascii(const uint8_t *data, size_t len, size_t bytes_per_line)
{
    if (!data || bytes_per_line == 0) {
        return;
    }

    printf("%08lX\n", (uint32_t) data);
    printf("---------------------------------------------------\n");
    for (size_t i = 0; i < len; i += bytes_per_line) {

        printf("%04X: ", i);

        // Hex-Teil
        for (size_t j = 0; j < bytes_per_line; j++) {
            if (i + j < len)
                printf("%02X ", data[i + j]);
            else
                printf("   "); // Leerraum für unvollständige Zeile
        }

        printf(" | ");

        // ASCII-Teil
        for (size_t j = 0; j < bytes_per_line; j++) {
            if (i + j < len) {
                uint8_t c = data[i + j];
                printf("%c", (c >= 32 && c <= 126) ? c : '.');
            } else {
                printf(" ");
            }
        }

        printf("\n");
    }
}


