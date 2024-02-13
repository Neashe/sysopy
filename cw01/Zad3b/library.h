
#ifndef SYSOPY_LIBRARY_H
#define SYSOPY_LIBRARY_H

typedef struct {
    int current_size;
    int size;
    char** ptr;
} MemoryArray;

MemoryArray* create_MemoryArray(int size);
void wc_file(MemoryArray* memoryArray,char* fileName);
char* getValue_at(MemoryArray* memoryArray, int index);
void clear_block(MemoryArray* memoryArray,int index);
void free_MemoryArray(MemoryArray* memoryArray);

#endif //SYSOPY_LIBRARY_H
