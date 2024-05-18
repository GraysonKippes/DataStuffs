// Author: Grayson Kippes
// Date: 5/16/2024
// Description: type-generic B-heap struct and functions.

#ifndef DATASTUFF_BHEAP_H
#define DATASTUFF_BHEAP_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdbool.h>
#include <stddef.h>
#include "CmpFunc.h"

typedef struct BHeap {

    size_t size;
    size_t capacity;
    void **ppArray;

    const size_t objectSize;
    const CmpFunc cmpFunc;

} BHeap;

size_t getPageSize(void);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // DATASTUFF_BHEAP_H