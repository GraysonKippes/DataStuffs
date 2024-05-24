#include "LinkedList.h"

#include <stdlib.h>
#include <string.h>

static LinkedListNode *newLinkedListNode(const LinkedList linkedList, void *const pObject);

LinkedList newLinkedList(const size_t objectSize) 
{
    return (LinkedList){
        .pHeadNode = NULL,
        .pTailNode = NULL,
        .objectSize = objectSize
    };
}

void deleteLinkedList(LinkedList *const pLinkedList)
{
    if (!pLinkedList) {
        return;
    }

    while (pLinkedList->pHeadNode) {
        LinkedListNode *pNode = pLinkedList->pHeadNode;
        pLinkedList->pHeadNode = pNode->pNextNode;
        if (pNode->pObject) {
            free(pNode->pObject);
        }
        free(pNode);
    }
    pLinkedList->pTailNode = NULL;
}

bool linkedListValidate(const LinkedList linkedList)
{
    return ((linkedList.pHeadNode && linkedList.pTailNode) || (!linkedList.pHeadNode && !linkedList.pTailNode))
        && linkedList.objectSize > 0;
}

bool linkedListIsEmpty(const LinkedList linkedList)
{
    return !linkedList.pHeadNode && !linkedList.pTailNode; 
}

void linkedListInsertFront(LinkedList *const pLinkedList, void *const pObject)
{
    if (!pLinkedList || !pObject) {
        return;
    } else if (!linkedListValidate(*pLinkedList) || linkedListIsEmpty(*pLinkedList)) {
        return;
    }

    LinkedListNode *pNewNode = newLinkedListNode(*pLinkedList, pObject);
    if (!pNewNode) {
        return;
    }
    pNewNode->pNextNode = pLinkedList->pHeadNode;

    pLinkedList->pHeadNode = pNewNode;
    if (!pLinkedList->pTailNode) {
        pLinkedList->pTailNode = pNewNode;
    }
}

void linkedListInsertBack(LinkedList *const pLinkedList, void *const pObject)
{
    if (!pLinkedList || !pObject) {
        return;
    } else if (!linkedListValidate(*pLinkedList)) {
        return;
    }

    LinkedListNode *pNewNode = newLinkedListNode(*pLinkedList, pObject);
    if (!pNewNode) {
        return;
    }

    if (pLinkedList->pTailNode) {
        pLinkedList->pTailNode->pNextNode = pNewNode;
    }
    pLinkedList->pTailNode = pNewNode;
    if (!pLinkedList->pHeadNode) {
        pLinkedList->pHeadNode = pNewNode;
    }
}

LinkedListNode *linkedListInsertAfter(LinkedList *const pLinkedList, LinkedListNode *const pNode, void *const pObject)
{
    if (!pLinkedList || !pNode || !pObject) {
        return NULL;
    } else if (!linkedListValidate(*pLinkedList)) {
        return NULL;
    }

    LinkedListNode *pNewNode = newLinkedListNode(*pLinkedList, pObject);
    if (!pNewNode) {
        return NULL;
    }
    pNewNode->pNextNode = pNode->pNextNode;

    pNode->pNextNode = pNewNode;
    if (pNode == pLinkedList->pTailNode) {
        pLinkedList->pTailNode = pNewNode;
    }

    return pNewNode;
}

void linkedListRemoveFront(LinkedList *const pLinkedList)
{
    if (!pLinkedList) {
        return;
    } else if (!linkedListValidate(*pLinkedList) || !pLinkedList->pHeadNode) {
        return;
    }

    LinkedListNode *pNode = pLinkedList->pHeadNode;
    pLinkedList->pHeadNode = pLinkedList->pHeadNode->pNextNode;
    if (pNode->pObject) {
        free(pNode->pObject);
    }
    free(pNode);
    if (pLinkedList->pHeadNode == NULL) {
        pLinkedList->pTailNode = NULL;
    }
}

static LinkedListNode *newLinkedListNode(const LinkedList linkedList, void *const pObject)
{
    if (!pObject) {
        return NULL;
    }

    LinkedListNode *pNewNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    if (!pNewNode) {
        return NULL;
    }

    pNewNode->pObject = malloc(linkedList.objectSize);
    if (!pObject) {
        free(pNewNode);
        return NULL;
    }
    memcpy(pNewNode->pObject, pObject, linkedList.objectSize);
    pNewNode->pNextNode = NULL;

    return pNewNode;
}