#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archive_definition.h"

int main(int argc, char *argv[]) {
    unsigned char **hex = read_data(argc - 1, argv);
    arch_def(argc - 1, hex, argv);
    free_mem(argc - 1, hex);
    return 0;
}
