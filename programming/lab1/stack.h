#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct __Stack Stack;

struct __Stack {
    int cap;
    int length; 
    float * arr;
};

/* paste _init(), _deinit(), _alloc(), _free() prototypes here */

size_t Stack_size (Stack * self);

void Stack_init(Stack * self);
void Stack_deinit(Stack * self);
Stack * Stack_alloc(void);
void Stack_free(Stack * self);
void Stack_push (Stack * self, float value);  // add value
float Stack_peek (Stack * self);           // get top value
float Stack_pop (Stack * self);           // remove top value
void Stack_print(Stack * self);
bool Stack_isEmpty (Stack * self);