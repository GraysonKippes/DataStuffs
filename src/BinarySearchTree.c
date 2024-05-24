#include "BinarySearchTree.h"

#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

static BinarySearchTreeNode *newBinarySearchTreeNode(void);

BinarySearchTree newBinarySearchTree(const size_t objectSize, CmpFunc cmpFunc)
{
    return (BinarySearchTree){
        .pRootNode = NULL,
        .height = 0,
        .objectSize = objectSize,
        .cmpFunc = cmpFunc
    };
}

bool deleteBinarySearchTree(BinarySearchTree *const pBst)
{
    if (!pBst) {
        return false;
    }

    LinkedList deletionQueue = newLinkedList(sizeof(BinarySearchTreeNode *));
    linkedListInsertBack(&deletionQueue, &pBst->pRootNode);

    while (!linkedListIsEmpty(deletionQueue)) {
        BinarySearchTreeNode *pBstNode = *(BinarySearchTreeNode **)deletionQueue.pHeadNode->pObject;

        // If the BST node exists, push a new queue node for each of its children.
        if (pBstNode) {
            linkedListInsertBack(&deletionQueue, &pBstNode->pLeftChild);
            linkedListInsertBack(&deletionQueue, &pBstNode->pRightChild);

            // Free the BST node and its object.
            if (pBstNode->pObject) {
                free(pBstNode->pObject);
                pBstNode->pObject = NULL;
            }
            free(pBstNode);
        }
        linkedListRemoveFront(&deletionQueue);
    }

    pBst->pRootNode = NULL;
    pBst->height = 0;
    pBst->objectSize = 0;
    pBst->cmpFunc = NULL;

    return true;
}

bool bstValidate(const BinarySearchTree bst)
{
    return bst.objectSize > 0 && bst.cmpFunc;
}

bool bstInsert(BinarySearchTree *const pBst, const void *const pObject)
{
    if (!pBst || !pObject) {
        return false;
    } else if (!bstValidate(*pBst)) {
        return false;
    }

    // Find where to insert the node.
    size_t nodeLevel = 0; // Height at which the node is inserted.
    BinarySearchTreeNode **ppInsertionPoint = &pBst->pRootNode;
    while (*ppInsertionPoint) {
        switch (pBst->cmpFunc(pObject, (**ppInsertionPoint).pObject)) {
            default:
                return false;
            case -1:
                ppInsertionPoint = &(**ppInsertionPoint).pLeftChild;
                break;
            case 0:
                return true;
            case 1:
                ppInsertionPoint = &(**ppInsertionPoint).pRightChild;
                break;
        }
        nodeLevel += 1;
    }

    // Node creation.
    BinarySearchTreeNode *const pNode = newBinarySearchTreeNode();
    if (!pNode) {
        return false;
    }
    pNode->pObject = malloc(pBst->objectSize);
    if (!pNode->pObject) {
        free(pNode);
        return false;
    }
    memcpy(pNode->pObject, pObject, pBst->objectSize);

    // Node insertion.
    *ppInsertionPoint = pNode;
    size_t newHeight = nodeLevel > 0 ? nodeLevel - 1 : 0;
    pBst->height = newHeight > pBst->height ? newHeight : pBst->height;

    return true;
}

bool bstSearch(BinarySearchTree *const pBst, const void *const pObject, BinarySearchTreeNode **const ppNode)
{
    if (!pBst || !pObject || !ppNode) {
        return false;
    } else if (!bstValidate(*pBst)) {
        return false;
    }

    BinarySearchTreeNode *pNode = pBst->pRootNode;
    while (pNode) {
        switch (pBst->cmpFunc(pObject, pNode->pObject)) {
            default:
                return false;
            case -1:
                pNode = pNode->pLeftChild;
                break;
            case 0:
                goto end_loop;
            case 1:
                pNode = pNode->pRightChild;
                break;
        }
    }

end_loop:
    *ppNode = pNode;
    return true;
}

bool bstRemove(BinarySearchTree *const pBst, const void *const pObject)
{
    if (!pBst || !pObject) {
        return false;
    } else if (!bstValidate(*pBst)) {
        return false;
    }

    // Find the node to be deleted.
    BinarySearchTreeNode *pNode = pBst->pRootNode;
    BinarySearchTreeNode **ppDeletionPoint = NULL;
    while (pNode) {
        switch (pBst->cmpFunc(pObject, pNode->pObject)) {
            default:
                return false;
            case -1:
                ppDeletionPoint = &pNode->pLeftChild;
                pNode = pNode->pLeftChild;
                break;
            case 0:
                goto end_loop;
            case 1:
                ppDeletionPoint = &pNode->pRightChild;
                pNode = pNode->pRightChild;
                break;
        }
    }

end_loop:
    if (!pNode) {
        return true;
    }

    // Perform the deletion depending on which children exist.
    if (!pNode->pLeftChild && !pNode->pRightChild) {
        // Case: no children.
        *ppDeletionPoint = NULL;
        free(pNode);
        return true;
    }
    if (pNode->pLeftChild && !pNode->pRightChild) {
        // Case: only left child.
        *ppDeletionPoint = pNode->pLeftChild;
        free(pNode);
        return true;
    }
    if (!pNode->pLeftChild && pNode->pRightChild) {
        // Case: only left child.
        *ppDeletionPoint = pNode->pRightChild;
        free(pNode);
        return true;
    }
    if (pNode->pLeftChild && pNode->pRightChild) {
        // Case: both children.
        // Find the successor node and swap it with the node to be deleted.
        BinarySearchTreeNode **ppSuccessorNode = &pNode->pRightChild;
        while (*ppSuccessorNode && (*ppSuccessorNode)->pLeftChild) {
            ppSuccessorNode = &(*ppSuccessorNode)->pLeftChild;
        }
        BinarySearchTreeNode *pSuccessorNode = *ppSuccessorNode;
        pSuccessorNode->pLeftChild = pNode->pLeftChild;
        pSuccessorNode->pRightChild = pNode->pRightChild;
        *ppDeletionPoint = pSuccessorNode;
        *ppSuccessorNode = NULL;
        free(pNode);
        return true;
    }

    return false;
}

static void bstTraverseInOrderHelper(const BinarySearchTree bst, BinarySearchTreeNode *const pNode, LinkedList *const pQueue)
{
    if (pNode && pQueue) {
        bstTraverseInOrderHelper(bst, pNode->pLeftChild, pQueue);
        linkedListInsertBack(pQueue, pNode);
        bstTraverseInOrderHelper(bst, pNode->pRightChild, pQueue);
    }
}

LinkedList bstTraverseInOrder(const BinarySearchTree bst)
{
    if (!bstValidate(bst)) {
        return newLinkedList(0);
    }

    // Build a list of BST nodes.
    // Don't store the original pointers to nodes, so that they can't be mutated through the traversal.
    LinkedList queue = newLinkedList(sizeof(BinarySearchTreeNode));
    if (!linkedListValidate(queue)) {
        return queue;
    }
    bstTraverseInOrderHelper(bst, bst.pRootNode, &queue);
    return queue;
}

static BinarySearchTreeNode *newBinarySearchTreeNode(void)
{
    BinarySearchTreeNode *pNode = (BinarySearchTreeNode *const)malloc(sizeof(BinarySearchTreeNode));
    if (pNode) {
        pNode->pObject = NULL;
        pNode->pLeftChild = NULL;
        pNode->pRightChild = NULL;
    }
    return pNode;
}