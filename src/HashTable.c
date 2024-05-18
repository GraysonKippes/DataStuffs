#include "HashTable.h"

#include <stdlib.h>
#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>

HashTable newHashTable(const size_t initCapacity, const size_t objectSize, const EqFunc equalsFunc)
{
    static const size_t defaultInitCapacity = 16;

    HashTable hashTable = {
        .size = 0,
        .capacity = 0,
        .ppArray = NULL,
        .objectSize = objectSize,
        .equalsFunc = equalsFunc
    };

    if (hashTable.objectSize == 0 || hashTable.equalsFunc == NULL) {
        return hashTable;
    }

    const size_t capacity = initCapacity > 0 ? initCapacity : defaultInitCapacity;
    const size_t arraySize = capacity * sizeof(void *);
    hashTable.ppArray = malloc(arraySize);
    if (hashTable.ppArray) {
        memset(hashTable.ppArray, 0, arraySize);
        hashTable.capacity = capacity;
    }
    return hashTable;
}

void deleteHashTable(HashTable *const pHashTable)
{
    if (!pHashTable) {
        return;
    }

    if (pHashTable->ppArray) {
        for (size_t i = 0; i < pHashTable->capacity; ++i) {
            if (pHashTable->ppArray[i]) {
                free(pHashTable->ppArray[i]);
                pHashTable->ppArray[i] = NULL;
            }
        }
        free(pHashTable->ppArray);
        pHashTable->ppArray = NULL;
    }
    pHashTable->capacity = 0;
    pHashTable->size = 0;
}

bool hashTableValidate(const HashTable hashTable)
{
    return hashTable.capacity > 0
        && hashTable.ppArray != NULL
        && hashTable.objectSize > 0
        && hashTable.equalsFunc != NULL;
}

// TODO - PLACEHOLDER
static size_t hashInt(const HashTable hashTable, void *const pValue)
{
    if (hashTable.capacity == 0 || !pValue) {
        return 0;
    }

    const size_t modulo = hashTable.capacity - 1;
    const int value = *(int *)pValue;
    return (size_t)value % modulo;
}

void hashTableInsert(HashTable *const pHashTable, void *const pValue)
{
    if (!pHashTable || !pValue) {
        return;
    } else if (!hashTableValidate(*pHashTable)) {
        return;
    }

    size_t hashIndex = hashInt(*pHashTable, pValue);
    for (size_t i = 0; i < pHashTable->capacity; ++i) {
        if (!pHashTable->ppArray[hashIndex + i]) {
            hashIndex += i;
            break;
        }
    }

    pHashTable->ppArray[hashIndex] = malloc(pHashTable->objectSize);
    if (!pHashTable->ppArray) {
        return;
    }
    memcpy_s(pHashTable->ppArray[hashIndex], pHashTable->objectSize, pValue, pHashTable->objectSize);
    pHashTable->size += 1;
}