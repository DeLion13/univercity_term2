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

#include <csv.h>
#include <list.h>
#include "strstrmap.h"
#include "kvlist.h"
#include "bstree.h"

StrStrMap * createLangMap(int id, const char * name, const char * type, const char * author);
void   Csv_ListOfListsToTable    (List * inFile, List * table);
void   Csv_ListOfListsToBinTree    (List * inFile, BSTree * table);

int main(int argc, char *argv[]) {
    FILE * fout;
    List table;
    List_init(&table);

    List inFile;
    List_init(&inFile);

    StrStrMap * maps[5];

    maps[0] = createLangMap(34, "PHP", "J ", "f");
    maps[1] = createLangMap(831, "Python", "Object-oriented", "gsdf");
    maps[2] = createLangMap(12, "Java", "Object-oriented", "sada");
    maps[3] = createLangMap(1023, "Ruby on Rails", "Dynamic", "Yukihiro Matsumoto");
    maps[4] = createLangMap(2, "Perl", "Multi-paradigm", "Larry Wall");

    char buf[500];
    bool wasIn = false;
    bool wasN = false;
    bool wasO = false;
    bool wasB = false;
 
    int id = 0;
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
                id = atoi(argv[k]);
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
            } else if (strcmp("-b", argv[k]) == 0) {
                wasB = true;
            }
        } 
    }

    if (wasIn) {
        Csv_fillTableFromString(&inFile, buf);
        Csv_ListOfListsToTable(&inFile, &table);
    } else {
        for (int i = 0; i < 5; i++) {
            List_add(&table, (StrStrMap*)maps[i]);
        }
    }

    BSTree binT;
    BSTree_init(&binT);
    if (wasB) {

        if (wasIn) {
            Csv_ListOfListsToBinTree(&inFile, &binT);
        } else {
            for (int i = 0; i < 5; i++) {
                BSTree_insert(&binT, (StrStrMap*)maps[i]);
            }
        }

        printf("\nFirst BinTree:\n");
        printTree(&binT);

        if (wasN == true && wasIn == true) {
            int size = BSTree_size(&binT);
            for (int i = 0; i < size; i++) {
                StrStrMap * ok = List_get(&table, i);
                if (atoi(StrStrMap_get(ok, "id")) > id) {
                    StrStrMap * tmp = BSTree_delete(&binT, getKey(ok));
                    free((char*)StrStrMap_get(tmp, "id"));
                    free((char*)StrStrMap_get(tmp, "name"));
                    free((char*)StrStrMap_get(tmp, "author"));
                    free((char*)StrStrMap_get(tmp, "type"));
                    StrStrMap_free(tmp);
                }
            }
        } else if (wasN == true && wasIn == false) {
            int size = BSTree_size(&binT);
            for (int i = 0; i < size; i++) {
                StrStrMap * ok = List_get(&table, i);
                if (atoi(StrStrMap_get(ok, "id")) > id) {
                    BSTree_delete(&binT, getKey(ok));
                }
            }
        }

        printf("\nNew BinTree:\n");
        printTree(&binT);
    }

    List cat;
    List_init(&cat);

    if (wasN) {
        for (int i = 0; i < List_size(&table); i++) {
            StrStrMap * ok = List_get(&table, i);
            if (getKey(ok) <= id) {
                List * pRow = List_alloc();
                Csv_addString(pRow, StrStrMap_get(ok, "id"));
                Csv_addString(pRow, StrStrMap_get(ok, "name"));
                Csv_addString(pRow, StrStrMap_get(ok, "type"));
                Csv_addString(pRow, StrStrMap_get(ok, "author"));

                Csv_addRow(&cat, pRow);
            }
        }
    } else {
        for (int i = 0; i < List_size(&table); i++) {
            StrStrMap * ok = List_get(&table, i);

            List * pRow = List_alloc();
            Csv_addString(pRow, StrStrMap_get(ok, "id"));
            Csv_addString(pRow, StrStrMap_get(ok, "name"));
            Csv_addString(pRow, StrStrMap_get(ok, "type"));
            Csv_addString(pRow, StrStrMap_get(ok, "author"));

            Csv_addRow(&cat, pRow);
        }
    }


    if (wasO) {
        if (fout != NULL) {
            Csv_printFile(&cat, fout);
            fclose(fout);
        }
    } else {
        Csv_print(&cat);
    }

    if (wasIn) {
        for (int i = 0; i < 5; i++) {
            free((char*)StrStrMap_get(maps[i], "id"));
            free((char*)StrStrMap_get(maps[i], "name"));
            free((char*)StrStrMap_get(maps[i], "author"));
            free((char*)StrStrMap_get(maps[i], "type"));
            StrStrMap_free(maps[i]);
        }
        for (int i = 0; i < List_size(&table); i++) {
            StrStrMap * tmp = List_get(&table, i);
            if (getKey(tmp) >= id && wasN) {
                free((char*)StrStrMap_get(tmp, "id"));
                free((char*)StrStrMap_get(tmp, "name"));
                free((char*)StrStrMap_get(tmp, "author"));
                free((char*)StrStrMap_get(tmp, "type"));
            }
        }
        for (int i = 0; i < List_size(&table); i++) {
            StrStrMap_free(List_get(&table, i));
        }
        List_deinit(&table);
        Csv_clearTable(&inFile);
        List_deinit(&inFile);
        Csv_clearTable(&cat);
        List_deinit(&cat);
        BSTree_clear(&binT);
    } else {
        for (int i = 0; i < List_size(&cat); i++) {
            List_free(List_get(&cat, i));
        }
        List_deinit(&cat);
        List_deinit(&inFile);
        for (int i = 0; i < List_size(&table); i++) {
            StrStrMap * tmp = List_get(&table, i);
            free((char*)StrStrMap_get(tmp, "id"));
            free((char*)StrStrMap_get(tmp, "name"));
            free((char*)StrStrMap_get(tmp, "author"));
            free((char*)StrStrMap_get(tmp, "type"));
            StrStrMap_deinit(List_get(&table, i));
        }
        
        for (int i = 0; i < List_size(&table); i++) {
            free(List_get(&table, i));
        }
        List_deinit(&table);
    }
    BSTree_deinit(&binT);

    return 0;
}


void   Csv_ListOfListsToTable    (List * inFile, List * table) {
    for (int i = 1; i < List_size(inFile); i++) {
        List_add(table, (StrStrMap*)createLangMap(atoi(List_get(List_get(inFile, i), 0)), List_get(List_get(inFile, i), 1), List_get(List_get(inFile, i), 2), List_get(List_get(inFile, i), 3)));
    }
}

void   Csv_ListOfListsToBinTree    (List * inFile, BSTree * table) {
    for (int i = 1; i < List_size(inFile); i++) {
        BSTree_insert(table, (StrStrMap*)createLangMap(atoi(List_get(List_get(inFile, i), 0)), List_get(List_get(inFile, i), 1), List_get(List_get(inFile, i), 2), List_get(List_get(inFile, i), 3)));
    }
}

StrStrMap * createLangMap(int id, const char * name, const char * type, const char * author) {
    char * id_c = String_allocFromInt(id);
    char * name_c = String_allocCopy(name);
    char * type_c = String_allocCopy(type);
    char * author_c = String_allocCopy(author);

    StrStrMap * map = StrStrMap_alloc();
    StrStrMap_add(map, "id", id_c);
    StrStrMap_add(map, "name", name_c);
    StrStrMap_add(map, "type", type_c);
    StrStrMap_add(map, "author", author_c);
    return map;
}