// Author: Grayson Kippes
// Date: 5/21/2024
// Description: type-generic vector struct and functions.

#ifndef DATASTUFF_VECTOR_H
#define DATASTUFF_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdbool.h>
#include <stddef.h>

typedef struct Vector {

    size_t size;
    size_t capacity;
    void *pArray;

    size_t objectSize;

} Vector;

Vector newVector(const size_t initialCapacity, const size_t objectSize);

void deleteVector(Vector *const pVector);



#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // DATASTUFF_VECTOR_H