#include "list.h"

#include <stdio.h>
#include <math.h>

void    List_init     (List * self) {
    self->capacity = 4;
    self->size = 0;
    self->items = malloc(sizeof(float) * self->capacity);
    if (self->items == NULL) {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
}

void    List_deinit   (List * self) {
    free(self->items);
}

List *  List_alloc    (void) {
    List * self = malloc(sizeof(List));
    List_init(self);
    return self;
}

void List_free (List * self) {
    List_deinit(self);
    free(self);
}

float List_get (List * self, int index) {
    if (index < 0 || index >= self -> size) {
        List_error(self);
        return -1;
    }
    return self->items[index]; 
}

void List_set (List * self, int index, float value) {
    if (index < 0 || index >= self -> size) {
        List_error(self);
        return;
    }
    self -> items[index] = value;
}

size_t List_size (List * self) {
    return self->size;
}

void List_insert (List * self, int index, float value) {
    if (index < 0 || index >= self -> size) {
        List_error(self);
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

static void List_realloc(List * self, int newCapacity) {
    float * newArray = realloc(self -> items, sizeof(float) * newCapacity);
    if (newArray == NULL) {
        fprintf(stderr, "Reallocating memory error\n");
        abort();
    }
    self->items = newArray;
    self->capacity = newCapacity;
}

void List_removeAt (List * self, int index) {
    if (index < 0 || index >= self -> size) {
        List_error(self);
        return;
    }
    for (int i = index; i < self -> size - 1; i++) {
        self -> items[i] = self -> items[i + 1];
    }
    self -> size -= 1;
}

void List_add (List * self, float value) {
    if (self -> size == self -> capacity) {
        List_realloc(self, self->capacity * 2);
    }
    self->items[self->size] = value;
    self->size += 1;
}

void List_remove (List * self, float value) {
    List_removeAt(self, List_indexOf(self, value));
}

int List_indexOf (List * self, float value) {
    for (int i = 0; i < self -> size; i++) {
        if (self -> items[i] == value) {
            return i;
        }
    }
    printf("Not found your element!");
    return -1;
}

bool List_contains (List * self, float value) {
    bool c = false;
    for (int i = 0; i < self -> size; i++) {
        if (self -> items[i] == value) {
            c = true;
        }
    }
    return c;
}

bool List_isEmpty (List * self) {
    bool emp = false;
    if (self -> items == NULL) {
        emp = true;
    }
    return emp;
}

void List_clear (List * self) {
    self -> size = 0;
}

void List_print (List * self) {
    for(int i = 0; i < self -> size; i++) {
        if (i < self -> size - 1) {
            printf("%.3f -> ", self -> items[i]);
        } else {
            printf("%.3f", self -> items[i]);
        }
        
    }
    printf("\n");
}

void List_ten (List * self) {
    int r = 0;
    for (int i = 0; i < self -> size; i++) {
        if (fabs(self -> items[i]) > 10) {
            List_insert(self, r, self -> items[i]);
            List_removeAt(self, i + 1);
            r++;
        }
    }
}

void List_error(List * self) {
    fprintf(stderr, "Segmentation fault!");
}