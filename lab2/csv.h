#pragma once

#include "list.h" // generic list (array implementation)

typedef struct __Language Language;

struct __Language {
    int    year;
    char *  name;
    char *  type;
    char *  author;
};

void   Csv_addInt     (List * row, int value);  // malloc a string and write value in it
void   Csv_addString  (List * row, const char * value); // malloc a string and copy value

int    Csv_int        (List * row, int index);  // get item (str) and convert it to int
int    Csv_string     (List * row, int index, char * buf, int nBuf);  // get str & copy it to buf

void   Csv_addRow     (List * table, List * row);  // add row to table as an item
List * Csv_row        (List * table, int index);   // get item from table as List *

void   Csv_fillTableFromString  (List * csvTable, const char * csvStr);  // parse csv & fill table
int    Csv_fillStringFromTable  (List * csvTable, char * buf, int nBuf); // fill buf with csv
char * Csv_createStringFromTable(List * csvTable);  // malloc string array and fill it with csv
void   Csv_clearTable           (List * csvTable);  // free all table allocated memory
void   Csv_printFile            (List * csvTable, FILE * file);
void   Csv_print                (List * csvTable);
char * String_allocCopy         (const char * src);

void   Csv_ListOfListsToTable    (List * inFile, List * table);