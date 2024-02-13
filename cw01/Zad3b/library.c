#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"


MemoryArray* create_MemoryArray(int size){
    MemoryArray* memoryArray;
    memoryArray = (MemoryArray*)malloc(sizeof(MemoryArray));
    memoryArray->size=size;
    memoryArray->current_size = 0;
    memoryArray->ptr = calloc(size, sizeof(char*));
    return memoryArray;
}
long get_fileSize(FILE* file){
    fseek(file,0,SEEK_END);
    long size = ftell(file);
    fseek(file,0,SEEK_SET);
    return size;
}

char* get_content(char* fileName){
    FILE* file = fopen(fileName,"r");
    size_t size = get_fileSize(file);
    char* buff = calloc(size,sizeof(char));
    fread(buff,sizeof(char),size,file);
    fclose(file);
    return buff;
}
void wc_file(MemoryArray* memoryArray, char* fileName){
    char tmpFilename[] = "/tmp/temp-XXXXXX";
    char wcTemp[255] = "wc ";
    char s[] =" > ";
    mkstemp(tmpFilename);

    strcat(wcTemp,fileName);
    strcat(wcTemp,s);
    strcat(wcTemp,tmpFilename);
    int e= system(wcTemp);
    if (e == 0){
        char* buff = get_content(tmpFilename);
        if (memoryArray->current_size < memoryArray->size){
            memoryArray->ptr[memoryArray->current_size] =(char*) calloc(strlen(buff),sizeof(char));
            strcpy(memoryArray->ptr[memoryArray->current_size],buff);
            memoryArray->current_size++;
        }
        else{
            printf("Not enough memory");
        }
    }
    //usun plik tymczasowy
    if (remove(tmpFilename) != 0){
        perror("Failed to delete temporary file");
        exit(EXIT_FAILURE);
    }
}
char* getValue_at(MemoryArray* memoryArray, int index){
    if (memoryArray->current_size<=index){
        return "Wrong index";
    }
    return memoryArray->ptr[index];
}
void clear_block(MemoryArray* memoryArray, int index){
    if (index >= 0 && index< memoryArray->current_size){
        free(memoryArray->ptr[index]);
        while (index < memoryArray->current_size-1){
            memoryArray->ptr[index] = memoryArray->ptr[index+1];
            index++;
        }
        memoryArray->current_size--;
    }

}
void free_MemoryArray(MemoryArray* memoryArray){
    for (int i = 0; i<memoryArray->current_size;i++){
        free(memoryArray->ptr[i]);
    }
    free(memoryArray->ptr);
    free(memoryArray);
}


