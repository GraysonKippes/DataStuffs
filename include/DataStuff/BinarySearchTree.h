// Author: Grayson Kippes
// Date: 4/24/2024
// Description: type-generic binary search tree struct and functions.

#ifndef DATASTUFF_BINARY_SEARCH_TREE_H
#define DATASTUFF_BINARY_SEARCH_TREE_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include <stdbool.h>
#include <stddef.h>
#include "CmpFunc.h"
#include "LinkedList.h"

typedef struct BinarySearchTreeNode {
    void *pObject;
    struct BinarySearchTreeNode *pLeftChild;
    struct BinarySearchTreeNode *pRightChild;
} BinarySearchTreeNode;

typedef struct BinarySearchTree {
    BinarySearchTreeNode *pRootNode;
    size_t height;      // Length of longest path in this tree.
    size_t objectSize;  // Size of each element in this tree.
    CmpFunc cmpFunc;    // Function used for comparing objects within this tree.
} BinarySearchTree;

// Creates a new binary search tree with the specified object size and object comparison function.
BinarySearchTree newBinarySearchTree(const size_t objectSize, CmpFunc cmpFunc);

// Frees all the nodes inside the binary search tree.
// Returns true if the function executed successfully, false otherwise.
bool deleteBinarySearchTree(BinarySearchTree *const pBst);

// Returns true if the binary search tree has valid data, false otherwise.
bool bstValidate(const BinarySearchTree bst);

// Inserts a new node into the binary search tree containing the specified value.
// Returns true if the function executed successfully, false otherwise.
bool bstInsert(BinarySearchTree *const pBst, const void *const pObject);

// Searches for a node containing the specified value in the binary search tree.
// Returns true if the function executed successfully, false otherwise.
bool bstSearch(BinarySearchTree *const pBst, const void *const pObject, BinarySearchTreeNode **const ppNode);

// Deletes a node containing the specified value in the binary search tree.
// Returns true if the function if such a node was successfully found and deleted, false otherwise.
bool bstRemove(BinarySearchTree *const pBst, const void *const pObject);

// Returns a linked list containing the nodes in the binary search tree from an in-order traversal.
LinkedList bstTraverseInOrder(const BinarySearchTree bst);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // DATASTUFF_BINARY_SEARCH_TREE_H
