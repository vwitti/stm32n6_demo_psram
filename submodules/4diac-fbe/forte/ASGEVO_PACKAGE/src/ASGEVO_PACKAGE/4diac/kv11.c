//#include "kv11.h"
#include "forte/ASGEVO_PACKAGE/4diac/kv11.h"
#include <string.h>

/* ---- BE helpers ---- */
static uint32_t rd_u32_be(const uint8_t *p) {
    return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) | ((uint32_t)p[2] << 8) | (uint32_t)p[3];
}
static uint16_t rd_u16_be(const uint8_t *p) {
    return (uint16_t)(((uint16_t)p[0] << 8) | (uint16_t)p[1]);
}
static int wr_u32_be(uint8_t *b, size_t cap, size_t *o, uint32_t v) {
    if (*o + 4 > cap) return -1;
    b[(*o)++] = (uint8_t)((v >> 24) & 0xFF);
    b[(*o)++] = (uint8_t)((v >> 16) & 0xFF);
    b[(*o)++] = (uint8_t)((v >> 8) & 0xFF);
    b[(*o)++] = (uint8_t)(v & 0xFF);
    return 0;
}
static int wr_u16_be(uint8_t *b, size_t cap, size_t *o, uint16_t v) {
    if (*o + 2 > cap) return -1;
    b[(*o)++] = (uint8_t)((v >> 8) & 0xFF);
    b[(*o)++] = (uint8_t)(v & 0xFF);
    return 0;
}

static void u32_to_be_bytes(uint8_t out[4], uint32_t v) {
    out[0] = (uint8_t)((v >> 24) & 0xFF);
    out[1] = (uint8_t)((v >> 16) & 0xFF);
    out[2] = (uint8_t)((v >> 8) & 0xFF);
    out[3] = (uint8_t)(v & 0xFF);
}
static uint32_t u32_from_be_bytes(const uint8_t in[4]) {
    return ((uint32_t)in[0] << 24) | ((uint32_t)in[1] << 16) | ((uint32_t)in[2] << 8) | (uint32_t)in[3];
}

/* ---- API ---- */

int kv11_decode(const uint8_t *buf, size_t len, kv11_pair_cb cb, void *user) {
    if (!buf || len < 8) return -10;

    const uint8_t *p = buf;
    const uint8_t *end = buf + len;

    uint32_t magic = rd_u32_be(p); p += 4;
    uint8_t version = *p++;
    uint8_t count = *p++;
    (void)rd_u16_be(p); p += 2;

    if (magic != KV11_MAGIC) return -11;
    if (version != KV11_VER) return -12;

    for (uint8_t i = 0; i < count; i++) {
        /* key(4)+type(1)+res(1)+len(2) */
        if (p + 8 > end) return -20;

        uint32_t key = rd_u32_be(p); p += 4;
        uint8_t type = *p++;
        (void)*p++; /* reserved */
        uint16_t vlen = rd_u16_be(p); p += 2;

        if (p + vlen > end) return -21;

        if (cb) cb(user, key, type, p, vlen);
        p += vlen;
    }

    return 0;
}

int kv11_write_header(uint8_t *buf, size_t cap, size_t *off, uint8_t count) {
    if (!buf || !off) return -40;
    if (wr_u32_be(buf, cap, off, KV11_MAGIC) != 0) return -41;
    if (*off + 2 > cap) return -42;
    buf[(*off)++] = (uint8_t)KV11_VER;
    buf[(*off)++] = count;
    if (wr_u16_be(buf, cap, off, 0) != 0) return -43;
    return 0;
}

int kv11_write_pair_raw(
    uint8_t *buf, size_t cap, size_t *off,
    uint32_t key, uint8_t type,
    const uint8_t *value, uint16_t value_len
) {
    if (!buf || !off) return -30;
    if (!value && value_len != 0) return -31;
    if (*off + 8 + (size_t)value_len > cap) return -32;

    if (wr_u32_be(buf, cap, off, key) != 0) return -33;

    buf[(*off)++] = type;
    buf[(*off)++] = 0; /* reserved */

    if (wr_u16_be(buf, cap, off, value_len) != 0) return -34;

    if (value_len) {
        memcpy(buf + *off, value, value_len);
        *off += value_len;
    }
    return 0;
}

/* ---- Typed setters ---- */
#if 0
int kv11_add_u32(uint8_t *buf, size_t cap, size_t *off, uint32_t key, uint32_t value) {
    uint8_t tmp[4];
    u32_to_be_bytes(tmp, value);
    return kv11_write_pair_raw(buf, cap, off, key, KV_T_UINT32, tmp, 4);
}

int kv11_add_i32(uint8_t *buf, size_t cap, size_t *off, uint32_t key, int32_t value) {
    uint8_t tmp[4];
    u32_to_be_bytes(tmp, (uint32_t)value);
    return kv11_write_pair_raw(buf, cap, off, key, KV_T_INT32, tmp, 4);
}

int kv11_add_float(uint8_t *buf, size_t cap, size_t *off, uint32_t key, float value) {
    uint32_t raw;
    memcpy(&raw, &value, sizeof(raw));
    uint8_t tmp[4];
    u32_to_be_bytes(tmp, raw);
    return kv11_write_pair_raw(buf, cap, off, key, KV_T_FLOAT, tmp, 4);
}

int kv11_add_string(uint8_t *buf, size_t cap, size_t *off, uint32_t key, const char *str) {
    if (!str) str = "";
    size_t n = strlen(str);
    if (n > 65535) return -60;
    return kv11_write_pair_raw(buf, cap, off, key, KV_T_STRING, (const uint8_t*)str, (uint16_t)n);
}
#endif

/* ---- Typed getters ---- */

int kv11_get_u32(uint8_t type, const uint8_t *value, uint16_t len, uint32_t *out) {
    if (!out || !value) return -70;
    if (type != KV_T_UINT32 || len != 4) return -71;
    *out = u32_from_be_bytes(value);
    return 0;
}

int kv11_get_i32(uint8_t type, const uint8_t *value, uint16_t len, int32_t *out) {
    if (!out || !value) return -72;
    if (type != KV_T_INT32 || len != 4) return -73;
    *out = (int32_t)u32_from_be_bytes(value);
    return 0;
}

int kv11_get_float(uint8_t type, const uint8_t *value, uint16_t len, float *out) {
    if (!out || !value) return -74;
    if (type != KV_T_FLOAT || len != 4) return -75;
    uint32_t raw = u32_from_be_bytes(value);
    memcpy(out, &raw, sizeof(raw));
    return 0;
}
