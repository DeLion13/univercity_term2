#include "storage.hpp"
#include "csv_storage.h"
#include "xml_storage.h"
#include "sqlite_storage.h"
#include "cui.hpp"

int main(int argc, char *argv[]) {
//   XmlStorage xml_storage("../lab8/data/xml/");
   SqliteStorage sql_storage("../lab8/data/sqlite/");
   //CsvStorage csv_storage("../lab8/data/csv/");

   Storage * storage_ptr = &sql_storage;
   storage_ptr -> load();

   Cui cui(storage_ptr);
   cui.show();

    return 0;
}
