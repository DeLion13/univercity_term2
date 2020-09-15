#pragma once;

#include <stdio.h>
#include <stdlib.h>

typedef struct Value Value;
typedef struct Key Key;
typedef struct KeyValue KeyValue;
typedef struct KeyValue2 KeyValue2;
typedef struct Hashtable Hashtable;
typedef struct Hashtable2 Hashtable2;
typedef enum status status;

enum status {
    EMPTY,
    NOT_EMPTY,
    DELETED
};

struct Value {
    int passportID;
    char * flightCode;
    int seat;
    int priorityBoarding;
};


struct Key {
    int resNum;
    char * lastName;
};

struct KeyValue {
    Value * v;
    Key * k;
    status s;
};

struct Hashtable {
    KeyValue ** table;
    float loadness;
    size_t size;
    int capacity;
};

struct KeyValue2 {
    char * v;
    char * k;
};

struct Hashtable2 {
    KeyValue2 ** table;
    float loadness;
    size_t size;
    int capacity;
};

int hashCode(Key * k, Hashtable * h);
int hashInt(int n, int cap);
int hashChar(char * c, int cap);

Hashtable * initHashTable();
void insert(Hashtable * h, Key * k, Value * v);
int removeEl(Hashtable * h, Key * k);
Value * find(Hashtable * h, Key * k);

int contains(Hashtable * h, Key * k);
int isEmpty(Hashtable * h);
size_t size(Hashtable * h);
float loadness(Hashtable * h);
void clear(Hashtable * h);

KeyValue * createBlock(Key * k, Value * v);
void deleteBlock(KeyValue * kv);

void print(Hashtable * h);

Key * Key_init();
Value * Value_init();

void sameFlightPassengers(Hashtable * h, char * flightCode);
Key * preparingKey(char * lastName);
Value * preparingValue(int seat, char * flightCode, int passportID, int priorityBoarding);