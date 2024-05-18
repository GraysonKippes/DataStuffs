#include <stdio.h>

#include "BHeap.h"
#include "BinarySearchTree.h"
#include "CmpFunc.h"
#include "EqFunc.h"
#include "HashTable.h"
#include "Heap.h"
#include "LinkedList.h"
#include "Stack.h"

#define ARR_LEN 10
static const int arr_len = ARR_LEN;

static int testBST(void);
static int testHeap(void);

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	printf("Hello world!\n");
	//testBST();
	//testHeap();
	const size_t pageSize = getPageSize();
	printf("pageSize = %llu\n", pageSize);
	
	return 0;
}

static int testBST(void)
{
	BinarySearchTree bst = newBinarySearchTree(sizeof(int), cmpFuncInt);
	
	int vals[ARR_LEN];
	for (int i = 0; i < arr_len; ++i)
		vals[i] = (i + 1) * 10;
	
	bstInsert(&bst, &vals[0]);
	bstInsert(&bst, &vals[5]);
	bstInsert(&bst, &vals[3]);
	bstInsert(&bst, &vals[7]);
	bstInsert(&bst, &vals[2]);
	bstInsert(&bst, &vals[9]);
	bstInsert(&bst, &vals[1]);
	bstInsert(&bst, &vals[4]);
	bstInsert(&bst, &vals[6]);
	bstInsert(&bst, &vals[8]);

	LinkedList traversal = bstTraverseInOrder(bst);

	int counter = 0;
	for (LinkedListNode *pNode = traversal.pHeadNode; pNode != NULL; pNode = pNode->pNextNode) {
		const int value = *(int *)((BinarySearchTreeNode *)pNode->pObject)->pObject;
		printf("%i: %i\n", counter, value);
		counter += 1;
	}

	deleteLinkedList(&traversal);
	deleteBinarySearchTree(&bst);
	return 0;
}

static int testHeap(void)
{
	Heap heap = newHeap(64, sizeof(int), cmpFuncInt);

	int vals[ARR_LEN];
	for (int i = 0; i < arr_len; ++i)
		vals[i] = (i + 1) * 10;

	heapPush(&heap, &vals[5]);
	heapPush(&heap, &vals[9]);
	heapPush(&heap, &vals[1]);
	heapPush(&heap, &vals[6]);
	heapPush(&heap, &vals[4]);
	heapPush(&heap, &vals[2]);
	heapPush(&heap, &vals[3]);
	heapPush(&heap, &vals[8]);
	heapPush(&heap, &vals[7]);
	heapPush(&heap, &vals[0]);

	for (int i = 0; i < arr_len; ++i) {
		printf("%i:\t", i);
		if (heap.ppArray[i]) {
			const int val = *(int *)heap.ppArray[i];
			printf("%i\n", val);
		} else {
			printf("NULL\n");
		}
	}

	const int insert = 69;
	int extract = 0;
	heapPopPush(&heap, &extract, &insert);
	printf("extr:\t%i\n", extract);

	for (int i = 0; i < arr_len; ++i) {
		printf("%i:\t", i);
		if (heap.ppArray[i]) {
			const int val = *(int *)heap.ppArray[i];
			printf("%i\n", val);
		} else {
			printf("NULL\n");
		}
	}

	deleteHeap(&heap);
}