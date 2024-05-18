#include "Stack.h"

#include <stdlib.h>
#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>

Stack newStack(const size_t initCapacity, const size_t objectSize)
{
    static const size_t defaultInitCapacity = 16;

    Stack stack = {
        .size = 0,
        .capacity = 0,
        .pArray = NULL,
        .objectSize = objectSize
    };

    if (stack.objectSize == 0) {
        return stack;
    }

    const size_t capacity = initCapacity > 0 ? initCapacity : defaultInitCapacity;
    const size_t arraySize = capacity * objectSize;
    stack.pArray = malloc(arraySize);
    if (stack.pArray) {
        memset(stack.pArray, 0, arraySize);
        stack.capacity = capacity;
    }
    return stack;
}

void deleteStack(Stack *const pStack)
{
    if (!pStack) {
        return;
    }

    free(pStack->pArray);
    pStack->pArray = NULL;
    pStack->capacity = 0;
    pStack->size = 0;
}

bool stackValidate(const Stack stack)
{
    return stack.size <= stack.capacity
        && stack.capacity > 0
        && stack.pArray != NULL
        && stack.objectSize > 0;
}

bool stackIsEmpty(const Stack stack)
{
    return stack.size == 0;
}

bool stackIsFull(const Stack stack)
{
    return stack.size == stack.capacity;
}

void stackPush(Stack *const pStack, const void *const pValue)
{
    if (!pStack || !pValue) {
        return;
    } else if (!stackValidate(*pStack)) {
        return;
    }

    // If the stack's internal array is full, resize it.
    if (stackIsFull(*pStack)) {
        void *pResize = realloc(pStack->pArray, 2 * pStack->capacity * pStack->objectSize);
        if (!pResize) {
            return;
        }
        pStack->pArray = pResize;
        pStack->capacity *= 2;
    }

    memcpy(((unsigned char *)pStack->pArray + pStack->size * pStack->objectSize), pValue, pStack->objectSize);
    pStack->size += 1;
}

void stackPop(Stack *const pStack, void *pValue)
{
    if (!pStack) {
        return;
    } else if (!stackValidate(*pStack) || stackIsEmpty(*pStack)) {
        return;
    }

    if (pValue) {
        memcpy(pValue, ((unsigned char *)pStack->pArray + (pStack->size - 1) * pStack->objectSize), pStack->objectSize);
    }
    pStack->size -= 1;
}

void stackPeek(const Stack stack, void *pValue)
{
    if (!stackValidate(stack) || stackIsEmpty(stack)) {
        return;
    }
    memcpy(pValue, ((unsigned char *)stack.pArray + (stack.size - 1) * stack.objectSize), stack.objectSize);
}