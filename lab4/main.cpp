#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cassert>

#include "list.hpp"
#include "stack.hpp"

int main() {

    FILE * fin = fopen("data.txt", "r");

    List list;
    Stack stack1;
    Stack stack2;

    char buf[100];
    int buf_i = 0;

    if (fin == nullptr) {
        return -1;
    }

    char ch = fgetc(fin);

    while (1) {
        if (ch == ' ' || ch == EOF) {
            buf[buf_i] = '\0';
            buf_i = 0;
            float curr_num = atof(buf);
            if (buf[0] != '\0') {
                list.add(curr_num);
            }
        } else {
            buf[buf_i++] = ch;
        }
        if (ch == EOF) {
            break;
        }
        ch = fgetc(fin);
    }

    if (fin != nullptr) {
        fclose(fin);
    }
    
    printf("\nFirst list:\n");
    list.print();
    list.ten();
    printf("\nAll over ten by module numbers at HEAD:\n");
    list.print();

    int pos = 0;
    for (int i = 0; i < list.size(); i++) {
        if (pos % 2 == 0) {
            stack1.push(list[i]);
        } else {
            stack2.push(list[i]);
        }
        pos++;
    }

    printf("\nStack of pare positions:\n");
    stack2.print();
    printf("\nStack of non pare positions:\n");
    stack1.print();
    list.clear();

    int stack_s1 = stack1.size();
    int stack_s2 = stack2.size();

    for (int i = 0; i < stack_s1; i++) {
        list.add(stack1.pop());
    }
    for (int i = 0; i < stack_s2; i++) {
        list.add(stack2.pop());
    }

    printf("\nMerged stacks:\n");
    list.print();

    return 0;
}