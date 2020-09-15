#include "storage.hpp"
#include "csv_storage.h"
#include "xml_storage.h"
#include "cui.hpp"

int main(int argc, char *argv[]) {
   XmlStorage xml_storage("../lab6/data/xml/");
   //CsvStorage csv_storage("../lab6/data/csv/");

   Storage * storage_ptr = &xml_storage;
   storage_ptr -> load();

   Cui cui(storage_ptr);
   cui.show();

    return 0;
}
