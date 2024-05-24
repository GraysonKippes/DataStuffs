// Author: Grayson Kippes
// Date: 5/20/2024
// Description: interactive menu to test data structures.

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "BHeap.h"
#include "BinarySearchTree.h"
#include "CmpFunc.h"
#include "EqFunc.h"
#include "HashTable.h"
#include "Heap.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Vector.h"

static void menu(void);
static void menuPrintElements(const Heap heap);
static void menuPushElement(Heap *const pHeap);
static void menuPopElement(Heap *const pHeap);
static void menuSearchElement(const Heap heap);
static void menuRemoveElement(Heap *const pHeap);

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	menu();
	return 0;
}

static void menu(void)
{
	printf("Min-heap demo.");
	Heap heap = newHeap(64, sizeof(int), cmpFuncInt);
	bool menuRunning = true;
	while (menuRunning) {
		printf("(0) Exit.\n");
		printf("(1) Print number of elements.\n");
		printf("(2) Print heap capacity.\n");
		printf("(3) Print elements.\n");
		printf("(4) Push element.\n");
		printf("(5) Pop element.\n");
		printf("(6) Search for element.\n");
		printf("(7) Remove element.\n");
		printf("Please enter a command: ");
		int input = -1;
		scanf("%i", &input);
		if (input < 0 || input > 7) {
			printf("Error: invalid input. Please input command again.\n");
			continue;
		}

		switch(input) {
			case 0:
				printf("Exiting program.\n");
				menuRunning = false;
				break;
			case 1: 
				printf("The heap currently has %llu elements.\n", heap.size);
				break;
			case 2: 
				printf("The heap currently has a capacity of %llu.\n", heap.capacity);
				break;
			case 3:
				menuPrintElements(heap);
				break;
			case 4:
				menuPushElement(&heap);
				break;
			case 5:
				menuPopElement(&heap);
				break;
			case 6:
				menuSearchElement(heap);
				break;
			case 7:
				menuRemoveElement(&heap);
				break;
		}
	}

	deleteHeap(&heap);
}

static void menuPrintElements(const Heap heap) {
	printf("Printing %llu elements in the heap...\n", heap.size);
	for (size_t i = 0; i < heap.size; ++i) {
		const size_t leftChildIndex = (i << 1) + 1;
		const size_t rightChildIndex = leftChildIndex + 1;
		const int val = *(int *)heap.ppArray[i];
		printf("%llu: %i", i, val);
		if (leftChildIndex < heap.size) {
			printf(" -> %llu", leftChildIndex);
		}
		if (rightChildIndex < heap.size) {
			printf(", %llu", rightChildIndex);
		}
		printf("\n");
	}
}

static void menuPushElement(Heap *const pHeap) {
	printf("Please enter a value to insert (integer): ");
	int val = 0;
	scanf("%i", &val);
	heapPush(pHeap, &val);
}

static void menuPopElement(Heap *const pHeap) {
	int val = 0;
	heapPop(pHeap, &val);
	printf("Popped element %i from the heap.\n", val);
}

static void menuSearchElement(const Heap heap) {
	printf("Please enter a value to search for (integer): ");
	int val = 0;
	scanf("%i", &val);
	const size_t search = heapSearch(heap, &val);
	if (search < heap.size) {
		printf("Value %i found at position %llu in the heap.\n", val, search);
	} else {
		printf("Value %i not found in the heap.\n", val);
	}
}

static void menuRemoveElement(Heap *const pHeap) {
	printf("Please enter an index to remove from: ");
	size_t index = SIZE_MAX;
	scanf("%llu", &index);
	if (index < pHeap->size) {
		heapRemove(pHeap, index);
	} else {
		printf("Index %llu not within bounds of heap.\n", index);
	}
}