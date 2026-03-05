// by chad
#include "TxArray.h"
#include <string.h>

static inline void _lock(TxArray* arr) {
    if (arr->initialized)
        tx_mutex_get(&arr->mutex, TX_WAIT_FOREVER);
}

static inline void _unlock(TxArray* arr) {
    if (arr->initialized)
        tx_mutex_put(&arr->mutex);
}

UINT TxArray_Init(TxArray* arr, CHAR* mutex_name, void* data_pool, size_t element_size, size_t max_elements)
{
    if (!arr || !data_pool || element_size == 0 || max_elements == 0)
        return TX_PTR_ERROR;

    arr->data = (uint8_t*)data_pool;
    arr->count = 0;
    arr->element_size = element_size;
    arr->max_elements = max_elements;

    UINT status = tx_mutex_create(&arr->mutex, mutex_name, TX_INHERIT);
    if (status != TX_SUCCESS)
        return status;

    arr->initialized = true;
    return TX_SUCCESS;
}

UINT TxArray_Add(TxArray* arr, const void* element) {
    if (!arr || !arr->initialized || !element)
        return TX_PTR_ERROR;

    _lock(arr);

    if (arr->count >= arr->max_elements) {  // <- max_elements statt TX_ARRAY_MAX_SIZE
        _unlock(arr);
        return TX_QUEUE_ERROR;
    }

    memcpy(&arr->data[arr->count * arr->element_size], element, arr->element_size);
    arr->count++;

    _unlock(arr);
    return TX_SUCCESS;
}

UINT TxArray_Get(const TxArray* arr, size_t index, void* out_element) {
    if (!arr || !arr->initialized || !out_element)
        return TX_PTR_ERROR;

    tx_mutex_get((TX_MUTEX*)&arr->mutex, TX_WAIT_FOREVER);

    if (index >= arr->count) {
        tx_mutex_put((TX_MUTEX*)&arr->mutex);
        return TX_PTR_ERROR;
    }

    memcpy(out_element, &arr->data[index * arr->element_size], arr->element_size);
    tx_mutex_put((TX_MUTEX*)&arr->mutex);

    return TX_SUCCESS;
}

UINT TxArray_Set(TxArray* arr, size_t index, const void* element) {
    if (!arr || !arr->initialized || !element)
        return TX_PTR_ERROR;

    _lock(arr);

    if (index >= arr->count) {
        _unlock(arr);
        return TX_PTR_ERROR;
    }

    memcpy(&arr->data[index * arr->element_size], element, arr->element_size);
    _unlock(arr);

    return TX_SUCCESS;
}

UINT TxArray_Remove(TxArray* arr, size_t index) {
    if (!arr || !arr->initialized)
        return TX_PTR_ERROR;

    _lock(arr);

    if (index >= arr->count) {
        _unlock(arr);
        return TX_PTR_ERROR;
    }

    if (index < arr->count - 1) {
        memmove(&arr->data[index * arr->element_size],
                &arr->data[(index + 1) * arr->element_size],
                (arr->count - index - 1) * arr->element_size);
    }
    arr->count--;

    _unlock(arr);
    return TX_SUCCESS;
}

UINT TxArray_Clear(TxArray* arr) {
    if (!arr || !arr->initialized)
        return TX_PTR_ERROR;

    _lock(arr);
    arr->count = 0;
    _unlock(arr);

    return TX_SUCCESS;
}

size_t TxArray_Count(const TxArray* arr) {
    if (!arr || !arr->initialized)
        return 0;

    tx_mutex_get((TX_MUTEX*)&arr->mutex, TX_WAIT_FOREVER);
    size_t size = arr->count;
    tx_mutex_put((TX_MUTEX*)&arr->mutex);
    return size;
}
