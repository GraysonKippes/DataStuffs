// Author: Grayson Kippes
// Date: 5/12/2024
// Description: type-generic hash table struct and functions.

#ifndef DATASTUFF_HASH_TABLE_H
#define DATASTUFF_HASH_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdbool.h>
#include <stddef.h>
#include "EqFunc.h"

typedef struct HashTable HashTable;
typedef bool (*HashFunc)(const HashTable hashTable, void *const pValue);

typedef struct HashTable {

    size_t size;        // Number of occupied buckets in this hash table.
    size_t capacity;    // Total number of buckets in this hash table.
    void **ppArray;     // Pointer to array of buckets.

    const size_t objectSize;    // Fixed size of the type of object store in this hash table.
    const EqFunc equalsFunc;    // Equality function to compare objects in this hash table.

} HashTable;

// Returns a new hash table with a capacity at least as big as the specified initial capacity,
//  and the specified object size and equality function.
HashTable newHashTable(const size_t initCapacity, const size_t objectSize, const EqFunc equalsFunc);

// Frees the memory held by the hash table, and resets ppArray to NULL.
void deleteHashTable(HashTable *const pHashTable);

bool hashTableValidate(const HashTable hashTable);

void hashTableInsert(HashTable *const pHashTable, void *const pValue);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // DATASTUFF_HASH_TABLE_H