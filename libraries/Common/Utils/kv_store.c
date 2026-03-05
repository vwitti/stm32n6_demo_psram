#include "kv_store.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* --- internal helpers --------------------------------------------------- */

static char *kv_strdup(const char *s)
{
    if (!s) return NULL;
    size_t len = strlen(s);
    char *p = (char *)malloc(len + 1);
    if (!p) return NULL;
    memcpy(p, s, len + 1);
    return p;
}

static void kv_ensure_capacity(kv_store_t *store, size_t min_capacity)
{
    if (store->capacity >= min_capacity)
        return;

    size_t new_cap = store->capacity ? store->capacity * 2 : 8;
    if (new_cap < min_capacity)
        new_cap = min_capacity;

    kv_pair_t *new_items = (kv_pair_t *)realloc(store->items, new_cap * sizeof(kv_pair_t));
    if (!new_items) {
        /* allocation failed; leave store unchanged */
        return;
    }

    store->items   = new_items;
    store->capacity = new_cap;
}

static int kv_find_index(const kv_store_t *store, const char *key)
{
    if (!store || !key) return -1;

    for (size_t i = 0; i < store->count; ++i) {
        if (store->items[i].key && strcmp(store->items[i].key, key) == 0)
            return (int)i;
    }
    return -1;
}

static char *trim_whitespace(char *s)
{
    char *end;

    if (!s) return s;

    /* leading */
    while (*s && isspace((unsigned char)*s))
        s++;

    if (*s == '\0')
        return s;

    /* trailing */
    end = s + strlen(s) - 1;
    while (end > s && isspace((unsigned char)*end))
        *end-- = '\0';

    return s;
}

/* --- public API --------------------------------------------------------- */

void kv_init(kv_store_t *store)
{
    if (!store) return;
    store->items    = NULL;
    store->count    = 0;
    store->capacity = 0;
}

void kv_free(kv_store_t *store)
{
    if (!store) return;

    for (size_t i = 0; i < store->count; ++i) {
        free(store->items[i].key);
        free(store->items[i].value);
    }

    free(store->items);
    store->items    = NULL;
    store->count    = 0;
    store->capacity = 0;
}

const char *kv_get(const kv_store_t *store, const char *key)
{
    int idx = kv_find_index(store, key);
    if (idx < 0)
        return NULL;
    return store->items[idx].value;
}

int kv_set(kv_store_t *store, const char *key, const char *value)
{
    if (!store || !key || !value)
        return -1;

    int idx = kv_find_index(store, key);

    if (idx >= 0) {
        /* update existing */
        char *new_val = kv_strdup(value);
        if (!new_val) return -2;
        free(store->items[idx].value);
        store->items[idx].value = new_val;
        return 0;
    }

    /* add new */
    kv_ensure_capacity(store, store->count + 1);
    if (store->capacity < store->count + 1)
        return -3; /* allocation failed */

    char *k = kv_strdup(key);
    char *v = kv_strdup(value);
    if (!k || !v) {
        free(k);
        free(v);
        return -2;
    }

    store->items[store->count].key   = k;
    store->items[store->count].value = v;
    store->count++;

    return 0;
}

void kv_remove(kv_store_t *store, const char *key)
{
    if (!store || !key) return;

    int idx = kv_find_index(store, key);
    if (idx < 0)
        return;

    free(store->items[idx].key);
    free(store->items[idx].value);

    /* compact array */
    for (size_t i = (size_t)idx; i + 1 < store->count; ++i) {
        store->items[i] = store->items[i + 1];
    }
    store->count--;
}

int kv_load_from_file(kv_store_t *store, const char *filename)
{
    if (!store || !filename)
        return -1;

    FILE *f = fopen(filename, "r");
    if (!f)
        return -2;

    char line[512];

    while (fgets(line, sizeof(line), f)) {
        /* strip newline */
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';

        /* trim */
        char *p = trim_whitespace(line);
        if (*p == '\0')
            continue; /* empty line */

        /* comment? (# or ;) */
        if (*p == '#' || *p == ';')
            continue;

        /* find '=' */
        char *eq = strchr(p, '=');
        if (!eq)
            continue; /* invalid line, ignore */

        *eq = '\0';
        char *key = trim_whitespace(p);
        char *val = trim_whitespace(eq + 1);

        if (*key == '\0')
            continue; /* no key */

        kv_set(store, key, val);
    }

    fclose(f);
    return 0;
}

int kv_save_to_file(const kv_store_t *store, const char *filename)
{
    if (!store || !filename)
        return -1;

    FILE *f = fopen(filename, "w");
    if (!f)
        return -2;

    for (size_t i = 0; i < store->count; ++i) {
        if (!store->items[i].key || !store->items[i].value)
            continue;
        fprintf(f, "%s=%s\n", store->items[i].key, store->items[i].value);
    }

    fclose(f);
    return 0;
}

