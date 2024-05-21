// Author: Grayson Kippes
// Date: 5/11/2024
// Description: type-generic heap struct and functions.

#ifndef DATASTUFF_HEAP_H
#define DATASTUFF_HEAP_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdbool.h>
#include <stddef.h>
#include "CmpFunc.h"

// This struct represents a heap.
typedef struct Heap {

    size_t size;
    size_t capacity;
    void **ppArray;

    size_t objectSize;
    CmpFunc cmpFunc;

} Heap;

// Returns a new heap with a capacity at least as large as initCapacity,
//  the specified object size and comparison function.
// An object that gets less-than (-1) when passed into the comparison function with another object
//  is prioritized over the other object.
// In other words, a comparison function that returns less-than (-1) for smaller numbers
//  results in a min-heap, and a comparison function that returns less-than (1) for larger
//  numbers results in a max-heap.
Heap newHeap(const size_t initCapacity, const size_t objectSize, CmpFunc cmpFunc);

// Frees the memory held by the heap, and resets ppArray to NULL.
// The heap's capacity and size are set to 0 as well.
void deleteHeap(Heap *const pHeap);

// Returns true if the heap's state is valid, false otherwise.
bool heapValidate(const Heap heap);

// Returns true if the heap is empty, false otherwise.
bool heapIsEmtpy(const Heap heap);

// Returns true if the heap is full, false otherwise.
bool heapIsFull(const Heap heap);

// Returns the index to the first object in the heap array equal to *pObject,
//  or SIZE_MAX if no such object is found. 
size_t heapSearch(const Heap heap, const void *const pObject);

// Returns the index to the last object in the heap array equal to *pObject,
//  or SIZE_MAX if no such object is found. 
size_t heapReverseSearch(const Heap heap, const void *const pObject);

// Removes an arbitrary element from the heap and restores the heap property.
void heapRemove(Heap *const pHeap, const size_t index);

// Inserts the given object into the heap.
void heapPush(Heap *const pHeap, const void *const pObject);

// Extracts the front (i.e. highest priority) object from the heap, returning it in pObject.
void heapPop(Heap *const pHeap, void *const pObject);

// Inserts the given object into the heap, then extracts the front object from the heap.
// More efficient than simply calling heapPush then heapPop.
void heapPushPop(Heap *const pHeap, const void *const pPushObject, void *const pPopObject);

// Extracts the front object from the heap, then inserts the given object into the heap.
// More efficient than simply calling heapPop then heapPush.
void heapPopPush(Heap *const pHeap, void *const pPopObject, const void *const pPushObject);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // DATASTUFF_HEAP_H