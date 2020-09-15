#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

List * List_alloc()
{
    List * self = malloc(sizeof(List));
    List_init(self);
    return self;
}

void List_freeNode(List * self) {
    free(self);
}

void List_free(List *self)
{
    List_deinit(self);
    free(self);
}

void List_init(List *self)
{
    self->capacity = 16;
    self->size = 0;
    self->items = malloc(sizeof(void *) * self->capacity);
    if (self->items == NULL)
    {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
}
void List_deinit(List *self)
{
    free(self->items);
}

void * List_get(List *self, int index)
{
    return self->items[index]; 
}
void List_set(List *self, int index, void * value)
{
    if (index < 0 || index >= self -> size) {
        return;
    }
    self -> items[index] = value;
}
size_t List_size(List *self)
{
    return self->size;
}
void List_insert(List *self, int index, void *value)
{
    if (index < 0 || index >= self -> size) {
        return;
    }
    if (self -> size == self -> capacity) {
        List_realloc(self, self->capacity * 2);
    }
    for (int i = self -> size - 1; i >= index; i--) {
        self -> items[i + 1] = self -> items[i];
    }
    self -> items[index] = value;
    self -> size += 1;
}
void List_removeAt(List *self, int index)
{
    if (index < 0 || index >= self -> size) {
        return;
    }
    for (int i = index; i < self -> size - 1; i++) {
        self -> items[i] = self -> items[i + 1];
    }
    self -> size -= 1;
}

void List_add(List *self, void *value)
{
    if (self -> size == self -> capacity) {
        List_realloc(self, self->capacity * 2);
    }
    self->items[self->size] = value;
    self->size += 1;
}
void List_remove(List *self, void *value)
{
    List_removeAt(self, List_indexOf(self, value));
}
int List_indexOf(List *self, void *value)
{
    for (int i = 0; i < self -> size; i++) {
        if (self -> items[i] == value) {
            return i;
        }
    }
    printf("Not found your element!");
    return -1;
}
bool List_contains(List *self, void *value)
{
    bool c = false;
    for (int i = 0; i < self -> size; i++) {
        if (self -> items[i] == value) {
            c = true;
        }
    }
    return c;
}
bool List_isEmpty(List *self)
{
    bool emp = false;
    if (self -> items == NULL) {
        emp = true;
    }
    return emp;
}
void List_clear(List *self)
{
    for (int i = 0; i < List_size(self); i++) {
        free(self -> items[i]);
    }
    self -> size = 0;
}

static void List_realloc(List * self, int newCapacity) {
    void * newArray = realloc(self -> items, sizeof(void *) * newCapacity);
    if (newArray == NULL) {
        fprintf(stderr, "Reallocating memory error\n");
        abort();
    }
    self->items = newArray;
    self->capacity = newCapacity;
}
