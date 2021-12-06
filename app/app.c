//#include "app.h"
#include <stdio.h>
#include <libfile.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE *pfile;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    
    // use library to read and print file content
    pfile = lib_fopen(argv[1], "r");
    fclose(pfile);

    return 0;
}