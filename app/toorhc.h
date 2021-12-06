#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ENDO_TOORHC 337
#define LIBFILE 3
#define MAIN 2

int toorhc_config(const char* filename) {
    FILE* fpcfg;
    char domain[16], dir[16];
    int dom;

    fpcfg = fopen(filename, "r");
    if (!fpcfg) {
        perror("toorhc fopen");
        return -1;
    }

    while (fscanf(fpcfg, "%s %s\n", domain, dir) > 0) {
        printf("toorhc config: domain: %s, dir: %s\n", domain, dir);
        dom = (strcmp(domain, "MAIN") == 0) ? 2 : 3;
        syscall(ENDO_TOORHC, dom, dir);
    }
    return 0;

}