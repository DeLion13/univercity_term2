#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <progbase.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

struct __Queue {
    int * items;
    int first;
    int last;
    size_t size;
    size_t capacity;
};
typedef struct __Queue Queue;

void Queue_init(Queue * self);
void Queue_deinit(Queue * self);
Queue *  Queue_alloc    (void) ;
static void Queue_realloc(Queue * self, int newCapacity);
void Queue_print(Queue * self);
void Queue_free(Queue * self);

void Queue_enqueue(Queue * self, int value);
int  Queue_dequeue(Queue * self);
size_t  Queue_size(Queue * self);