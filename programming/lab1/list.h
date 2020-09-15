#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct __List List;

struct __List {
    float * items;
    size_t capacity;
    size_t size;
};

void    List_init     (List * self);
void    List_deinit   (List * self);
List *  List_alloc    (void);
void    List_free     (List * self);
static void List_realloc(List *self, int newCapacity);

size_t  List_size     (List * self);
float   List_get      (List * self, int index);
void    List_set      (List * self, int index, float value);
void    List_insert   (List * self, int index, float value);
void    List_removeAt (List * self, int index);

void    List_add      (List * self, float value);
void    List_remove   (List * self, float value);
int     List_indexOf  (List * self, float value);
bool    List_contains (List * self, float value);
bool    List_isEmpty  (List * self);
void    List_clear    (List * self);
void    List_print    (List * self);
void    List_ten      (List * self);
void    List_error(List * self);