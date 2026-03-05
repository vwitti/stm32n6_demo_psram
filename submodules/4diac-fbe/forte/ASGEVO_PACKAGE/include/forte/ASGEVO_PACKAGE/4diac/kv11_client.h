#ifndef KV11_CLIENT_H
#define KV11_CLIENT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Engine lifecycle */
int  kv11_client_start(const char *dst_ip, uint16_t dst_port, int period_ms);
void kv11_client_stop(void);

/* Optional: start a new datagram/frame (count=0, clear pairs) */
void kv11_client_reset_frame(void);

/* USER API: exactly as requested (no buffer args) */
int kv11_add_u32(uint32_t key, uint32_t value);
int kv11_add_i32(uint32_t key, int32_t value);
int kv11_add_float(uint32_t key, float value);
int kv11_add_string(uint32_t key, const char *str);

#ifdef __cplusplus
}
#endif

#endif /* KV11_CLIENT_H */
