#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>
#include <fstream>
#include <iostream>

using namespace std;
#include "csv.hpp"
#include "storage.hpp"
#include "cui.hpp"

int main(int argc, char *argv[]) {

    Storage storage("./data/");
    storage.load();
    Cui cui(&storage);
    cui.show();

    return 0;
}