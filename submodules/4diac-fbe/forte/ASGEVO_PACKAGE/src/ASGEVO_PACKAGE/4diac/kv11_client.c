#define _POSIX_C_SOURCE 200809L

//#include "kv11_client.h"
//#include "kv11.h"
#include "forte/ASGEVO_PACKAGE/asgevo_package_config.h"
#include "forte/ASGEVO_PACKAGE/4diac/kv11_client.h"
#include "forte/ASGEVO_PACKAGE/4diac/kv11.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <time.h>

#include <stdio.h>

#define KV11C_CAP 1500

struct kv11c_state {
    int sockfd;
    struct sockaddr_in dst;

    uint8_t buf[2][KV11C_CAP];
    size_t  len[2];
    uint8_t count[2];
    int     front;
    int     has_data;

    pthread_mutex_t mtx;
    pthread_cond_t  cv;

    pthread_t sender;
    int period_ms;

    volatile sig_atomic_t stop;
};

static struct kv11c_state g;

/* ---- time helpers ---- */
static struct timespec ts_add_ms(struct timespec t, int ms) {
    t.tv_nsec += (long)(ms % 1000) * 1000000L;
    t.tv_sec  += ms / 1000;
    if (t.tv_nsec >= 1000000000L) { t.tv_nsec -= 1000000000L; t.tv_sec += 1; }
    return t;
}
static void sleep_until(const struct timespec *abs_t) {
    for (;;) {
        int rc = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, abs_t, NULL);
        if (rc == 0) return;
    }
}

/* ---- init a fresh KV11 frame in buffer idx ---- */
static void begin_frame_locked(int idx) {
    size_t off = 0;
    /* header count=0 */
    (void)kv11_write_header(g.buf[idx], KV11C_CAP, &off, 0);
    g.len[idx] = off;     /* 8 */
    g.count[idx] = 0;
}

/* commit back->front */
static void commit_locked(int back) {
    //g.front = back;
    g.has_data = 1;
    pthread_cond_broadcast(&g.cv);
}

/* common pair append into BACK buffer */
static int add_pair_locked(uint32_t key, uint8_t type, const uint8_t *v, uint16_t vlen) {
    int back = g.front;

    if (g.len[back] < 8) begin_frame_locked(back);
    if (g.count[back] == 255) return -1;

    size_t off = g.len[back];
    int rc = kv11_write_pair_raw(g.buf[back], KV11C_CAP, &off, key, type, v, vlen);
    if (rc != 0) return rc;

    g.len[back] = off;
    g.count[back]++;

    /* Patch header count byte: magic(4) + ver(1) => count at offset 5 */
    g.buf[back][5] = g.count[back];

    /* Make snapshot visible */
    commit_locked(back);
    return 0;
}

/* sender thread sends front snapshot every period_ms */
static void* sender_thread(void *arg) {
    (void)arg;

    //pthread_mutex_lock(&g.mtx);
    //while (!g.has_data && !g.stop) pthread_cond_wait(&g.cv, &g.mtx);
    //pthread_mutex_unlock(&g.mtx);

    struct timespec next;
    clock_gettime(CLOCK_MONOTONIC, &next);
    next = ts_add_ms(next, g.period_ms);

    uint8_t local[KV11C_CAP];

    while (!g.stop) {
        size_t n = 0;
        pthread_mutex_lock(&g.mtx);  ///#######################
        int f = g.front;
        int has_data = g.has_data;
        n = g.len[f];
        if (n > KV11C_CAP) n = KV11C_CAP;
        memcpy(local, g.buf[f], n);
        // clear current buffer and switch front buffer so application can add data while sending
        memset(g.buf[f], 0x00, sizeof(g.buf[f]));
        g.len[f]=0;
        g.has_data = 0;
        g.front = 1 - g.front;
        pthread_mutex_unlock(&g.mtx);///#######################

        if(has_data)
        {
        	(void)sendto(g.sockfd, local, n, 0, (struct sockaddr*)&g.dst, sizeof(g.dst));
        }


        sleep_until(&next);
        next = ts_add_ms(next, g.period_ms);
    }
    return NULL;
}

/* ---- public lifecycle ---- */

int kv11_client_start(const char *dst_ip, uint16_t dst_port, int period_ms) {
    memset(&g, 0, sizeof(g));
    g.period_ms = (period_ms <= 0) ? 100 : period_ms;

    pthread_mutex_init(&g.mtx, NULL);
    pthread_cond_init(&g.cv, NULL);

    g.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (g.sockfd < 0) return -1;

    memset(&g.dst, 0, sizeof(g.dst));
    g.dst.sin_family = AF_INET;
    g.dst.sin_port = htons(dst_port);
    if (inet_pton(AF_INET, dst_ip, &g.dst.sin_addr) != 1) {
        close(g.sockfd);
        return -2;
    }

    pthread_mutex_lock(&g.mtx);
    begin_frame_locked(0);
    begin_frame_locked(1);
    g.front = 0;
    g.has_data = 0;
    pthread_mutex_unlock(&g.mtx);

    if (pthread_create(&g.sender, NULL, sender_thread, NULL) != 0) {
        close(g.sockfd);
        return -3;
    }

    return 0;
}

void kv11_client_stop(void) {
    g.stop = 1;

    pthread_mutex_lock(&g.mtx);
    pthread_cond_broadcast(&g.cv);
    pthread_mutex_unlock(&g.mtx);

    if (g.sender) pthread_join(g.sender, NULL);

    if (g.sockfd > 0) close(g.sockfd);

    pthread_cond_destroy(&g.cv);
    pthread_mutex_destroy(&g.mtx);

    memset(&g, 0, sizeof(g));
}

void kv11_client_reset_frame(void) {
    pthread_mutex_lock(&g.mtx);
    int back = 1 - g.front;
    begin_frame_locked(back);
    commit_locked(back);
    pthread_mutex_unlock(&g.mtx);
}

/* ---- USER API: kv11_add_* (no buffer args) ---- */

int kv11_add_u32(uint32_t key, uint32_t value) {
    uint8_t tmp[4];
    tmp[0] = (uint8_t)((value >> 24) & 0xFF);
    tmp[1] = (uint8_t)((value >> 16) & 0xFF);
    tmp[2] = (uint8_t)((value >>  8) & 0xFF);
    tmp[3] = (uint8_t)( value        & 0xFF);

    pthread_mutex_lock(&g.mtx);
    int rc = add_pair_locked(key, KV_T_UINT32, tmp, 4);
    pthread_mutex_unlock(&g.mtx);
    return rc;
}

/* strict type tagging for i32 */
int kv11_add_i32(uint32_t key, int32_t value) {
    uint32_t u = (uint32_t)value;
    uint8_t tmp[4];
    tmp[0] = (uint8_t)((u >> 24) & 0xFF);
    tmp[1] = (uint8_t)((u >> 16) & 0xFF);
    tmp[2] = (uint8_t)((u >>  8) & 0xFF);
    tmp[3] = (uint8_t)( u        & 0xFF);

    pthread_mutex_lock(&g.mtx);
    int rc = add_pair_locked(key, KV_T_INT32, tmp, 4);
    pthread_mutex_unlock(&g.mtx);
    return rc;
}

int kv11_add_float(uint32_t key, float value) {
    uint32_t raw;
    memcpy(&raw, &value, sizeof(raw));

    uint8_t tmp[4];
    tmp[0] = (uint8_t)((raw >> 24) & 0xFF);
    tmp[1] = (uint8_t)((raw >> 16) & 0xFF);
    tmp[2] = (uint8_t)((raw >>  8) & 0xFF);
    tmp[3] = (uint8_t)( raw        & 0xFF);

    pthread_mutex_lock(&g.mtx);
    int rc = add_pair_locked(key, KV_T_FLOAT, tmp, 4);
    pthread_mutex_unlock(&g.mtx);
    return rc;
}

int kv11_add_string(uint32_t key, const char *str) {
    if (!str) str = "";
    size_t n = strlen(str);
    if (n > 65535) return -4;

    pthread_mutex_lock(&g.mtx);
    int rc = add_pair_locked(key, KV_T_STRING, (const uint8_t*)str, (uint16_t)n);
    pthread_mutex_unlock(&g.mtx);
    return rc;
}
