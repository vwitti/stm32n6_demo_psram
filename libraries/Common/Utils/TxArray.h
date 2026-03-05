// by chad
#ifndef COMMON_UTILS_TX_ARRAY_H
#define COMMON_UTILS_TX_ARRAY_H

#include "tx_api.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t* data;        // Zeiger auf externen Speicherpool
    size_t count;         // aktuelle Anzahl der Elemente
    size_t max_elements;  // maximale Anzahl der Elemente
    size_t element_size;  // Groeße eines Elements
    TX_MUTEX mutex;
    bool initialized;
} TxArray;

// --- API-Funktionen ---
UINT TxArray_Init(TxArray* arr, CHAR* mutex_name, void* data_pool, size_t element_size, size_t max_elements);
UINT TxArray_Add(TxArray* arr, const void* element);
UINT TxArray_Get(const TxArray* arr, size_t index, void* out_element);
UINT TxArray_Set(TxArray* arr, size_t index, const void* element);
UINT TxArray_Remove(TxArray* arr, size_t index);
UINT TxArray_Clear(TxArray* arr);
size_t TxArray_Count(const TxArray* arr);

#ifdef __cplusplus
}
#endif

#endif // COMMON_UTILS_TX_ARRAY_H
