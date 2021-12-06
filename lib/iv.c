#define _GNU_SOURCE
#include <dlfcn.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/mman.h>
#include <stdio.h>
#include <link.h>
#include <string.h>


int domain_id;

void *libaddresses[3] = {0, 0, 0};
void* domain_id_addr[3] = {0, 0, 0};

void __attribute__((constructor(1024))) __init_memsep(){
    Dl_info info;
    char* addr;
    dladdr1(&domain_id, &info, (void**)(&addr), RTLD_DL_LINKMAP);
    libaddresses[0] = addr;
    domain_id_addr[0] = &domain_id;
    syscall(335, libaddresses, domain_id_addr);
}

