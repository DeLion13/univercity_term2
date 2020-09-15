#include "min_heap.h"

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


MinHeap * MinHeap_alloc() {
    MinHeap * this = malloc(sizeof(MinHeap));
    this -> size = 0;
    this -> capacity = 20;
    this -> tree = malloc(sizeof(int) * this -> capacity);

    return this;
}

void MinHeap_dealloc(MinHeap * self) {
    free(self -> tree);
    free(self);
}

static void MinHeap_realloc(MinHeap * self, int newCapacity) {
    int * newItems = realloc(self -> tree, sizeof(int) * newCapacity);
    if (newItems == NULL) {
        fprintf(stderr, "Reallocation error");
        abort();
    }
    self -> tree = newItems;
    self -> capacity = newCapacity;
}

int MinHeap_findMin(MinHeap * self) {
    return self -> tree[0];
}

int MinHeap_extractMin(MinHeap * self) {
    return MinHeap_delete(self, MinHeap_findMin(self));
}

int MinHeap_delete(MinHeap * self, int key) {
    int index = 0;
    for (int i = 0; i < self -> size; i++) {
        if (self -> tree[i] == key) {
            index = i;
            break;
        }
    }

    for (int i = index; i < self -> size; i++) {
        self -> tree[i] = self -> tree[i + 1];
    }
    self -> size--;

    MinHeap_heapify(self);

    return index;
}

bool MinHeap_heapify(MinHeap * self) {
    bool was = false;
    for (int j = self -> size - 1; j >= 0; j--) {
        int i = j;

        int leftChild;
        int rightChild;
        int largestChild;

        while (true) {
            leftChild = 2 * i + 1;
            rightChild = 2 * i + 2;
            largestChild = i;

            if (leftChild < self -> size && self -> tree[leftChild] < self -> tree[largestChild]) {
                if (was == false) {
                    Console_setCursorAttribute(FG_INTENSITY_RED);
                    printf("\nERROR! Not minimal binary heap or not ended! Process of heapifying...\n");
                    Console_reset();
                    was = true;
                }
                largestChild = leftChild;
            }

            if (rightChild < self -> size && self -> tree[rightChild] < self -> tree[largestChild]) {
                if (was == false) {
                    Console_setCursorAttribute(FG_INTENSITY_RED);
                    printf("\nERROR! Not minimal binary heap or not ended! Process of heapifying...\n");
                    Console_reset();
                    was = true;
                }
                largestChild = rightChild;
            }

            if (largestChild == i) {
                break;
            }

            int temp = self -> tree[i];
            self -> tree[i] = self -> tree[largestChild];
            self -> tree[largestChild] = temp;
            i = largestChild; 
        }
    }
    return true;
}

void MinHeap_insert(MinHeap * self, int key) {
    Console_setCursorAttribute(BG_INTENSITY_BLUE);
    printf("\n                                         ");
    Console_reset();
    Console_setCursorAttribute(FG_INTENSITY_GREEN);
    printf("\nInserted: %d\n", key);
    Console_reset();
    if (self -> size == self -> capacity) {
        MinHeap_realloc(self, self -> capacity * 2);
    }

    self -> size++;
    self -> tree [self -> size - 1] = key;

    printf("\nsize: %lu\n", self -> size);

    int i = self -> size - 1;
    int parent = (i - 1) / 2;

    while (self -> size > 1 && i > 0 && self -> tree[parent] > self -> tree[i]) {
        Console_setCursorAttribute(FG_INTENSITY_GREEN);
        printf("\tswap: %d and %d\n", self -> tree[i], self -> tree[parent]);
        Console_reset();

        int temp = self -> tree[i];
        self -> tree[i] = self -> tree[parent];
        self -> tree[parent] = temp;

        i = parent;
        parent = (i - 1) / 2;
    }

    printf("\n\tHeap:\t");
    for (int i = 0; i < self -> size; i++) {
        printf("%d ", self -> tree[i]);
    }
    printf("\n");
}

void printIn(int count) {
    printf("\n");
    for (int i = 0; i < count; i++) {
            printf("|  \\  ");
        
    }
    printf("\n");
    for (int i = 0; i < count; i++) {
        printf("|   \\ ");
    }
    printf("\n");
    for (int i = 0; i < count; i++) {
        printf("|    \\");
    }
}

void MinHeap_print(MinHeap * self) {
    printf("\n-");
    for (int i = 0; i < self -> size; i++) {
        printf("------");
    }
    printf("\n|");
    for (int i = 0; i < self -> size; i++) {
        Console_setCursorAttribute(FG_INTENSITY_MAGENTA);
        printf(" %3d ", i);
        Console_reset();
        printf("|");
    }
    printf("\n-");
    for (int i = 0; i < self -> size; i++) {
        printf("------");
    }
    printf("\n|");
    for (int i = 0; i < self -> size; i++) {
        Console_setCursorAttribute(FG_INTENSITY_MAGENTA);
        printf(" %3d ", self -> tree[i]);
        Console_reset();
        printf("|");
    }
    printf("\n-");
    for (int i = 0; i < self -> size; i++) {
        printf("------");
    }
    printf("\n");
}

size_t MinHeap_size(MinHeap * self) {
    return self -> size;
}