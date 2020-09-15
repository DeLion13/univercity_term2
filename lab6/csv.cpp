#include "csv.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <iostream>
#include <strstream>
#include <vector>
#include <string>

using std::vector;
using std::string;

using CsvRow = vector <string>;
using CsvTable = vector <CsvRow>;

CsvTable Csv::createTableFromString(const string & csv_str) {
    CsvTable table;

    const char * p = csv_str.c_str();
    char buf[500];
    int bufX = 0;
    CsvRow row;
    while (1) {
        if (*p == ',' || *p == '\n' || *p == '\0') {
            buf[bufX] = '\0';
            row.push_back(string(buf));
            if (*p == '\n') {
                table.push_back(row);
                row = CsvRow();
            }
            bufX = 0;
        } else {
            buf[bufX] = *p;
            bufX += 1;
        }
        if (*p == '\0') {
            break;
        }
        p += 1;
    }
    
    return table;
}

string Csv::createStringFromTable(const CsvTable & csv_table) {
    string csv_text;

    for (int i = 0; i < csv_table.size(); i++) {
        CsvRow row = csv_table[i];
        for (int j = 0; j < row.size(); j++) {
            string value = row[j];
            csv_text += value;

            if (j != row.size() - 1) {
                csv_text += ',';
            }
        }
        if (i != csv_table.size() - 1) {
            csv_text += '\n';
        }
    }

    return csv_text;
}

void printfStrings(vector <string> & self) {
    for (int i = 0; i < self.size(); i++) {
        printf("%s ", self[i].c_str());
    }
}