#include "libfile.h"
#include <unistd.h>
#define LIBFILE 3
#define USER 2

#define ENDO_TOORHC 337
#define ENDO_SWITCH 338

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

char *get_buff() {
    char* buff;
    int ret;

    buff = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, 
                MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if (!buff) {
        perror("libfile: mmap");
        return NULL;
    }
    ret = pkey_mprotect(buff, 0x1000, PROT_READ | PROT_WRITE, USER);
    if (ret != 0) {
        perror("lib: pkey_mprotect");
    }

    return buff;
}

bool verify_msg(char *buff) {
    syscall(ENDO_SWITCH, LIBFILE);
    printf("libfile: get msg: %s\n", buff);
    if (strcmp(buff, MSG) == 0) {
        printf("good pass!\n");
        syscall(ENDO_SWITCH, USER);
        return true;
    } 
    printf("bad pass!\n");
    syscall(ENDO_SWITCH, USER);
    return false;
}