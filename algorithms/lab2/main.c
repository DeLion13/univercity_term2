#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "queue.h"

void test();

int main() {
    test();
    Queue * q = Queue_alloc();
    Console_clear();
    int k = 0;
    Console_setCursorAttribute(FG_INTENSITY_MAGENTA);
    printf("Input your number: ");
    Console_reset();
    scanf("%d", &k);
    Console_clear();

    while (1) {
        Queue_enqueue(q, k);
        if (k == 0) {
            for (int i = 0; i < 3; i++) {
                if (Queue_size(q) == 0) {
                    break;
                }
                Queue_dequeue(q);
            }
        }
        if (Queue_size(q) == 0) {
            Console_setCursorAttribute(FG_BLUE);
            printf("Queue is empty!\n");
            Console_reset();
            break;
        }
        Queue_print(q);
        Console_setCursorAttribute(FG_INTENSITY_MAGENTA);
        printf("Input your number: ");
        Console_reset();
        scanf("%d", &k);
        Console_clear();
    }
    

    Queue_free(q);
    return 0;
}

void test() {
    Queue q1;
    Queue_init(&q1);

    assert(Queue_size(&q1) == 0);

    Queue_enqueue(&q1, 13);
    assert(Queue_size(&q1) == 1);

    Queue_enqueue(&q1, -42);
    assert(Queue_size(&q1) == 2);
    assert(Queue_dequeue(&q1) == 13);
    assert(Queue_size(&q1) == 1);
    assert(Queue_dequeue(&q1) == -42);

    for (int i = 0; i < 10; i++) {
        Queue_enqueue(&q1, i);
    }

    Queue_deinit(&q1);
}