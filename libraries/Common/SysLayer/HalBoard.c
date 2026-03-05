/*
 * ThreadX Logger Skeleton — Channels + Rotation (10 files)
 * UART + Syslog (UDP, NetX Duo) + FileX sinks
 *
 * NEW:
 *  - Individuelle Log-Kanaele (z. B. "net", "sensor", "ui") mit eigenem Level & Sink-Maske.
 *  - API: Kanal registrieren, Level/Sinks je Kanal setzen, gezielt in Kanal loggen.
 *  - File-Rotation: bis zu 10 Dateien (app.log, app.1.log … app.9.log).
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "stm32n6xx_hal.h"
#include "STM32N6570-DK/stm32n6570_discovery.h"
#include "BSP/Inc/stm32_dev_handles.h"
#include "BSP/Inc/gpio.h"
#include "HalBoard.h"

void HAL_Board_Led_ERR(bool on)
{
	if(on == true)
	{
		UserLed_Red_On();
	}
	else
	{
		UserLed_Red_Off();
	}
}

void HAL_Board_Led_RUN(bool on)
{
	if(on == true)
	{
		UserLed_Green_On();
	}
	else
	{
		UserLed_Green_Off();
	}
}

uint32_t HAL_Board_Debug_UART_Write(void* handle, const uint8_t* data, uint32_t len, uint32_t timeout_ticks)
{
	HAL_StatusTypeDef res = HAL_OK;

	UART_HandleTypeDef * hUsart = DebugUsartHandle_get();

	(void) handle;
	(void) timeout_ticks;

	if(hUsart != NULL)
	{
		do {
			res = HAL_UART_Transmit_IT(hUsart, (uint8_t*)data, len);
		} while(res == HAL_BUSY);
	}

	return res;
}
