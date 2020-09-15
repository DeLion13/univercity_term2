#include "stack.h"

#include <stdio.h>

void Stack_init(Stack * self) {
    self->cap = 4;
    self->length = 0;
    self->arr = malloc(sizeof(float) * self->cap);
    if (self->arr == NULL) {
        fprintf(stderr, "Allocating memory error\n");
        abort();
    }
}

void Stack_deinit(Stack * self) {
    free(self->arr);
}

Stack * Stack_alloc(void) {
    Stack * self = malloc(sizeof(Stack));
    Stack_init(self);
    return self;
}

void Stack_free(Stack * self) {
    Stack_deinit(self);
    free(self);
}

void Stack_push(Stack * self, float value) {
    self->arr[self->length] = value;
    self->length += 1;
    // realloc mem
    if (self->length == self->cap) {
        int newcap = self->cap * 2;
        float * newarr = realloc(self->arr, sizeof(float) * newcap);
        if (newarr == NULL) {
            fprintf(stderr, "Reallocating memory error\n");
            abort();
        }
        self -> arr = newarr;
        self -> cap = newcap;
    }
}

float Stack_pop(Stack * self) {
    float oldValue = self->arr[self->length - 1];
    self->length -= 1;
    return oldValue;
}

float Stack_peek(Stack * self) {
    return self->arr[self->length - 1];
}

size_t Stack_size(Stack * self) {
    return self->length;
}

void Stack_print(Stack * self) {
    for (int i = 0; i < Stack_size(self); i++) {
        if (i == 0) {
            printf("%.3f", self -> arr[i]);
        } else {
            printf(" <- %.3f", self -> arr[i]);
        }
    }
    printf("\n");
}

bool Stack_isEmpty (Stack * self) {
    bool emp = false;
    if (self -> arr == NULL) {
        emp = true;
    }
    return emp;
}