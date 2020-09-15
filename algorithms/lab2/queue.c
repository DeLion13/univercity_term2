#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <progbase.h>
#include <progbase/console.h>
#include <time.h>
#include <progbase/canvas.h>

void Queue_init(Queue * self) {
    self -> capacity = 4;
    self -> size = 0;
    self -> first = 0;
    self -> last = 0;
    self -> items = malloc(sizeof(self->items) * self->capacity);

    if (self -> items == NULL) {
        fprintf(stderr, "Allocating error");
        abort();
    }
}
//
void Queue_deinit(Queue * self) {
    free(self -> items);
}
//
Queue * Queue_alloc(void) {
    Queue * self = malloc(sizeof(Queue));
    Queue_init(self);
    return self;
}
//
void Queue_free(Queue * self) {
    Queue_deinit(self);
    free(self);
}
//
void Queue_enqueue(Queue * self, int value) {
    srand(time(NULL));
    self -> items[self -> last] = value;
    if (self -> last == self -> capacity) {
        self -> last = 0;
    } else if (self -> last < self -> capacity){
        self->last += 1;
    }
    self -> size += 1;

    if (self -> last == self -> first) {
        int newCap = self -> capacity + 5;
        int k = rand() % (20000 - 1000 + 1) + 1000;
        Console_setCursorAttribute(FG_INTENSITY_RED);
        printf("===%d=== ERROR! Massive is full, capacity updated.\n", k);
        printf("            Jump or move to undeclared element:\n");
        printf("            in realloc/Queue_realloc/Queue_add/main\n");
        printf("            at Queue_realloc: problems with memory\n");
        printf("            at Queue_add: reallocation\n");
        printf("            at main!\n");
        Console_reset();
        Queue_realloc(self, newCap);
    }
}
//
int Queue_dequeue(Queue * self)
{
    int value = self -> items[self -> first];
    self -> size -= 1;
    if (self -> first == self -> capacity) {
        self->first = 0;
    } else {
        self -> first += 1;
    }
    return value;
}
//
size_t Queue_size(Queue * self)
{
    return self -> size;
}
//
bool Queue_isEmpty(Queue * self)
{
    return Queue_size(self) == 0;
}
//
static void Queue_realloc(Queue * self, int newCapacity)
{
    int cap = self -> capacity;
    int * newItems = realloc(self -> items, sizeof(int) * newCapacity);
    if (newItems == NULL) {
        fprintf(stderr, "Reallocation error");
        abort();
    }
    self -> items = newItems;
    self -> capacity = newCapacity;
    for (int i = self -> first; i < cap + 1; i++) {
        self -> items[newCapacity - cap + i] = self -> items[i];
    }
    self -> first = self -> first + newCapacity - cap;
}

void Queue_print(Queue * self) {
    int l = self -> first;
    Console_setCursorAttribute(FG_INTENSITY_GREEN);
    printf("Size: %zu\nCap: %zu\nFirst: %d\nLast: %d\n", self -> size, self -> capacity, self -> first, self -> last);
    Console_reset();
    while (l != self -> last) {
        Console_setCursorAttribute(FG_INTENSITY_CYAN);
        printf("%d", self -> items[l]);
        Console_reset();
        Console_setCursorAttribute(FG_INTENSITY_RED);
        printf(" <- ");
        Console_reset();
        if (l >= self -> capacity) {
            l = 0;
        } else {
            l++;
        }
    }
    printf("\n");
}