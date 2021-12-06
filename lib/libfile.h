#ifndef LIBFILE_H
#define LIBFILE_H
#define _GNU_SOURCE
#include <err.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MSG "0xTOORHC"

/**
 * @brief Open a file and output its content to stdout.
 * @return FILE* The pointer to the file.
 */
FILE* lib_fopen(const char*, const char*);

/**
 * @brief This is a fake exploited function. It tries to read the 
 * private key.
 */
void exploited_func();

/**
 * @brief Get the buff object. Create a buffer and map it to 
 * its own region.
 * @return char* the address to buff
 */
char* get_buff();

/**
 * @brief Veryfy the correctness of pre-defined message.
 * @param buff address to message
 * @return true message is correct.
 * @return false message is incorrect.
 */
bool verify_msg(char *buff);

#endif