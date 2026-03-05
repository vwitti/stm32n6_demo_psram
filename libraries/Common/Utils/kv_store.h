/*
 * ip_utils.h
 *
 *  Created on: Nov 6, 2025
 *      Author: vw
 */

#ifndef COMMON_UTILS_KV_STORE_H_
#define COMMON_UTILS_KV_STORE_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    char *key;
    char *value;
} kv_pair_t;

typedef struct
{
    kv_pair_t *items;
    size_t     count;
    size_t     capacity;
} kv_store_t;

/* Initialize an empty store */
void kv_init(kv_store_t *store);

/* Free all memory (keys, values, array) */
void kv_free(kv_store_t *store);

/* Load key/value pairs from a file with lines like "KEY=VALUE"
 * - Lines starting with '#' or ';' are treated as comments and ignored
 * - Empty / whitespace-only lines are ignored
 * - Existing content in store is preserved (call kv_init before if you want it empty)
 * Returns 0 on success, <0 on error
 */
int kv_load_from_file(kv_store_t *store, const char *filename);

/* Save all key/value pairs to a file as "KEY=VALUE" lines
 * (comments are not preserved)
 * Returns 0 on success, <0 on error
 */
int kv_save_to_file(const kv_store_t *store, const char *filename);

/* Get value for key, or NULL if not found */
const char *kv_get(const kv_store_t *store, const char *key);

/* Set or update key to value
 * - If key exists, value is replaced
 * - If key does not exist, it is added
 * Returns 0 on success, <0 on error
 */
int kv_set(kv_store_t *store, const char *key, const char *value);

/* Remove a key if it exists, no error if it does not */
void kv_remove(kv_store_t *store, const char *key);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_UTILS_KV_STORE_H_ */
