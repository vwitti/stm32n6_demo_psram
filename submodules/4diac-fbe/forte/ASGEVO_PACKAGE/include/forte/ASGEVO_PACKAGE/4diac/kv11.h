#ifndef KV11_H
#define KV11_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KV11_MAGIC  0x4B563131u /* "KV11" */
#define KV11_VER    2u

enum kv_type {
    KV_T_INT32  = 1,
    KV_T_UINT32 = 2,
    KV_T_FLOAT  = 3,
    KV_T_STRING = 4
};

typedef void (*kv11_pair_cb)(
    void *user,
    uint32_t key,
    uint8_t type,
    const uint8_t *value,
    uint16_t value_len
);

/* Decode: validiert Header und ruft cb pro Pair auf */
int kv11_decode(const uint8_t *buf, size_t len, kv11_pair_cb cb, void *user);

/* Header schreiben */
int kv11_write_header(uint8_t *buf, size_t cap, size_t *off, uint8_t count);

/* Raw Pair schreiben (key + type + reserved + len + value) */
int kv11_write_pair_raw(
    uint8_t *buf, size_t cap, size_t *off,
    uint32_t key, uint8_t type,
    const uint8_t *value, uint16_t value_len
);

/* Typed Getter (für Server) */
int kv11_get_u32(uint8_t type, const uint8_t *value, uint16_t len, uint32_t *out);
int kv11_get_i32(uint8_t type, const uint8_t *value, uint16_t len, int32_t *out);
int kv11_get_float(uint8_t type, const uint8_t *value, uint16_t len, float *out);

#ifdef __cplusplus
}
#endif

#endif /* KV11_H */
