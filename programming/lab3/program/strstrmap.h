#pragma once
#include <stdlib.h> 
#include <stdbool.h> 

#include "kvlist.h"

typedef struct __StrStrMap StrStrMap;
struct __StrStrMap
{
    SortedKeyValueList list;
};

void StrStrMap_init(StrStrMap * self);
void StrStrMap_deinit(StrStrMap * self);
StrStrMap * StrStrMap_alloc(void);
void StrStrMap_free(StrStrMap * self);

size_t StrStrMap_size         (StrStrMap * self);

void   StrStrMap_add          (StrStrMap * self, const char * key, const char * value);
bool   StrStrMap_contains     (StrStrMap * self, const char * key);
const char * StrStrMap_get    (StrStrMap * self, const char * key);
const char * StrStrMap_set    (StrStrMap * self, const char * key, const char * value);
const char * StrStrMap_remove (StrStrMap * self, const char * key);
void   StrStrMap_clear        (StrStrMap * self);

void   StrStrMap_keys         (StrStrMap * self, KeyValue * keys);
void   StrStrMap_values       (StrStrMap * self, KeyValue * values);

char * String_allocCopy       (const char * value);
char * String_allocFromInt    (int value);