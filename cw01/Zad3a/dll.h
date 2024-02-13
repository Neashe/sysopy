#ifndef SYSOPY_DLL_H
#define SYSOPY_DLL_H

#ifdef USE_DLL
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void load_dll_symbols(const char* fileName){
    void *handle = dlopen(fileName,RTLD_LAZY);
    if (handle == NULL){
        printf("Symbol not found");
        return;
    }
    *(void **)(&create_MemoryArray) = dlsym(handle,"create_MemoryArray");
    *(void **)(&wc_file) = dlsym(handle,"wc_file");
    *(void **)(&getValue_at) = dlsym(handle,"getValue_at");
    *(void **)(&clear_block) = dlsym(handle,"clear_block");
    *(void **)(&free_MemoryArray) = dlsym(handle,"free_MemoryArray");
}
#else
void load_dll_symbols(const char* fileName){}
#endif
#endif //SYSOPY_DLL_H
