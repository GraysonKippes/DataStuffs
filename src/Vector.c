#include "Vector.h"

#include <stdlib.h>
#include <string.h>

Vector newVector(const size_t initialCapacity, const size_t objectSize)
{
    Vector vector = {
        .size = 0,
        .capacity = 0,
        .pArray = NULL,
        .objectSize = objectSize
    };

    if (vector.objectSize == 0) {
        return vector;
    }

    const size_t capacity = initialCapacity > 0 ? initialCapacity : 16;
    const size_t arraySize = capacity * vector.objectSize;
    vector.pArray = malloc(arraySize);
    if (vector.pArray) {
        memset(vector.pArray, 0, arraySize);
        vector.capacity = capacity;
    }
    return vector;
}

void deleteVector(Vector *const pVector)
{
    if (!pVector) {
        return;
    }

    free(pVector->pArray);
    pVector->capacity = 0;
    pVector->size = 0;
    pVector->objectSize = 0;
}