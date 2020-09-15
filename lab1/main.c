#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "list.h"
#include "stack.h"

void clearBuf(int len, char str[len]);

int main() {

    FILE * fin = fopen("data.txt", "r");

    List * list;
    list = List_alloc();

    char buf[100];
    int buf_i = 0;

    char ch = fgetc(fin);

    while (1) {
        if (ch == ' ' || ch == EOF) {
            buf[buf_i] = '\0';
            buf_i = 0;
            float curr_num = atof(buf);
            if (buf[0] != '\0') {
                List_add(list, curr_num);
            }
        } else {
            buf[buf_i++] = ch;
        }
        if (ch == EOF) {
            break;
        }
        ch = fgetc(fin);
    }

    if (fin != NULL) {
        fclose(fin);
    }
    
    printf("\nFirst list:\n");
    List_print(list);
    List_ten(list);
    printf("\nAll over ten by module numbers at HEAD:\n");
    List_print(list);

    Stack * stack_1 = Stack_alloc();
    Stack * stack_2 = Stack_alloc();

    int pos = 0;
    for (int i = 0; i < List_size(list); i++) {
        if (pos % 2 == 0) {
            Stack_push(stack_1, List_get(list, i));
        } else {
            Stack_push(stack_2, List_get(list, i));
        }
        pos++;
    }

    printf("\nStack of pare positions:\n");
    Stack_print(stack_2);
    printf("\nStack of non pare positions:\n");
    Stack_print(stack_1);
    List_clear(list);

    int stack_s1 = Stack_size(stack_1);
    int stack_s2 = Stack_size(stack_2);

    for (int i = 0; i < stack_s1; i++) {
        List_add(list, Stack_pop(stack_1));
    }
    for (int i = 0; i < stack_s2; i++) {
        List_add(list, Stack_pop(stack_2));
    }

    printf("\nMerged stacks:\n");
    List_print(list);

    Stack_free(stack_1);
    Stack_free(stack_2);
    List_free(list);

    return 0;
}

void clearBuf(int len, char str[len]) {
    for (int i = 0; i < len; i++) {
        str[i] = '\0';
    }
}