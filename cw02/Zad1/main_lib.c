#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void replace_lib(char ch1, char ch2, char* input_filename,char* output_filename){
    FILE *input = fopen(input_filename,"rb");
    if (!input){
        printf("Error opening input file\n");
        exit(EXIT_FAILURE);
    }
    FILE *output = fopen(output_filename,"wb");
    if(!output){
        printf("Error opening output file\n");
        exit(EXIT_FAILURE);
    }
    char buffer[BUFSIZ];
    int n;
    while((n= fread(buffer,1,BUFSIZ,output))>0){
        for(int i = 0;i<n;i++){
            if (buffer[i] == ch1){
                buffer[i] = ch2;
            }
        }
        if (fwrite(buffer,1,n,output) !=n){
            printf("Failed to save data to output file\n");
            exit(EXIT_FAILURE);
        }
    }
    fclose(input);
    fclose(output);
}

int main(int argc, char *argv[]){
    if (argc !=5){
        printf("Wrong number of arguments");
        exit(EXIT_FAILURE);
    }
    char to_be_changed = argv[1][0];
    char change_to = argv[2][0];

    struct timespec start_time,end_time;
    clock_gettime(CLOCK_MONOTONIC_RAW,&start_time);
    replace_lib(to_be_changed,change_to,argv[3],argv[4]);
    clock_gettime(CLOCK_MONOTONIC_RAW,&end_time);
    printf("Execution time (char): %ld s %ld ns\n",end_time.tv_sec-start_time.tv_sec,end_time.tv_nsec-start_time.tv_nsec);

    return 0;

}