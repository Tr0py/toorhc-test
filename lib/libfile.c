#include "libfile.h"
#include <err.h>
#include <stdlib.h>

FILE* lib_fopen(const char* filename, const char* modes) {
    FILE *ret;
    char buff[256];

    printf("\nlibfile: =========Trying to read file %s=========\n\n", filename);

    ret = fopen(filename, modes);
    if (!ret) {
        perror("libfile: fopen");
        return NULL;
    }

    //printf("file content:\n===============\n");
    while (fgets(buff, 255, ret)) {
        printf("libfile: %s", buff);
    }
    //printf("\n==============\nEOF\n");

    fclose(ret);

    return ret;
}

void exploited_func() {
    lib_fopen("./ssh/pkey", "r");
}