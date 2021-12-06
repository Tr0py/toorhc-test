//#include "app.h"
#include <stdio.h>
#include <libfile.h>
#include <unistd.h>
#include <stdlib.h>

#define ENDO_TOORHC 337
#define ENDO_SWITCH 338
#define LIBFILE 3
#define USER 2

void open_output_file(const char* filename) {
    FILE *pfile;
    char buff[256];

    printf("\napp: =========Trying to read file %s=========\n\n", filename);
    pfile = fopen(filename, "r");
    if (!pfile) {
        perror("app: fopen");
        return;
    }
    while (fgets(buff, 255, pfile)) {
        printf("%s", buff);
    }
    fclose(pfile);
}

int main(int argc, char* argv[]) {

    syscall(ENDO_TOORHC, 3, "./data");
    syscall(ENDO_TOORHC, 2, "./ssh");

    open_output_file("./ssh/pkey");
    
    // use library to read and print file content
    syscall(ENDO_SWITCH, LIBFILE);
    lib_fopen("./data/test", "r");
    syscall(ENDO_SWITCH, USER);

    syscall(ENDO_SWITCH, LIBFILE);
    exploited_func();
    syscall(ENDO_SWITCH, USER);


    open_output_file("./data/test");

    return 0;
}