#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <progbase.h>
#include <progbase/console.h>

#include "hash.h"

void test();

void printKeyValue(Key * k, Value * v) {
    printf("\nLAST NAME: ");
    for (int j = 0; j < strlen(k -> lastName); j++) {
        printf("%c",k -> lastName[j]);
    }
    printf("\tRESERVATION NUMBER: %d\n\t", k -> resNum);
    printf("INFORMATION:\n\t\t");
    printf("PassportID: %d\t", v -> passportID);
    printf("Flight code: ");
    for (int j = 0; j < strlen(v -> flightCode); j++) {
        printf("%c", v -> flightCode[j]);
    }
    printf("\n\t\tSeat: %d\tPriority: %d\n", v -> seat, v -> priorityBoarding);
}

int main() {
<<<<<<< HEAD
=======
    Console_setCursorAttribute(BG_RED);
    printf("------TEST------\n");
    Console_reset();
>>>>>>> 045a9f8798afae6aa6e6581f1c1c99aee6df620f
    test();
    srand(time(NULL));
    Hashtable * h = initHashTable();
    Console_setCursorAttribute(BG_BLUE);
    printf("------WORK 1------");
    Console_reset();
    Console_setCursorAttribute(FG_RED);
    printf("\n\nInputing of 5 elements. Starting capacity = 7\n");
    Console_reset();

    Key * k2 = preparingKey("Shapovalov");
    Value * v2 = preparingValue(93, "NC-31", 459632, 0);

    Key * k3 = preparingKey("Lahman");
    Value * v3 = preparingValue(45, "NC-53", 341094, 1);

    Key * k4 = preparingKey("Romanenko");
    Value * v4 = preparingValue(62, "NC-11", 459632, 1);

    Key * k5 = preparingKey("Voronin");
    Value * v5 = preparingValue(23, "NC-11", 123049, 0);

    Key * k = preparingKey("Bodichelly");
    Value * v = preparingValue(10, "NC-31", 450213, 1);

    insert(h, k2, v2);
    insert(h, k3, v3);
    insert(h, k4, v4);
    insert(h, k5, v5);
    insert(h, k, v);


    Console_setCursorAttribute(BG_BLUE);
    printf("\n------WORK 2------\n");
    Console_reset();
    Console_setCursorAttribute(FG_RED);
    printf("\nFinding of elements 1 and 5\n");
    Console_reset();

    Value * vt_1 = Value_init();
    vt_1 = find(h, k);
    printKeyValue(k, vt_1);
    Value * vt_5 = Value_init();
    vt_5 = find(h, k5);
    printKeyValue(k5, vt_5);

    Console_setCursorAttribute(BG_BLUE);
    printf("\n------WORK 3------\n");
    Console_reset();
    Console_setCursorAttribute(FG_RED);
    printf("\nDeleting of element \"Shapovalov\" and \"Lahman\" elements\n");
    Console_reset();

    removeEl(h, k2);
    removeEl(h, k3);
    print(h);

    Console_setCursorAttribute(BG_BLUE);
    printf("\n------WORK 4------\n");
    Console_reset();
    Console_setCursorAttribute(FG_RED);
    printf("\nAll races 'NC-11'\n");
    Console_reset();

    sameFlightPassengers(h, "NC-11");

    return 0;
}

void test() {
    srand(time(NULL));
    Hashtable * h = initHashTable();
    Key * k2 = preparingKey("Shapovalov");
    Value * v2 = preparingValue(93, "NC-31", 459632, 0);
    insert(h, k2, v2);

    Key * k3 = preparingKey("Bod");
    Value * v3 = preparingValue(93, "NC-21", 45632, 1);
    insert(h, k3, v3);

    assert(contains(h, k2) == 1);
    assert(contains(h, k3) == 1);

    assert(find(h, k2) == v2);
    assert(find(h, k3) == v3);
    
    removeEl(h, k2);
    assert(contains(h, k2) == 0);

    removeEl(h, k3);
    assert(contains(h, k3) == 0);
}