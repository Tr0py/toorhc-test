//#include "app.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <libfile.h>
#include <unistd.h>
#include <stdlib.h>
#include "toorhc.h"

#define ENDO_TOORHC 337
#define ENDO_SWITCH 338
#define LIBFILE 3
#define USER 2

char message[] = MSG;

/** These are test functions for MPI **/
int test_mpi_grant();
int direct_pass(char *msg);
int copy_pass(char *msg);
int grant_pass(char *msg);
int trap_emu_pass(char *msg);

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

    toorhc_config("./toorhc_config");

    // main program reads pkey
    open_output_file("./ssh/pkey");
    
    // use library to read and print file content
    syscall(ENDO_SWITCH, LIBFILE);
    lib_fopen("./data/test", "r");
    syscall(ENDO_SWITCH, USER);

    syscall(ENDO_SWITCH, LIBFILE);
    // this exploited lib func call tries to read pkey
    exploited_func();
    syscall(ENDO_SWITCH, USER);


    // main program reads data
    open_output_file("./data/test");

    // test message passing interfaces
    test_mpi_grant();

    return 0;
}

int test_mpi_grant() {
    int ret;

    printf("app: msg %p\n", message);

    printf("\n\n========TEST DIRECT PASS============\n\n");
    ret = direct_pass(message);
    if (ret != true) {
        printf("app: direct pass fail!\n");
    }

    printf("\n\n========TEST COPY PASS============\n\n");
    ret = copy_pass(message);
    if (ret != true) {
        printf("app: copy pass fail!\n");
    }

    printf("\n\n========TEST GRANT PASS============\n\n");
    ret = grant_pass(message);
    if (ret != true) {
        printf("app: grant pass fail!\n");
    }

    printf("\n\n========TEST TRAP EMU PASS============\n\n");
    ret = trap_emu_pass(message);
    if (ret != true) {
        printf("app: trap emu pass fail!\n");
    }

    return 0;
}

int direct_pass(char *msg) {
    return verify_msg(msg);
}

int copy_pass(char *msg) {
    char *buff;

    buff = get_buff();
    strcpy(buff, msg);

    return verify_msg(buff);
}

#define ALIGN(x,a)              __ALIGN_MASK(x,(typeof(x))(a)-1)
#define __ALIGN_MASK(x,mask)    (((x))&~(mask))
#define PAGE_ALIGN(x)  (void*)ALIGN((unsigned long)x, PAGE_SIZE)
#define PAGE_SIZE 0x1000

int grant_pass(char *msg) {
    int ret;

    ret = pkey_mprotect(PAGE_ALIGN(msg), PAGE_SIZE, PROT_READ, LIBFILE);
    if (ret != 0) {
        perror("app: pkey_mprotect");
        return 1;
    }

    return verify_msg(msg);
}

int trap_emu_pass(char *msg) {
    int ret;


    ret = pkey_mprotect(PAGE_ALIGN(msg), PAGE_SIZE, PROT_READ|PROT_WRITE, 1);
    if (ret != 0) {
        perror("app: pkey_mprotect");
        return 1;
    }
    //*(int*)msg = 1;
    //*(int*)0 = 1;

    return verify_msg(msg);
}