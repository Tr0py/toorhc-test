#include "libfile.h"

FILE* lib_fopen(const char* filename, const char* modes) {
    FILE *ret;
    char buff[256];
    ret = fopen(filename, modes);

    printf("file content:\n===============\n");
    while (fgets(buff, 255, ret)) {
        printf("%s", buff);
    }
    printf("\n==============\nEOF\n");

    return ret;
}