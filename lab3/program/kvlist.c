#include "kvlist.h"
#include <string.h>
#include <stdio.h>

void SortedKeyValueList_init(SortedKeyValueList * self) {
    self->capacity = 16;
    self->items = malloc(sizeof(KeyValue) * self->capacity);
    self->size = 0;
}

void SortedKeyValueList_deinit(SortedKeyValueList * self) {
    free(self->items);
}

size_t  SortedKeyValueList_size     (SortedKeyValueList * self) {
    return self->size;
}

KeyValue     SortedKeyValueList_get      (SortedKeyValueList * self, int index) {
    return self->items[index];
}

void    SortedKeyValueList_set      (SortedKeyValueList * self, int index, KeyValue value) {
    KeyValue curr = self->items[index];
    if (KeyValue_compare(&curr, &value) == 0) {
        self->items[index] = value;
    }
    else {
        abort();
    }
    
}
void    SortedKeyValueList_removeAt (SortedKeyValueList * self, int index) {
    // @todo check index
    for (int i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1];
    }
    self->size -= 1;
}

int KeyValue_compare(KeyValue * a, KeyValue * b) {
    return strcmp(a->key, b->key); 
}

void    SortedKeyValueList_add      (SortedKeyValueList * self, KeyValue kv) {

    if (self -> size == self -> capacity) {
        SortedKeyValueList_realloc(self, self->capacity * 2);
    }
    for (int i = self->size; i >= 0; i--) {
        if (i == 0) {
            self->items[i] = kv;
        }
        else {
            int cmp = KeyValue_compare(&kv, &self->items[i - 1]);
            if (cmp >= 0) {
                self->items[i] = kv;
                break;
            }
            else {
                self->items[i] = self->items[i - 1];
            }
        }
    } 
    self->size += 1;
    if (self -> size == self -> capacity) {
        SortedKeyValueList_realloc(self, self->capacity * 2);
    }
}

void    SortedKeyValueList_remove   (SortedKeyValueList * self, KeyValue kv) {
    int index = SortedKeyValueList_indexOf(self, kv);
    if (index == -1) return;
    for (int i = index; i < self->size - 1; i++)
    {
        self->items[i] = self->items[i + 1];
    }
    self->size -= 1;
}

int     SortedKeyValueList_indexOf  (SortedKeyValueList * self, KeyValue kv) {
    KeyValue * item = bsearch(
        &kv,
        self->items, 
        self->size,
        sizeof(KeyValue), 
        (__compar_fn_t)KeyValue_compare);
    if (item == NULL) return -1;
    return item - self->items;
}

bool    SortedKeyValueList_contains (SortedKeyValueList * self, KeyValue kv) {
    return SortedKeyValueList_indexOf(self, kv) != -1;
}

void    SortedKeyValueList_clear    (SortedKeyValueList * self) {
    self->size = 0; 
}

void SortedKeyValueList_realloc (SortedKeyValueList * self, int newCapacity) {
    void * newArray = realloc(self -> items, sizeof(void *) * newCapacity);
    if (newArray == NULL) {
        fprintf(stderr, "Reallocating memory error\n");
        abort();
    }
    self->items = newArray;
    self->capacity = newCapacity;
}
