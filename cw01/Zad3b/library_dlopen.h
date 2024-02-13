#ifndef SYSOPY_LIBRARY_DLOPEN_H
#define SYSOPY_LIBRARY_DLOPEN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
    int current_size;
    int size;
    char** ptr;
} MemoryArray;

MemoryArray* (*create_MemoryArray)(int);
void (*wc_file)(MemoryArray*,char*);
char* (*getValue_at)(MemoryArray*,int);
void (*clear_block)(MemoryArray*,int);
void (*free_MemoryArray)(MemoryArray*);
#endif //SYSOPY_LIBRARY_DLOPEN_H
