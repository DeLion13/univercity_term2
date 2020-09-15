#pragma once

#include <stdlib.h> 
#include <stdbool.h>

typedef struct KeyValue KeyValue;
struct KeyValue
{
    const char * key;
    const char * value;
};

int KeyValue_compare(KeyValue * a, KeyValue * b);

typedef struct __SortedKeyValueList SortedKeyValueList;
struct __SortedKeyValueList {
   KeyValue  * items;
   size_t capacity;
   size_t size;
};

void SortedKeyValueList_init(SortedKeyValueList * self);
void SortedKeyValueList_deinit(SortedKeyValueList * self);

size_t  SortedKeyValueList_size     (SortedKeyValueList * self);
KeyValue     SortedKeyValueList_get      (SortedKeyValueList * self, int index);
void    SortedKeyValueList_set      (SortedKeyValueList * self, int index, KeyValue value);
void    SortedKeyValueList_removeAt (SortedKeyValueList * self, int index);

void    SortedKeyValueList_add      (SortedKeyValueList * self, KeyValue value);  // add value and sort, tip: use insertion sort
void    SortedKeyValueList_remove   (SortedKeyValueList * self, KeyValue value);  // < O(n), tip: find index and _removeAt()
int     SortedKeyValueList_indexOf  (SortedKeyValueList * self, KeyValue value);  // < O(n), tip: use non-linear search method
bool    SortedKeyValueList_contains (SortedKeyValueList * self, KeyValue value);  // < O(n), tip: find index and check it for -1

void    SortedKeyValueList_clear    (SortedKeyValueList * self);
void    SortedKeyValueList_realloc  (SortedKeyValueList * self, int newCapacity);