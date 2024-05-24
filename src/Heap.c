#include "Heap.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Bubbles the last element up until heap property is restored.
static void heapUp(Heap *const pHeap, const size_t index);

// Bubbles the root element down until heap property is restored.
static void heapDown(Heap *const pHeap, const size_t index);

Heap newHeap(const size_t initCapacity, const size_t objectSize, CmpFunc cmpFunc)
{
    Heap heap = {
        .size = 0,
        .capacity = 0,
        .ppArray = NULL,
        .objectSize = objectSize,
        .cmpFunc = cmpFunc
    };

    if (heap.objectSize == 0) {
        return heap;
    }

    const size_t capacity = initCapacity > 0 ? initCapacity : 8;
    const size_t arraySize = capacity * sizeof(void *);
    heap.ppArray = malloc(arraySize);
    if (heap.ppArray) {
        memset(heap.ppArray, 0, arraySize);
        heap.capacity = capacity;
    }
    return heap;
}

void deleteHeap(Heap *const pHeap)
{
    if (!pHeap) {
        return;
    }

    if (pHeap->ppArray) {
        for (size_t i = 0; i < pHeap->capacity; ++i) {
            if (pHeap->ppArray[i]) {
                free(pHeap->ppArray[i]);
                pHeap->ppArray[i] = NULL;
            }
        }
        free(pHeap->ppArray);
        pHeap->ppArray = NULL;
    }
    pHeap->capacity = 0;
    pHeap->size = 0;
    pHeap->objectSize = 0;
}

bool heapValidate(const Heap heap)
{
    return heap.size <= heap.capacity
        && heap.capacity > 0 
        && heap.ppArray != NULL
        && heap.objectSize > 0
        && heap.cmpFunc != NULL;
}

bool heapIsEmtpy(const Heap heap)
{
    return heap.size == 0;
}

bool heapIsFull(const Heap heap)
{
    return heap.size == heap.capacity;
}

size_t heapSearch(const Heap heap, const void *const pObject)
{
    static const size_t invalidIndex = SIZE_MAX;
    if (!pObject || !heapValidate(heap)) {
        return invalidIndex;
    }

    for (size_t i = 0; i < heap.size; ++i) {
        if (heap.cmpFunc(heap.ppArray[i], pObject) == 0) {
            return i;
        }
    }
    return invalidIndex;
}

size_t heapReverseSearch(const Heap heap, const void *const pObject)
{
    static const size_t invalidIndex = SIZE_MAX;
    if (!pObject || !heapValidate(heap)) {
        return invalidIndex;
    }

    for (size_t i = heap.size; i > 0; ++i) {
        if (heap.cmpFunc(heap.ppArray[i - 1], pObject) == 0) {
            return i;
        }
    }
    return invalidIndex;
}

void heapRemove(Heap *const pHeap, const size_t index)
{
    if (!pHeap) {
        return;
    } else if (!heapValidate(*pHeap) || index >= pHeap->size) {
        return;
    }

    void *const pDeleteObject = pHeap->ppArray[index];
    pHeap->ppArray[index] = pHeap->ppArray[pHeap->size - 1];
    pHeap->ppArray[pHeap->size - 1] = NULL;
    pHeap->size -= 1;
    const int cmpResult = pHeap->cmpFunc(pHeap->ppArray[index], pDeleteObject);
    if (cmpResult == -1) {
        heapUp(pHeap, index);
    } else if (cmpResult == 1) {
        heapDown(pHeap, index);
    }
    free(pDeleteObject);
}

void heapPush(Heap *const pHeap, const void *const pObject)
{
    if (!pHeap || !pObject) {
        return;
    } else if (!heapValidate(*pHeap)) {
        return;
    }

    if (heapIsFull(*pHeap)) {
        // TODO - resize here.
        return;
    }

    // Insert element into leftmost empty slot on bottom level.
    const size_t insertIndex = pHeap->size;
    pHeap->ppArray[insertIndex] = malloc(pHeap->objectSize);
    if (!pHeap->ppArray[insertIndex]) {
        return;
    }
    memcpy(pHeap->ppArray[insertIndex], pObject, pHeap->objectSize);
    pHeap->size += 1;
    heapUp(pHeap, insertIndex);
}

void heapPop(Heap *const pHeap, void *const pObject)
{
    if (!pHeap || !pObject) {
        return;
    } else if (!heapValidate(*pHeap) || heapIsEmtpy(*pHeap)) {
        return;
    }

    // Extract first (i.e. highest-priority) element.
    if (!pHeap->ppArray) {
        return;
    }
    memcpy(pObject, pHeap->ppArray[0], pHeap->objectSize);
    free(pHeap->ppArray[0]);
    pHeap->size -= 1;

    // Replace first element with last element.
    const size_t replaceIndex = pHeap->size;
    pHeap->ppArray[0] = pHeap->ppArray[replaceIndex];
    // Check if the pointer to the replacement element was NULL.
    if (!pHeap->ppArray[0]) {   
        return;
    }
    pHeap->ppArray[replaceIndex] = NULL;
    heapDown(pHeap, 0);
}

void heapPushPop(Heap *const pHeap, const void *const pPushObject, void *const pPopObject)
{
    if (!pHeap || !pPushObject || !pPopObject) {
        return;
    } else if (!heapValidate(*pHeap) || !pHeap->ppArray[0]) {
        return;
    }

    // If the heap is empty or the push object is higher priority than the current root,
    //  then just simply return the push object and not mutate the heap at all.
    if (heapIsEmtpy(*pHeap) || pHeap->cmpFunc(pPushObject, pHeap->ppArray[0]) == -1) {
        memcpy(pPopObject, pPushObject, pHeap->objectSize);
        return;
    }

    // Extract the root object into pPopObject.
    memcpy(pPopObject, pHeap->ppArray[0], pHeap->objectSize);

    // Copy the push object into a new object to insert into the heap.
    void *const pInsertObject = malloc(pHeap->objectSize);
    if (!pInsertObject) {
        return;
    }
    memcpy(pInsertObject, pPushObject, pHeap->objectSize);
    free(pHeap->ppArray[0]);
    pHeap->ppArray[0] = pInsertObject;
    heapDown(pHeap, 0);
}

void heapPopPush(Heap *const pHeap, void *const pPopObject, const void *const pPushObject)
{
    if (!pHeap || !pPopObject || !pPushObject) {
        return;
    } else if (!heapValidate(*pHeap) || !pHeap->ppArray[0]) {
        return;
    }

    // If the heap is empty, just use heapPush and not return anything in pPopObject.
    if (heapIsEmtpy(*pHeap)) {
        heapPush(pHeap, pPushObject);
        return;
    }

    // Extract the root object into pPopObject.
    memcpy(pPopObject, pHeap->ppArray[0], pHeap->objectSize);

    // Copy the push object into a new object to insert into the heap.
    void *const pInsertObject = malloc(pHeap->objectSize);
    if (!pInsertObject) {
        return;
    }
    memcpy(pInsertObject, pPushObject, pHeap->objectSize);
    free(pHeap->ppArray[0]);
    pHeap->ppArray[0] = pInsertObject;
    heapDown(pHeap, 0);
}

static void heapUp(Heap *const pHeap, const size_t index)
{
    // Bubble-up last element.
    size_t swapIndex = index; // Index to object being bubbled up.
    while (true) {
        const size_t parentIndex = swapIndex > 0 ? (swapIndex - 1) / 2 : 0;
        if (pHeap->cmpFunc(pHeap->ppArray[swapIndex], pHeap->ppArray[parentIndex]) == -1) {
            void *const pSwapObject = pHeap->ppArray[parentIndex];
            pHeap->ppArray[parentIndex] = pHeap->ppArray[swapIndex];
            pHeap->ppArray[swapIndex] = pSwapObject;
            swapIndex = parentIndex;
        } else {
            break;
        }
    }
}

static void heapDown(Heap *const pHeap, const size_t index)
{
    // Bubble-down the replacement element.
    size_t swapIndex = index;
    while (true) {

        // Compute indices for both child objects.
        const size_t leftChildIndex = (swapIndex * 2) + 1;
        const size_t rightChildIndex = leftChildIndex + 1;
        if (rightChildIndex >= pHeap->capacity) {
            return;
        }

        // Pick the priotized child object.
        size_t childIndex = rightChildIndex;
        if (pHeap->cmpFunc(pHeap->ppArray[leftChildIndex], pHeap->ppArray[rightChildIndex]) == -1) {
            childIndex = leftChildIndex;
        }

        // If the replacement object is lower priority than its higher-priority child object, then swap them.
        // Otherwise, the heapification is done, so break out of the loop.
        if (pHeap->cmpFunc(pHeap->ppArray[swapIndex], pHeap->ppArray[childIndex]) == 1) {
            void *const pSwapObject = pHeap->ppArray[childIndex];
            pHeap->ppArray[childIndex] = pHeap->ppArray[swapIndex];
            pHeap->ppArray[swapIndex] = pSwapObject;
            swapIndex = childIndex;
        } else {
            break;
        }
    }
}