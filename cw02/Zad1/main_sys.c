#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

void replace_sys(char ch1, char ch2, char* input_filename,char* output_filename){
    int input_file;
    int output_file;
    int n;
    char buffer[BUFSIZ];
    if ((input_file = open(input_filename,O_RDONLY))==-1){
        printf("Error opening input file");
        exit(EXIT_FAILURE);
    }
    if ((output_file = open(output_filename,O_WRONLY+O_CREAT,O_TRUNC))==-1){
        printf("Error opening output file");
        exit(EXIT_FAILURE);
    }
    while ((n=read(input_file,buffer,sizeof(buffer)))>0){
        for (int i = 0; i < n; i++){
            if (buffer[i] ==ch1){
                buffer[i] = ch2;
            }
        }
        if (write(output_file,buffer,n)!=n){
            printf("Failed to save data to output file\n");
            exit(EXIT_FAILURE);
        }
        if (n==-1){
            printf("Error reading file\n");
            exit(EXIT_FAILURE);
        }
        if (close(input_file)== -1){
            printf("Error while closing input file\n");
            exit(EXIT_FAILURE);
        }
        if (close(output_file)== -1){
            printf("Error while closing output file\n");
            exit(EXIT_FAILURE);
        }

    }

}
int main(int argc, char *argv[]){
    if (argc !=5){
        printf("Wrong number of arguments");
        exit(EXIT_FAILURE);
    }
    char to_be_changed = argv[1][0];
    char change_to = argv[2][0];

    //poczatek pomiaru czasu
    struct timespec start_time,end_time;
    clock_gettime(CLOCK_MONOTONIC_RAW,&start_time);
    replace_sys(to_be_changed,change_to,argv[3],argv[4]);
    //koniec pomiaru czasu
    clock_gettime(CLOCK_MONOTONIC_RAW,&end_time);
    printf("Execution time (char): %ld s %ld ns\n",end_time.tv_sec-start_time.tv_sec,end_time.tv_nsec-start_time.tv_nsec);

    return 0;
}


