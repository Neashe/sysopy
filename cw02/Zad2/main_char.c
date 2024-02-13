
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    FILE *input_file;
    FILE *output_file;
    struct timespec start_time,end_time;
    clock_gettime(CLOCK_MONOTONIC_RAW,&start_time);

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
    char c;
    int n = fseek(input_file, -1, SEEK_END);
    while (n == 0) {
        c = fgetc(input_file);
        fputc(c, output_file);
        n = fseek(input_file, -2, SEEK_CUR);
    }
    fclose(input_file);
    fclose(output_file);
    clock_gettime(CLOCK_MONOTONIC_RAW,&end_time);
    printf("Execution time (char): %ld s %ld ns\n",end_time.tv_sec-start_time.tv_sec,end_time.tv_nsec-start_time.tv_nsec);
}

