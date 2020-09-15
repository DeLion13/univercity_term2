#include "csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    bool firstK = false;
    bool lastK = false;
    while (1) {
        if ((*p == ',' || *p == '\n' || *p == '\0') && ((firstK == false && lastK == false) || (firstK == true && lastK == true))) {
            buf[bufX] = '\0';
            Csv_addString(rowTable, String_allocCopy(buf));
            if (*p == '\n') {
                Csv_addRow(csvTable, rowTable);
                rowTable = List_alloc();
            } else if (*p == '\0') {
                Csv_addRow(csvTable, rowTable);
            }
            
            bufX = 0;
            firstK = false;
            lastK = false;
        }
        else {
            if (*p == '\"' && *(p + 1) != '\"') {
                if (firstK == true) {
                    lastK = true;
                } else {
                    firstK = true;
                }
            } else if (*p == '\"' && *(p + 1) == '\"') {
                buf[bufX] = *p;
                bufX += 1;
                p += 1;
            } else if ((*p == ',' || *p == '\n') && firstK == true && lastK == false) {
                buf[bufX] = *p;
                bufX += 1;
            } else {
                buf[bufX] = *p;
                bufX += 1;
            }
        }
        if (*p == '\0') {
            break;
        }
        p += 1;
    }
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
            bool wasSemInString = false;
            const char * str = List_get(List_get(csvTable, i), j);
            while (*str != '\0') {
                if (*str == '\"' || *str == ',' || *str == '\n') {
                    wasSemInString = true;
                }
                str++;
            }
            if (i == 0 && j == 0) {
                if (wasSemInString) {
                    str = List_get(List_get(csvTable, i), j);
                    fprintf(file, "%c", '\"');
                    while (*str != '\0') {
                        if (*str == '\"') {
                            fprintf(file, "%c", *str);
                            fprintf(file, "%c", '\"');
                        } else {
                            fprintf(file, "%c", *str);
                        }
                        str++;
                    }
                    fprintf(file, "%c", '\"');
                } else {
                    fprintf(file, "%s", List_get(List_get(csvTable, i), j));
                }
                
            } else if (i != 0 && j == 0) {
                if (wasSemInString) {
                    str = List_get(List_get(csvTable, i), j);
                    fprintf(file, "%c", '\"');
                    while (*str != '\0') {
                        if (*str == '\"') {
                            fprintf(file, "%c", *str);
                            fprintf(file, "%c", '\"');
                        } else {
                            fprintf(file, "%c", *str);
                        }
                        str++;
                    }
                    fprintf(file, "%c", '\"');
                } else {
                    fprintf(file, "%s", List_get(List_get(csvTable, i), j));
                }
            } else {
                fprintf(file, ",");
                if (wasSemInString) {
                    str = List_get(List_get(csvTable, i), j);
                    fprintf(file, "%c", '\"');
                    while (*str != '\0') {
                        if (*str == '\"') {
                            fprintf(file, "%c", *str);
                            fprintf(file, "%c", '\"');
                        } else {
                            fprintf(file, "%c", *str);
                        }
                        str++;
                    }
                    fprintf(file, "%c", '\"');
                } else {
                    fprintf(file, "%s", List_get(List_get(csvTable, i), j));
                }
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