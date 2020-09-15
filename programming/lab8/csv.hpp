#pragma once

#include <iostream>
#include <strstream>
#include <vector>
#include <string>

using std::vector;
using std::string;

using CsvRow = vector <string>;
using CsvTable = vector <CsvRow>;

namespace Csv
{
    CsvTable createTableFromString(const string & csv_str); 
    string createStringFromTable(const CsvTable & csv_table); 
}