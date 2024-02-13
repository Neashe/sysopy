
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define BLOCK_SIZE 1024
int main(int argc, char *argv[]) {

    struct timespec start_time,end_time;
    clock_gettime(CLOCK_MONOTONIC_RAW,&start_time);

    FILE *input_file;
    FILE *output_file;
    char buffer[BLOCK_SIZE];

    if (argc != 3) {
        printf("Wrong number of arguments!\n");
        return -1;
    }
    input_file = fopen(argv[1], "r");
    output_file = fopen(argv[2], "w");
    if (input_file == NULL) {
        printf("Failed to open input file\n");
        return -1;
    }
    int bytes;
    for(bytes=0; getc(input_file)!=EOF;bytes++);
    int bytes_read;
    int n = fseek(input_file,-BLOCK_SIZE,SEEK_END);
    while (n == 0){
        bytes_read = fread(buffer,sizeof(char ),BLOCK_SIZE,input_file);
        //odwroc stringa
        for (int i = 0;i<bytes_read/2;i++){
            char temp = buffer[i];
            buffer[i] = buffer[bytes_read-i-1];
            buffer[bytes_read-i-1] = temp;
        }
        fwrite(buffer,sizeof (char),bytes_read,output_file);
        n = fseek(input_file,-(2*BLOCK_SIZE),SEEK_CUR);
    }
    fseek(input_file,0,SEEK_SET);
    bytes_read = fread(buffer,sizeof(char),bytes%BLOCK_SIZE,input_file);
    for (int i = 0;i <bytes_read/2;i++){
        char tmp = buffer[i];
        buffer[i] = buffer[bytes_read-i-1];
        buffer[bytes_read-i-1] = tmp;
    }
    fwrite(buffer,sizeof(char),bytes_read,output_file);

    fclose(input_file);
    fclose(output_file);

    clock_gettime(CLOCK_MONOTONIC_RAW,&end_time);
    printf("Execution time (blocks): %ld s %ld ns\n",end_time.tv_sec-start_time.tv_sec,end_time.tv_nsec-start_time.tv_nsec);

    return 0;
}


