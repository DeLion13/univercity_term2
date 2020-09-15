#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <progbase.h>
#include <progbase/console.h>

#include "min_heap.h"

int main() {
    srand(time(NULL));
    system("clear");

    Console_setCursorAttribute(BG_INTENSITY_BLUE);
    printf("-----------INSERTING-----------\n");
    Console_reset();

    printf("\nMassive: ");

    MinHeap * heap = MinHeap_alloc();
    MinHeap * heap2 = MinHeap_alloc();

    int cap = 12;
    int mass[cap];

    for (int i = 0; i < cap; i++) {
        mass[i] = rand() % (999 - 1 + 1) + 1;
    }

    Console_setCursorAttribute(FG_INTENSITY_MAGENTA);
    for (int i = 0; i < cap; i++) {
        printf("%d ", mass[i]);
    }
    Console_reset();
    
    printf("\n");

    for (int i = 0; i < cap; i++) {
        MinHeap_insert(heap, mass[i]);
    }

    MinHeap_print(heap);
    printf("\n");

    Console_setCursorAttribute(BG_INTENSITY_BLUE);
    printf("\n-----------HEAPIFY-----------\n");
    Console_reset();

    int cap2 = 12;
    int mass2[cap2];

    for (int i = 0; i < cap2; i++) {
        mass2[i] = rand() % (999 - 1 + 1) + 1;
    }

    printf("\nMassive: ");
    Console_setCursorAttribute(FG_INTENSITY_MAGENTA);
    for (int i = 0; i < cap2; i++) {
        printf("%d ", mass2[i]);
    }
    Console_reset();
    printf("\n");

    for (int i = 0; i < cap2; i++) {
        heap2 -> size++;
        heap2 -> tree[i] = mass2[i];

    }

    MinHeap_heapify(heap2);

    MinHeap_print(heap2);

    printf("\n");

    Console_setCursorAttribute(BG_INTENSITY_BLUE);
    printf("\n-----------DELETING-----------\n");
    Console_reset();

    int key = heap2 -> tree[3];

    printf("Delete element: %d\n", key);
    MinHeap_delete(heap2, key);

    MinHeap_print(heap2);

    MinHeap_dealloc(heap);
    MinHeap_dealloc(heap2);

    return 0;
}