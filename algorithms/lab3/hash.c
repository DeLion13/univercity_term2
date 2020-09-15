#include "hash.h"

#include <string.h>
#include <stdbool.h>
#include <time.h>

#define HASHTABLE_CAPACITY 7

int hashCode(Key * k, Hashtable * h) {
    int hash = 7;

    hash = hash + hashInt(k -> resNum, h -> capacity);
    hash = hash + hashChar(k -> lastName, h -> capacity);

    printf("Key: %d, hash -> %d\n", k -> resNum, hash);
    return hash % h -> capacity;
}

static int hashCode_copy(Key * k, Hashtable * h) {
    int hash = 7;

    hash = hash + hashInt(k -> resNum, h -> capacity);
    hash = hash + hashChar(k -> lastName, h -> capacity);

    return hash % h -> capacity;
}
 
int hashInt(int n, int cap) {
    return (n - 232900) % cap;
}

int hashChar(char * c, int cap) {
    int hash = 0;
    int k = 5;
    for (int i = 0; i < strlen(c); i++) {
        hash = (c[i] - 'a' + 1) * k;
        k = k * k;
    }

    return hash % (cap - 1);
}

Hashtable * initHashTable() {
    Hashtable * h = malloc(sizeof(Hashtable));
    h -> capacity = HASHTABLE_CAPACITY;
    h -> size = 0;
    h -> table = malloc(sizeof(KeyValue) * h -> capacity);
    h -> loadness = 0;
    for (int i = 0; i < HASHTABLE_CAPACITY; i++) {
        h -> table[i] = NULL;
    }

    return h;
}

void insert(Hashtable * h, Key * k, Value * v) {
    if (contains(h, k) == 0) {
        KeyValue * kv = createBlock(k, v);
        int hash = hashCode(k, h);
        if (h -> table[hash] == NULL) {
            h -> table[hash] = kv;
        } else {
            int i = 1;
            while (h -> table[hash + i] != NULL) {
                i = i + 1;
                if (hash + i == h -> capacity) {
                    hash = 0;
                    i = 0;
                }
            }
            hash = hash + i;
            h -> table[hash] = kv;
        }
        h -> size += 1;
        h -> loadness = (float)h -> size / (float)h -> capacity;
        if (h -> loadness >= 0.5) {
            void * newArr = realloc(h -> table, sizeof(KeyValue) * h -> capacity * 2);
            h -> table = newArr;
            h -> capacity = h -> capacity * 2;
            h -> loadness = (float)h -> size / (float)h -> capacity;
            printf("\n.---------.\n|Rehashing|\n'---------'\n");
        }
    } else {
        int num = hashCode(k, h);
        while (1) {
            if (h -> table[num] != NULL && k == h -> table[num] -> k) {
                break;
            }
            num++;
            if (num == h -> capacity) {
                num = 0;
            }
        }
        h -> table[num] -> v = v;
    }
}

int removeEl(Hashtable * h, Key * k) {
    if (contains(h, k) == 0) {
        printf("Not contains!\n");
        abort();
    }
    int num = 0;
    while (1) {
        if (h -> table[num] != NULL && k == h -> table[num] -> k) {
            break;
        }
        num++;
        if (num == h -> capacity) {
            num = 0;
        }
    }

    deleteBlock(h -> table[num]);
    return h -> table[num] -> s;
}

Value * find(Hashtable * h, Key * k) {
    if (contains(h, k) == 0) {
        printf("Not contains!\n");
        return NULL;
    }
    int num = hashCode_copy(k, h);
    while (1) {
        if (h -> table[num] != NULL && k == h -> table[num] -> k) {
            break;
        }
        num++;
        if (num == h -> capacity) {
            num = 0;
        }
    }

    return h -> table[num] -> v;
}

int contains(Hashtable * h, Key * k) {
    bool Yes = false;
    for (int i = 0; i < h -> capacity; i++) {
        if (h -> table[i] != NULL) {
            if (h -> table[i] -> k == k) {
                Yes = true;
                break;
            }
        }
    }

    return Yes;
}

int isEmpty(Hashtable * h) {
    if (h -> size != 0) {
        return 0;
    }
    return 1;
}

size_t size(Hashtable * h) {
    return h -> size;
}

float loadness(Hashtable * h) {
    return h -> loadness;
}

void clear(Hashtable * h) {
    for (int i = 0; i < h -> capacity; i++) {
        free(h -> table[i]);
    }
    h -> size = 0;
}

KeyValue * createBlock(Key * k, Value * v) {
    KeyValue * kv = malloc(sizeof(KeyValue));
    kv -> k = k;
    kv -> v = v;
    kv -> s = NOT_EMPTY;

    return kv;
}

void deleteBlock(KeyValue * kv) {
    kv -> k = NULL;
    kv -> v = NULL;
    kv -> s = DELETED;
}

void print(Hashtable * h) {
    for (int i = 0; i < h -> capacity; i++) {
        if (h -> table[i] != NULL) {
            if (h -> table[i] -> s == DELETED) {
                printf("\nNUM: %d\n\tRESERVATION DELETED!\n", i);
            } else {
                printf("\nNUM: %d\n\tLAST NAME: ", i);
                for (int j = 0; j < strlen(h -> table[i] -> k -> lastName); j++) {
                    printf("%c", h -> table[i] -> k -> lastName[j]);
                }
                printf("\tRESERVATION NUMBER: %d\n\t", h -> table[i] -> k -> resNum);
                printf("INFORMATION:\n\t\t");
                printf("PassportID: %d\t", h -> table[i] -> v -> passportID);
                printf("Flight code: ");
                for (int j = 0; j < strlen(h -> table[i] -> v -> flightCode); j++) {
                    printf("%c", h -> table[i] -> v -> flightCode[j]);
                }
                printf("\n\t\tSeat: %d\tPriority: %d\n", h -> table[i] -> v -> seat, h -> table[i] -> v -> priorityBoarding);
            }
        }
    }
}

Key * Key_init() {
    Key * k = malloc(sizeof(Key));
    k -> lastName = malloc(sizeof(char) * 100);
    k -> resNum = 0;
    return k;
}

Value * Value_init() {
    Value * v = malloc(sizeof(Key));
    v -> flightCode = malloc(sizeof(char) * 100);
    v -> passportID = 0;
    v -> priorityBoarding = 0;
    v -> seat = 0;
    return v;
}

static void insert2(Hashtable2 * h, char * k, char * v) {
    KeyValue2 * kv = malloc(sizeof(KeyValue2));
    kv -> v = malloc(sizeof(char) * 100);
    kv -> k = malloc(sizeof(char) * 100);
    kv -> v = v;
    kv -> k = k;

    int hash = hashChar(k, h -> capacity);
    
    if (h -> table[hash] == NULL) {
        h -> table[hash] = kv;
    } else {
        int i = 1;
        while (h -> table[hash + i] != NULL) {
            i = i + 1;
            if (hash + i == h -> capacity) {
                hash = 0;
                i = 0;
            }
        }
        hash = hash + i;
        h -> table[hash] = kv;
    }
    h -> size += 1;
    h -> loadness = (float)h -> size / (float)h -> capacity;
    if (h -> loadness >= 0.5) {
        void * newArr = realloc(h -> table, sizeof(KeyValue) * h -> capacity * 2);
        h -> table = newArr;
        h -> capacity = h -> capacity * 2;
        h -> loadness = (float)h -> size / (float)h -> capacity;
    }
}

void sameFlightPassengers(Hashtable * h, char * flightCode) {
    Hashtable2 * h2 = malloc(sizeof(Hashtable2));
    h2 -> capacity = HASHTABLE_CAPACITY;
    h2 -> size = 0;
    h2 -> table = malloc(sizeof(KeyValue2) * h2 -> capacity);
    h2 -> loadness = 0;
    for (int i = 0; i < HASHTABLE_CAPACITY; i++) {
        h2 -> table[i] = NULL;
    }

    for (int i = 0; i < h -> capacity; i++) {
        if (h -> table[i] != NULL) {
            if (h -> table[i] -> s != DELETED && strcmp(h -> table[i] -> v -> flightCode, flightCode) == 0) {
                insert2(h2, flightCode, h -> table[i] -> k -> lastName);
            }
        }
    }

    for (int i = 0; i < h2 -> capacity; i++) {
        if (h2 -> table[i] != NULL) {
            printf("\nRace: ");
            for (int j = 0; j < strlen(h2 -> table[i] -> k); j++) {
                printf("%c", h2 -> table[i] -> k[j]);
            }
            printf("\tLast name: ");
            for (int j = 0; j < strlen(h2 -> table[i] -> v); j++) {
                printf("%c", h2 -> table[i] -> v[j]);
            }
        }
    }

    printf("\n");
}

Key * preparingKey(char * lastName) {
    Key * k = Key_init();
    k -> lastName = lastName;
    k -> resNum = 232900 + rand() % (200 - 1 + 1) + 1;

    return k;
}

Value * preparingValue(int seat, char * flightCode, int passportID, int priorityBoarding) {
    Value * v = Value_init();
    v -> seat = seat;
    v -> flightCode = flightCode;
    v -> passportID = passportID;
    v -> priorityBoarding = priorityBoarding;

    return v;
}