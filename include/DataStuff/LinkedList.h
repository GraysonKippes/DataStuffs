// Author: Grayson Kippes
// Date: 5/12/2024
// Description: type-generic linked list struct and functions.

#ifndef DATASTUFF_LINKED_LIST_H
#define DATASTUFF_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdbool.h>
#include <stddef.h>

typedef struct LinkedListNode {
    void *pObject;
    struct LinkedListNode *pNextNode;
} LinkedListNode;

// This struct represents a singly linked list.
typedef struct LinkedList {
    LinkedListNode *pHeadNode;
    LinkedListNode *pTailNode;
    size_t objectSize;
} LinkedList;

// Returns a new empty singly linked list.
LinkedList newLinkedList(const size_t objectSize);

// Frees the memory owned by the linked list.
void deleteLinkedList(LinkedList *const pLinkedList);

// Returns true if the linked list's state is valid, false otherwise.
bool linkedListValidate(const LinkedList linkedList);

// Returns true if the linked list is empty, false otherwise.
bool linkedListIsEmpty(const LinkedList linkedList);

// Inserts a new node containing the given object at the front of the list.
void linkedListInsertFront(LinkedList *const pLinkedList, void *const pObject);

// Inserts a new node containing the given object at the back of the list.
void linkedListInsertBack(LinkedList *const pLinkedList, void *const pObject);

// Inserts a new node after the specified node in the linked list.
LinkedListNode *linkedListInsertAfter(LinkedList *const pLinkedList, LinkedListNode *const pNode, void *const pObject);

// Removes and deletes the head node in the linked list.
void linkedListRemoveFront(LinkedList *const pLinkedList);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // DATASTUFF_LINKED_LIST_H