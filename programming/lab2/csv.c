#include "list.h"
#include "csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void   Csv_addInt     (List * row, int value) {
    char * s = malloc(sizeof(char) * 10);
    sprintf(s,"%d", value);
    List_add(row, (void*)s);
}

void   Csv_addString  (List * row, const char * value) {
    List_add(row, (void*)value);
}

int    Csv_int        (List * row, int index) {
    return atoi(List_get(row, index));
}

int    Csv_string     (List * row, int index, char * buf, int nBuf) {
    while (buf != '\0') {
        strcpy(buf, (char*)List_get(row, index));
    }
    int len = strlen(buf);
    return len;
}

void   Csv_addRow     (List * table, List * row) {
    List_add(table, row);
}

List * Csv_row        (List * table, int index) {
    return List_get(table, index);
}

char * String_allocCopy       (const char * src) {
    char * dst = malloc(sizeof(char) * strlen(src) + 1);
    if (dst == NULL) {
        fprintf(stderr, "Error reallocating memory\n");
        exit(EXIT_FAILURE);
    }
    strcpy(dst, src);
    return dst;
}

void   Csv_fillTableFromString  (List * csvTable, const char * csvStr) {
    const char * p = csvStr;
    char buf[500];
    int bufX = 0;
    List * rowTable = List_alloc();
    while (1) {
        if (*p == ',' || *p == '\n' || *p == '\0')
        {
            buf[bufX] = '\0';
            Csv_addString(rowTable, String_allocCopy(buf));
            if (*p == '\n') {
                Csv_addRow(csvTable, rowTable);
                rowTable = List_alloc();
            } else if (*p == '\0') {
                Csv_addRow(csvTable, rowTable);
                // rowTable = List_alloc();
            }
            
            bufX = 0;
        }
        else
        {
            buf[bufX] = *p;
            bufX += 1;
        }
        if (*p == '\0')
        {
                break;
            }
        p += 1;
    }
}

int    Csv_fillStringFromTable  (List * csvTable, char * buf, int nBuf) {
    for (int i = 0; i < List_size(csvTable); i++) {
        for (int j = 0; j < List_size(List_get(csvTable, i)); j++) {
            if (i == 0 && j == 0) {
                buf = List_get(List_get(csvTable, i), j);
                buf += strlen(List_get(List_get(csvTable, i), j));
            } else if (i != 0 && j == 0) {
                buf = List_get(List_get(csvTable, i), j);
                buf += strlen(List_get(List_get(csvTable, i), j));
            } else {
                buf = ",";
                buf += strlen(",");
                buf = List_get(List_get(csvTable, i), j);
                buf += strlen(List_get(List_get(csvTable, i), j));
            }
        }
        buf = "\n";
        buf += strlen("\n");
    }
    puts(buf);
    return strlen(buf);
}

char * Csv_createStringFromTable(List * csvTable) {
    char * buf[300];

    for (int i = 0; i < List_size(csvTable); i++) {
       for (int j = 0; j < List_size(List_get(csvTable, i)); j++) {
            if (i == 0 && j == 0) {
                *buf = List_get(List_get(csvTable, i), j);
                *buf += strlen(List_get(List_get(csvTable, i), j));
            } else if (i != 0 && j == 0) {
                *buf = List_get(List_get(csvTable, i), j);
                *buf += strlen(List_get(List_get(csvTable, i), j));
            } else {
                *buf = ",";
                *buf += strlen(",");
                *buf = List_get(List_get(csvTable, i), j);
                *buf += strlen(List_get(List_get(csvTable, i), j));
            }
       }
       *buf = "\n";
       *buf += strlen("\n");
   }

    return *buf;
}

void   Csv_clearTable           (List * csvTable) {
    for (int i = 0; i < List_size(csvTable); i++) {
        List_clear(List_get(csvTable, i));
        List_free(List_get(csvTable, i));
    }
    csvTable -> size = 0;
}

void Csv_printFile (List * csvTable, FILE * file) {
    for (int i = 0; i < List_size(csvTable); i++) {
        for (int j = 0; j < List_size(List_get(csvTable, i)); j++) {
            if (i == 0 && j == 0) {
                fprintf(file, "%s", List_get(List_get(csvTable, i), j));
            } else if (i != 0 && j == 0) {
                fprintf(file, "%s", List_get(List_get(csvTable, i), j));
            } else {
                fprintf(file, ",");
                fprintf(file, "%s", List_get(List_get(csvTable, i), j));
            }
        }
        if (i != List_size(csvTable) - 1) {
            fprintf(file, "\n");
        }
    }
}

void Csv_print (List * csvTable) {
    for (int i = 0; i < List_size(csvTable); i++) {
        for (int j = 0; j < List_size(List_get(csvTable, i)); j++) {
            if (i == 0 && j == 0) {
                printf("%s", List_get(List_get(csvTable, i), j));
            } else if (i != 0 && j == 0) {
                printf("%s", List_get(List_get(csvTable, i), j));
            } else {
                printf(",");
                printf("%s", List_get(List_get(csvTable, i), j));
            }
        }
        printf("\n");
    }
}

void   Csv_ListOfListsToTable    (List * inFile, List * table) {
    for (int i = 1; i < List_size(inFile); i++) {
        Language * lan = malloc(sizeof(Language));
        lan -> year = Csv_int(List_get(inFile, i), 0);
        lan -> name = List_get(List_get(inFile, i), 1);
        lan -> type = List_get(List_get(inFile, i), 2);
        lan -> author = List_get(List_get(inFile, i), 3);
        List_add(table, lan);
    }
}