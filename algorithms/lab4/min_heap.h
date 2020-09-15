#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <progbase.h>
#include <progbase/console.h>

struct MinHeap {
    int * tree;

    size_t size;
    size_t capacity;
};

typedef struct MinHeap MinHeap;


MinHeap * MinHeap_alloc();
void MinHeap_dealloc(MinHeap * self);
static void MinHeap_realloc(MinHeap * self, int newCapacity);

int MinHeap_findMin(MinHeap * self);
int MinHeap_extractMin(MinHeap * self);
int MinHeap_delete(MinHeap * self, int key);
bool MinHeap_heapify(MinHeap * self);
void MinHeap_insert(MinHeap * self, int key);

void MinHeap_print(MinHeap * self);
size_t MinHeap_size(MinHeap * self);