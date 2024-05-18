// Author: Grayson Kippes
// Date: 5/12/2024
// Description: type-generic stack struct and functions.

#ifndef DATASTUFF_STACK_H
#define DATASTUFF_STACK_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdbool.h>
#include <stddef.h>

// This struct represents an array-backed stack.
typedef struct Stack {

    // Internal array that implements the stack.
    size_t size;        // The current number of items on this stack.
    size_t capacity;    // The total space of items in this stack.
    void *pArray;       // Pointer to array that implements this stack.

    // Operational state.
    size_t objectSize;    // Fixed size of the type of object stored on this stack.

} Stack;

// Returns a new stack with a capacity at least as big as the specified initial capacity,
//  and the specified object size.
Stack newStack(const size_t initCapacity, const size_t objectSize);

// Frees the memory containing the array that backs this stack.
void deleteStack(Stack *const pStack);

// Returns true if the stack's state is valid, false otherwise.
bool stackValidate(const Stack stack);

// Returns true if the stack is empty, false otherwise.
bool stackIsEmpty(const Stack stack);

// Returns true if the stack is full, false otherwise.
bool stackIsFull(const Stack stack);

// Pushes an element onto the stack.
void stackPush(Stack *const pStack, const void *const pValue);

// Pops an element off the stack and moves it into pValue if it is not null.
void stackPop(Stack *const pStack, void *pValue);

// Returns the top element on the stack in pValue.
void stackPeek(const Stack stack, void *pValue);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // DATASTUFF_STACK_H