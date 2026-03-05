/*
 * Syslog.h
 *
 *  Created on: Nov 5, 2025
 *      Author: vw
 */

#ifndef COMMON_SYSLOG_SYSLOG_H_
#define COMMON_SYSLOG_SYSLOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define LOG_SYSLOG_PORT 11111

// Sink mask bits
#define LOG_SINK_UART   (1u << 0)
#define LOG_SINK_SYSLOG (1u << 1)
#define LOG_SINK_FILEX  (1u << 2)
// Only network
#define LOG_SINK_ALL    LOG_SINK_SYSLOG //(LOG_SINK_UART | LOG_SINK_SYSLOG | LOG_SINK_FILEX)

/************ Types ************/

typedef enum {
    LOG_LEVEL_ERROR = 0,
    LOG_LEVEL_WARN  = 1,
    LOG_LEVEL_INFO  = 2,
    LOG_LEVEL_DEBUG = 3,
    LOG_LEVEL_TRACE = 4
} log_level_t;

#if defined(TRACE_MODULE)
	#define TRACE(x)	x
#else
	#define TRACE(x)	/* x */
#endif

unsigned int Log_Init(
		void* nx_ip,
        uint32_t syslog_ip,
        uint16_t syslog_port,
		void* uart_handle, uint32_t (*uart_write_fn)(void*, const uint8_t*, uint32_t, uint32_t),
		log_level_t default_level);
unsigned int Log_Deinit(void);
int Log_ChannelRegister(const char* name, log_level_t level, uint32_t sink_mask);
int Log_ChannelGet(const char* name);
void Log_ChannelSetLevel(int ch_id, log_level_t level);
void Log_ChannelSetSinks(int ch_id, uint32_t sink_mask);
void Log_ChPrintf(uint8_t ch_id, log_level_t level, const char* fmt, ...);
void Log_Printf(log_level_t level, const char* fmt, ...);
void Log_Printf_Version_Info(log_level_t level);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_SYSLOG_SYSLOG_H_ */
