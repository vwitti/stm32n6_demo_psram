/*
 * ThreadX Logger Skeleton — Channels + Rotation (10 files)
 * UART + Syslog (UDP, NetX Duo) + FileX sinks
 *
 * NEW:
 *  - Individuelle Log-Kanäle (z. B. "net", "sensor", "ui") mit eigenem Level & Sink-Maske.
 *  - API: Kanal registrieren, Level/Sinks je Kanal setzen, gezielt in Kanal loggen.
 *  - File-Rotation: bis zu 10 Dateien (app.log, app.1.log … app.9.log).
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "threadx/common/inc/tx_api.h"
#include "netxduo/common/inc/nx_api.h"
//#include "fx_api.h"

#include "tcsglobal/asg_evo.h"
#include "SysLayer/HalThread.h"
#include "SysLog/Syslog.h"
#include "Utils/Sys_BuildInfo.h"

/************ Configuration ************/
#ifndef LOG_RING_CAPACITY
#define LOG_RING_CAPACITY   16 //128
#endif
#ifndef LOG_MSG_MAX
#define LOG_MSG_MAX         64 //256
#endif
#ifndef LOG_WORKER_STACK
#define LOG_WORKER_STACK    2560
#endif
#ifndef LOG_WORKER_PRIO
#define LOG_WORKER_PRIO     PRIO_BACKGROUND
#endif
#ifndef LOG_SYSLOG_PORT
#define LOG_SYSLOG_PORT     514
#endif
#ifndef LOG_HOSTNAME
#define LOG_HOSTNAME        "threadx-node"
#endif
#ifndef LOG_APPNAME
#define LOG_APPNAME         "app"
#endif
#ifndef LOG_THREADNAME
#define LOG_THREADNAME      "syslog.worker"
#endif


// File rotation
#ifndef LOG_FILE_MAX_SIZE
#define LOG_FILE_MAX_SIZE   (64*1024)   // 64 KB pro Datei
#endif
#ifndef LOG_FILE_ROTATE_COUNT
#define LOG_FILE_ROTATE_COUNT 10        // app.log + .1 … .9
#endif

// Channels
#ifndef LOG_MAX_CHANNELS
#define LOG_MAX_CHANNELS    16
#endif
#ifndef LOG_CH_NAME_MAX
#define LOG_CH_NAME_MAX     9
#endif



typedef struct {
    char        name[LOG_CH_NAME_MAX];
    log_level_t level_threshold;
    uint32_t    sink_mask; // bitmask of LOG_SINK_*
    bool        in_use;
} log_channel_t;

typedef struct {
    uint8_t     channel_id;            // 0..LOG_MAX_CHANNELS-1
    log_level_t level;
    uint32_t    tick;
    uint16_t    len;
    char        buf[LOG_MSG_MAX];
} log_msg_t;

typedef struct {
	bool        init_done;
    // ring buffer
    log_msg_t   entries[LOG_RING_CAPACITY];
    uint16_t    head;
    uint16_t    tail;

    // channels
    log_channel_t channels[LOG_MAX_CHANNELS];
    uint8_t        default_channel;    // usually 0

    // sync
    TX_MUTEX    lock;
    TX_SEMAPHORE sem_items;

    // worker
    TX_THREAD   worker_thread;
    ULONG       worker_stack[LOG_WORKER_STACK / sizeof(ULONG)];

    // global sinks availability (hardware/backend presence)
    bool        sink_uart_available;
    bool        sink_syslog_available;
    bool        sink_filex_available;

    // UART
    void*       uart_handle;
    uint32_t    (*uart_write_fn)(void* handle, const uint8_t* data, uint32_t len, uint32_t timeout_ticks);

#if !defined(ETHERNET_NOT_SUPPORTED)
    // Syslog (NetX Duo)
    NX_UDP_SOCKET  syslog_socket;
    NX_IP*         nx_ip;
    ULONG          syslog_server_ip;   // host-endian; will convert to network order on send
    USHORT         syslog_server_port;
    bool           syslog_socket_open;
#endif

    // FileX
    //FX_MEDIA*      fx_media;
    //CHAR           fx_path[64];

    volatile ULONG dropped;
} log_ctx_t;

static log_ctx_t g_log;

/************ Forward decls ************/
static VOID ThreadASG_log_worker_entry(ULONG arg);
static void ring_push_unlocked(const log_msg_t* msg);
static bool ring_pop_unlocked(log_msg_t* out);
static const char* level_str(log_level_t lv);

static void sink_uart_write(const char* s, UINT n);
#if !defined(ETHERNET_NOT_SUPPORTED)
UINT syslog_socket_open(void);

void sink_syslog_send(uint8_t ch_id, const log_msg_t* m);
#endif
//static void sink_filex_append_line(const char* s, UINT n);
//static void filex_rotate_if_needed(void);

/************ Helpers ************/
static inline uint16_t ring_next(uint16_t idx) { return (uint16_t)((idx + 1U) % LOG_RING_CAPACITY); }

static void ring_push_unlocked(const log_msg_t* msg) {
    uint16_t next = ring_next(g_log.head);
    if (next == g_log.tail) { g_log.tail = ring_next(g_log.tail); g_log.dropped++; }
    g_log.entries[g_log.head] = *msg; // copy
    g_log.head = next;
}

static bool ring_pop_unlocked(log_msg_t* out) {
    if (g_log.tail == g_log.head) return false;
    *out = g_log.entries[g_log.tail];
    g_log.tail = ring_next(g_log.tail);
    return true;
}

static const char* level_str(log_level_t lv) {
    switch (lv) {
        case LOG_LEVEL_ERROR: return "ERROR";
        case LOG_LEVEL_WARN:  return "WARN ";
        case LOG_LEVEL_INFO:  return "INFO ";
        case LOG_LEVEL_DEBUG: return "DEBUG";
        case LOG_LEVEL_TRACE: return "TRACE";
        default: return "?";
    }
}

/************ Channel API ************/
static int channel_find(const char* name) {
    for (int i = 0; i < LOG_MAX_CHANNELS; ++i) {
        if (g_log.channels[i].in_use && strncmp(g_log.channels[i].name, name, LOG_CH_NAME_MAX) == 0) return i;
    }
    return -1;
}

static int channel_alloc(void) {
    for (int i = 0; i < LOG_MAX_CHANNELS; ++i) {
        if (!g_log.channels[i].in_use) return i;
    }
    return -1;
}

// Register or fetch a channel by name. Returns channel id (>=0) or -1 on failure.
int Log_ChannelRegister(const char* name, log_level_t level, uint32_t sink_mask) {
    if (!name) return -1;
    tx_mutex_get(&g_log.lock, TX_WAIT_FOREVER);
    int idx = channel_find(name);
    if (idx < 0) {
        idx = channel_alloc();
        if (idx >= 0) {
            memset(&g_log.channels[idx], 0, sizeof(g_log.channels[idx]));
            strncpy(g_log.channels[idx].name, name, LOG_CH_NAME_MAX - 1);
            g_log.channels[idx].level_threshold = level;
            g_log.channels[idx].sink_mask = sink_mask;
            g_log.channels[idx].in_use = true;
        }
    } else {
        // update level/sinks on existing
        g_log.channels[idx].level_threshold = level;
        g_log.channels[idx].sink_mask = sink_mask;
    }
    tx_mutex_put(&g_log.lock);
    return idx;
}

int Log_ChannelGet(const char* name) {
    tx_mutex_get(&g_log.lock, TX_WAIT_FOREVER);
    int idx = channel_find(name);
    tx_mutex_put(&g_log.lock);
    return idx;
}

void Log_ChannelSetLevel(int ch_id, log_level_t level) {
    if (ch_id < 0 || ch_id >= LOG_MAX_CHANNELS) return;
    tx_mutex_get(&g_log.lock, TX_WAIT_FOREVER);
    if (g_log.channels[ch_id].in_use) g_log.channels[ch_id].level_threshold = level;
    tx_mutex_put(&g_log.lock);
}

void Log_ChannelSetSinks(int ch_id, uint32_t sink_mask) {
    if (ch_id < 0 || ch_id >= LOG_MAX_CHANNELS) return;
    tx_mutex_get(&g_log.lock, TX_WAIT_FOREVER);
    if (g_log.channels[ch_id].in_use) g_log.channels[ch_id].sink_mask = sink_mask;
    tx_mutex_put(&g_log.lock);
}

/************ Public API ************/
// Initialize logger and create default channel "default"
#if 0
UINT Log_Init(NX_IP* nx_ip,
              ULONG syslog_ip,
              USHORT syslog_port,
              FX_MEDIA* fx_media,
              const CHAR* fx_path,
              void* uart_handle,
              UINT (*uart_write_fn)(void*, const uint8_t*, UINT, ULONG),
              log_level_t default_level)
{
    memset(&g_log, 0, sizeof(g_log));

    g_log.nx_ip = nx_ip;
    g_log.syslog_server_ip = syslog_ip; // host-endian
    g_log.syslog_server_port = (syslog_port == 0) ? LOG_SYSLOG_PORT : syslog_port;

    g_log.fx_media = fx_media;
    if (fx_media && fx_path) strncpy(g_log.fx_path, fx_path, sizeof(g_log.fx_path) - 1);

    g_log.uart_handle = uart_handle;
    g_log.uart_write_fn = uart_write_fn;

    g_log.sink_uart_available   = (uart_handle && uart_write_fn);
    g_log.sink_syslog_available = (nx_ip && syslog_ip != 0);
    g_log.sink_filex_available  = (fx_media != NULL);

    // sync
    UINT s;
    s = tx_mutex_create(&g_log.lock, (CHAR*)"log.lock", TX_INHERIT); if (s != TX_SUCCESS) return s;
    s = tx_semaphore_create(&g_log.sem_items, (CHAR*)"log.items", 0);   if (s != TX_SUCCESS) return s;

    // default channel at index 0
    memset(g_log.channels, 0, sizeof(g_log.channels));
    strncpy(g_log.channels[0].name, "default", LOG_CH_NAME_MAX - 1);
    g_log.channels[0].level_threshold = default_level;
    g_log.channels[0].sink_mask = LOG_SINK_ALL; // enable all that are available
    g_log.channels[0].in_use = true;
    g_log.default_channel = 0;

    // worker
    s = tx_thread_create(&g_log.worker_thread,
                         (CHAR*)"log.worker",
                         log_worker_entry,
                         0,
                         g_log.worker_stack,
                         sizeof(g_log.worker_stack),
                         LOG_WORKER_PRIO,
                         LOG_WORKER_PRIO,
						 TIME_SLICE_BACKGROUND,
                         TX_AUTO_START);
    if (s != TX_SUCCESS) return s;

    return TX_SUCCESS;
}

UINT Log_Deinit(void) {
    tx_thread_terminate(&g_log.worker_thread);
    tx_thread_delete(&g_log.worker_thread);
    if (g_log.syslog_socket_open)
    {
        nx_udp_socket_unbind(&g_log.syslog_socket);
        nx_udp_socket_delete(&g_log.syslog_socket);
        g_log.syslog_socket_open = false;
    }
    tx_semaphore_delete(&g_log.sem_items);
    tx_mutex_delete(&g_log.lock);
    return TX_SUCCESS;
}
#else

bool Log_SelfCheck(void)
{
	bool ret = true;
	if(g_log.init_done == true)
	{
		// ...........
		// ret = false;
	}
	return ret;
}

UINT Log_Init(
		void* nx_ip,
        ULONG syslog_ip,
        USHORT syslog_port,
		void* uart_handle,
        uint32_t (*uart_write_fn)(void*, const uint8_t*, uint32_t, uint32_t),
        log_level_t default_level
)
{
    memset(&g_log, 0, sizeof(g_log));

#if !defined(ETHERNET_NOT_SUPPORTED)
    g_log.nx_ip = nx_ip;
    g_log.syslog_server_ip = syslog_ip; // host-endian
    g_log.syslog_server_port = (syslog_port == 0) ? LOG_SYSLOG_PORT : syslog_port;
#endif

    g_log.uart_handle = uart_handle;
    g_log.uart_write_fn = uart_write_fn;

    g_log.sink_uart_available   = (uart_handle && uart_write_fn);
#if !defined(ETHERNET_NOT_SUPPORTED)
    g_log.sink_syslog_available = (nx_ip && syslog_ip != 0);
    if(g_log.sink_syslog_available)
    {
    	syslog_socket_open();
    }
#endif


    // sync use prioritiy inheritance for syslog to avoid unintended locking, since log fcts are called from any context
    UINT s;
    s = tx_mutex_create(&g_log.lock, (CHAR*)"log.lock", TX_INHERIT); if (s != TX_SUCCESS) return s;
    s = tx_semaphore_create(&g_log.sem_items, (CHAR*)"log.items", 0);   if (s != TX_SUCCESS) return s;

    // default channel at index 0
    memset(g_log.channels, 0, sizeof(g_log.channels));
    strncpy(g_log.channels[0].name, "syslog", LOG_CH_NAME_MAX - 1);
    g_log.channels[0].level_threshold = default_level;
    g_log.channels[0].sink_mask = LOG_SINK_ALL; // enable all that are available
    g_log.channels[0].in_use = true;
    g_log.default_channel = 0;

    // worker
    s = HAL_Thread_Create(&g_log.worker_thread,
                         (CHAR*)LOG_THREADNAME,
                         ThreadASG_log_worker_entry,
                         0,
                         g_log.worker_stack,
                         sizeof(g_log.worker_stack),
                         LOG_WORKER_PRIO,
                         LOG_WORKER_PRIO,
						 TIME_SLICE_BACKGROUND, //TX_NO_TIME_SLICE,
                         TX_AUTO_START,
						 Log_SelfCheck);
    if (s != TX_SUCCESS) return s;
    g_log.init_done = true;
    return TX_SUCCESS;
}

UINT Log_Deinit(void) {
	g_log.init_done = false;
    tx_thread_terminate(&g_log.worker_thread);
    tx_thread_delete(&g_log.worker_thread);
#if !defined(ETHERNET_NOT_SUPPORTED)
    if (g_log.syslog_socket_open) {
        nx_udp_socket_unbind(&g_log.syslog_socket);
        nx_udp_socket_delete(&g_log.syslog_socket);
        g_log.syslog_socket_open = false;
    }
#endif
    tx_semaphore_delete(&g_log.sem_items);
    tx_mutex_delete(&g_log.lock);
    return TX_SUCCESS;
}


#endif

// Convenience: log into default channel
void Log_Printf(log_level_t level, const char* fmt, ...)
{
	if(g_log.init_done == false) { return; }

	va_list ap;
	va_start(ap, fmt);

	// delegate to channel print with default channel
	char tmp[LOG_MSG_MAX];
	int n = vsnprintf(tmp, sizeof(tmp), fmt, ap);
	va_end(ap);
	if (n < 0) return;
	if (n >= (int)sizeof(tmp)) {
		tmp[sizeof(tmp)-1] = '\0'; n = (int)strlen(tmp);
	}

	// Use channel 0
	extern void Log_ChVPrintf(uint8_t ch_id, log_level_t level, const char* fmt, va_list ap);
	va_start(ap, fmt); // re-open for safety (not used)
	// Build message directly
	log_msg_t m;
	m.channel_id = g_log.default_channel; m.level = level;
	m.tick = tx_time_get();
	m.len = (uint16_t)n;
	memcpy(m.buf, tmp, (size_t)n);
	m.buf[n] = '\0';

	tx_mutex_get(&g_log.lock, TX_WAIT_FOREVER);
	ring_push_unlocked(&m);
	tx_mutex_put(&g_log.lock);
	tx_semaphore_put(&g_log.sem_items);

	va_end(ap);
}

// Log to specific channel by id
void Log_ChPrintf(uint8_t ch_id, log_level_t level, const char* fmt, ...)
{
	if(g_log.init_done == false) { return; }

	if (ch_id >= LOG_MAX_CHANNELS || !g_log.channels[ch_id].in_use)
    {
    	return;
    }
    if (level > g_log.channels[ch_id].level_threshold)
    {
    	return;
    }

    log_msg_t m;
    m.channel_id = ch_id;
    m.level = level;
    m.tick = tx_time_get();
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(m.buf, sizeof(m.buf), fmt, ap);
    va_end(ap);
    if (n < 0) {
    	return;
    }
    if (n >= (int)sizeof(m.buf)) {
    	m.buf[sizeof(m.buf)-1] = '\0'; n = (int)strlen(m.buf);
    }
    m.len = (uint16_t)n;

    tx_mutex_get(&g_log.lock, TX_WAIT_FOREVER);
    ring_push_unlocked(&m);
    tx_mutex_put(&g_log.lock);
    tx_semaphore_put(&g_log.sem_items);
}

/************ Worker ************/
static VOID ThreadASG_log_worker_entry(ULONG arg)
{
    (void)arg;
    for (;;) {
        tx_semaphore_get(&g_log.sem_items, TX_WAIT_FOREVER);
        for (;;) {
            log_msg_t m; bool ok;
            tx_mutex_get(&g_log.lock, TX_WAIT_FOREVER);
            ok = ring_pop_unlocked(&m);
            tx_mutex_put(&g_log.lock);
            if (!ok) break;

            // channel context snapshot
            uint8_t ch = m.channel_id;
            log_channel_t chctx; memset(&chctx, 0, sizeof(chctx));
            tx_mutex_get(&g_log.lock, TX_WAIT_FOREVER);
            if (g_log.channels[ch].in_use) chctx = g_log.channels[ch];
            tx_mutex_put(&g_log.lock);

            // apply channel level filter again (in case changed after enqueue)
            if (m.level > chctx.level_threshold) continue;

            // format human-readable line for UART/File
            char line[LOG_MSG_MAX + 64];
            int prefix = snprintf(line, sizeof(line), "[%08lu %s %-8s] ", (unsigned long)m.tick, level_str(m.level), chctx.name[0]?chctx.name:"-");
            if (prefix < 0 || prefix >= (int)sizeof(line)) continue;
            size_t avail = sizeof(line) - (size_t)prefix - 1U;
            size_t copy = (m.len < avail) ? m.len : avail;
            memcpy(line + prefix, m.buf, copy);
            line[prefix + copy] = '\0';
            UINT line_len = (UINT)(prefix + copy);

            // sink selection: channel mask intersect with availability
            if ((chctx.sink_mask & LOG_SINK_UART) && (g_log.sink_uart_available == true)) {
                sink_uart_write(line, line_len);
                sink_uart_write("\n", 2);
            }
#if !defined(ETHERNET_NOT_SUPPORTED)
            if ((chctx.sink_mask & LOG_SINK_SYSLOG) && g_log.sink_syslog_available) {
                sink_syslog_send(ch, &m);
            }
#endif
#if 0
            if ((chctx.sink_mask & LOG_SINK_FILEX) && g_log.sink_filex_available) {
                sink_filex_append_line(line, line_len);
            }
#endif
        }
    }
}

/************ UART Sink ************/
static void sink_uart_write(const char* s, UINT n) {
    if (!g_log.uart_write_fn) return;
    (void)g_log.uart_write_fn(g_log.uart_handle, (const uint8_t*)s, n, 100 /*TX_TICKS_PER_SECOND / 10*/);
}

#if !defined(ETHERNET_NOT_SUPPORTED)
/************ Syslog Sink (NetX Duo UDP) ************/
UINT syslog_socket_open(void)
{
    if (g_log.syslog_socket_open)
    {
    	return NX_SUCCESS;
    }
    if (!g_log.nx_ip || g_log.syslog_server_ip == 0)
    {
    	return NX_NOT_ENABLED;
    }
    UINT s = nx_udp_socket_create(g_log.nx_ip, &g_log.syslog_socket, (CHAR*)"log.syslog", NX_IP_NORMAL, NX_FRAGMENT_OKAY, 0x80, 3);
    if (s != NX_SUCCESS)
    {
    	return s;
    }
    s = nx_udp_socket_bind(&g_log.syslog_socket, NX_ANY_PORT, TX_NO_WAIT);
    if (s != NX_SUCCESS) {
    	nx_udp_socket_delete(&g_log.syslog_socket); return s;
    }
    g_log.syslog_socket_open = true;
    return NX_SUCCESS;
}

void sink_syslog_send(uint8_t ch_id, const log_msg_t* m) {
    UINT res;

    if(g_log.syslog_socket_open == false)
    {
    	return;
    }

    // snapshot channel name
    char chname[LOG_CH_NAME_MAX]; chname[0] = '\0';
    tx_mutex_get(&g_log.lock, TX_WAIT_FOREVER);
    if (g_log.channels[ch_id].in_use)
    {
    	strncpy(chname, g_log.channels[ch_id].name, sizeof(chname)-1);
    }
    tx_mutex_put(&g_log.lock);

    // PRI mapping
    int pri = 14; // user.info default
    switch (m->level)
    {
        case LOG_LEVEL_ERROR: pri = 11; break; // user.err
        case LOG_LEVEL_WARN:  pri = 12; break;
        case LOG_LEVEL_INFO:  pri = 14; break;
        case LOG_LEVEL_DEBUG: pri = 15; break;
        case LOG_LEVEL_TRACE: pri = 15; break;
    }

    char payload[LOG_MSG_MAX + 128];
    int hdr = snprintf(payload, sizeof(payload), "<%d>1 %lu %s %s/%s - - - %s",
                       pri,
                       (unsigned long)m->tick,
                       LOG_HOSTNAME,
                       LOG_APPNAME,
                       (chname[0]?chname:"-"),
                       m->buf);
    if (hdr < 0)
    {
    	return;
    }
    UINT plen = (UINT)((hdr < (int)sizeof(payload)) ? hdr : (int)sizeof(payload));

    NX_PACKET* pkt;
    res = nx_packet_allocate(g_log.nx_ip->nx_ip_default_packet_pool, &pkt, NX_UDP_PACKET, TX_WAIT_FOREVER);
    if (res != NX_SUCCESS)
    {
    	return;
    }
    res = nx_packet_data_append(pkt, payload, plen, g_log.nx_ip->nx_ip_default_packet_pool, TX_WAIT_FOREVER);
    if (res != NX_SUCCESS)
    {
        nx_packet_release(pkt);
        return;
    }

    // Send the packet
    nx_udp_socket_send(&g_log.syslog_socket, pkt, g_log.syslog_server_ip, g_log.syslog_server_port);
}
#endif

/************ FileX Sink + Rotation ************/
#if 0
static void filex_rotate_if_needed(void) {
    FX_FILE file; ULONG len = 0;
    if (fx_file_open(g_log.fx_media, &file, (CHAR*)g_log.fx_path, FX_OPEN_FOR_READ) == FX_SUCCESS) {
        len = fx_file_length_get(&file); fx_file_close(&file);
    }
    if (len < LOG_FILE_MAX_SIZE) return;

    // delete oldest
    CHAR old_path[96]; snprintf(old_path, sizeof(old_path), "%s.%d", g_log.fx_path, LOG_FILE_ROTATE_COUNT-1);
    fx_file_delete(g_log.fx_media, old_path);

    // shift down (N-2..0)
    for (int i = LOG_FILE_ROTATE_COUNT - 2; i >= 0; --i) {
        CHAR src[96], dst[96];
        if (i == 0) snprintf(src, sizeof(src), "%s", g_log.fx_path);
        else         snprintf(src, sizeof(src), "%s.%d", g_log.fx_path, i);
        snprintf(dst, sizeof(dst), "%s.%d", g_log.fx_path, i + 1);
        fx_file_rename(g_log.fx_media, src, dst);
    }
}

static void sink_filex_append_line(const char* s, UINT n) {
    if (!g_log.fx_media) return;
    filex_rotate_if_needed();

    FX_FILE file;
    if (fx_file_open(g_log.fx_media, &file, (CHAR*)g_log.fx_path, FX_OPEN_FOR_WRITE) != FX_SUCCESS) {
        if (fx_file_create(g_log.fx_media, (CHAR*)g_log.fx_path) != FX_SUCCESS) return;
        if (fx_file_open(g_log.fx_media, &file, (CHAR*)g_log.fx_path, FX_OPEN_FOR_WRITE) != FX_SUCCESS) return;
    }
    fx_file_seek(&file, fx_file_length_get(&file));
    fx_file_write(&file, (VOID*)s, n);
    fx_file_write(&file, (VOID*)"\n", 2);
    fx_file_flush(&file);
    fx_file_close(&file);
}
#endif

#if 0
/************ Example Usage ************/
void Logger_StartExample(NX_IP* ip, FX_MEDIA* media) {
    ULONG syslog_ip = (192U<<24)|(168U<<16)|(1U<<8)|10U; // 192.168.1.10 (host-order)

    Log_Init(ip, syslog_ip, 514, media, "/log/app.log", NULL, NULL, LOG_LEVEL_DEBUG);

    // Register custom channels
    int ch_net = Log_ChannelRegister("net", LOG_LEVEL_INFO,  LOG_SINK_SYSLOG | LOG_SINK_FILEX);
    int ch_uart= Log_ChannelRegister("uart",LOG_LEVEL_DEBUG, LOG_SINK_UART | LOG_SINK_FILEX);

    Log_ChPrintf((uint8_t)ch_net,  LOG_LEVEL_INFO,  "net up");
    Log_ChPrintf((uint8_t)ch_uart, LOG_LEVEL_DEBUG, "tx bytes=%d", 42);
    Log_Printf(LOG_LEVEL_INFO, "default channel message");
}
#endif

void Log_Printf_Version_Info(log_level_t level)
{
	Log_Printf(level, "");
	Log_Printf(level, "Program: %s", SysLayer_BuildProgramName_GET());
	Log_Printf(level, "Version: %d.%d.%d %s %s %s", SysLayer_BuildVersion_Major_GET(), SysLayer_BuildVersion_Minor_GET(), SysLayer_BuildVersion_Patch_GET(), SysLayer_BuildDate_GET(), SysLayer_BuildTime_GET(), SysLayer_BuildType_GET());
	Log_Printf(level, "Git    : %s %s", SysLayer_BuildGitHash10_GET(), SysLayer_BuildGitBranch_GET());
	Log_Printf(level, "------------------------------------");
}
