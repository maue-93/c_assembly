#include <stdio.h>
#include "string.h"
#include "cpu.h"



int main(int argc, char *argv[]) {
    if(strcmp(argv[1], "simple_compute") != 0) return 0; // check argv[1]
    char path[30] = "../"; strcat(path, argv[2]); // adjust the path
    read_code_from_file_then_run(path); // run the code
    return 0;
}
