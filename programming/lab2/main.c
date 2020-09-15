#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>  
#include <getopt.h>

#include "csv.h"
#include "list.h"

int main(int argc, char *argv[]) {
    FILE * fout;
    List table;
    List_init(&table);

    List inFile;
    List_init(&inFile);

    Language testList[] = {
        {19,"PHP","J ","f"},
        {83,"Python","Object-oriented","gsdf"},
        {10,"Java","Object-oriented","sada"},
        {0,"Ruby on Rails","Dynamic","Yukihiro Matsumoto"},
        {2,"Perl","Multi-paradigm","Larry Wall"}
    };

    char buf[500];
    bool wasIn = false;
    bool wasN = false;
    bool wasO = false;
    int year = 0;
    char out_name[20];

    for(int k = 0; k < argc; k++) {
        if (strcmp("data.csv", argv[k]) == 0) {
            FILE * fin = fopen(argv[k], "r+");
            int buf_i = 0;

            char ch = fgetc(fin);

            while (1) {
                if (ch == EOF) {
                    break;
                }
                buf[buf_i] = ch;
                ch = fgetc(fin);
                buf_i++;
            }
            
            buf[buf_i] = '\0';

            if (fin != NULL) {
                fclose(fin);
            }
            wasIn = true;
        } else {
            if (strcmp("-n", argv[k]) == 0) {
                wasN = true;
                if (k != argc - 1) {
                    k++;
                } else {
                    printf("No num!\n");
                    List_deinit(&table);
                    List_deinit(&inFile);
                    return -1;
                }
                for (int i = 0; i < strlen(argv[k]); i++) {
                    if(!isdigit(argv[k][i])) {
                        printf("Not int with -n!\n");
                        List_deinit(&table);
                        List_deinit(&inFile);
                        return -1;
                    }
                }
                year = atoi(argv[k]);
            } else if (strcmp("-o", argv[k]) == 0) {
                wasO = true;
                if (k != argc - 1) {
                    k++;
                } else {
                    printf("No name!\n");
                    List_deinit(&table);
                    List_deinit(&inFile);
                    return -1;
                }
                for (int i = 0; i < strlen(argv[k]); i++) {
                    if(!isalnum(argv[k][i]) && argv[k][i] != '.') {
                        printf("Not name -o!\n");
                        List_deinit(&table);
                        List_deinit(&inFile);
                        return -1;
                    }
                }
                strcpy(out_name, argv[k]);
                fout = fopen(out_name, "w");
            }
        } 
    }

    

    if (wasIn) {
        Csv_fillTableFromString(&inFile, buf);
        Csv_ListOfListsToTable(&inFile, &table);
    } else {
        for (int i = 0; i < 5; i++) {
            List_add(&table, &testList[i]);
        }
    }

    List cat;
    List_init(&cat);

    if (wasN) {
        for (int i = 0; i < List_size(&table); i++) {
            Language * ok = List_get(&table, i);
            if (ok -> year <= year) {
                List * pRow = List_alloc();
                Csv_addInt(pRow, ok -> year);
                Csv_addString(pRow, ok -> name);
                Csv_addString(pRow, ok -> type);
                Csv_addString(pRow, ok -> author);

                Csv_addRow(&cat, pRow);
            }
        }
    } else {
        for (int i = 0; i < List_size(&table); i++) {
            Language * ok = List_get(&table, i);

            List * pRow = List_alloc();
            Csv_addInt(pRow, ok -> year);
            Csv_addString(pRow, ok -> name);
            Csv_addString(pRow, ok -> type);
            Csv_addString(pRow, ok -> author);

            Csv_addRow(&cat, pRow);
        }
    }

    if (wasO) {
        Csv_printFile(&cat, fout);
        fclose(fout);
    } else {
        Csv_print(&cat);
    }

    if (wasIn) {
        Csv_clearTable(&inFile);
        for (int i = 0; i < List_size(&inFile); i++) {
            char * value = List_get(List_get(&inFile, i), 0);
            free(value);
        }
        List_clear(&inFile);
        List_deinit(&inFile);
        for (int i = 0; i < List_size(&cat); i++) {
            char * value = List_get(List_get(&cat, i), 0);
            free(value);
        }
        for (int i = 0; i < List_size(&cat); i++) {
            List_deinit(List_get(&cat, i));
        }
        List_clear(&cat);
        List_deinit(&cat);
        List_clear(&table);
        List_deinit(&table);
    } else {
        for (int i = 0; i < List_size(&cat); i++) {
            List_freeNode(List_get(List_get(&cat, i), 0));
            List_deinit(List_get(&cat, i));
        }
        List_clear(&cat);
        List_deinit(&cat);
        for (int i = 0; i < List_size(&inFile); i++) {
            List_deinit(List_get(&inFile, i));
        }
        List_clear(&inFile);
        List_deinit(&inFile);
        List_deinit(&table);
    }


    return 0;
}