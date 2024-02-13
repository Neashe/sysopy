#ifdef USE_DLL
#include "library_dlopen.h"
#else
#include "library.h"
#endif

#include "dll.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/times.h>
#include <unistd.h>

#define MAX_COMMAND_SIZE 1024

int main() {
    load_dll_symbols("./library.so");

    char buffer[MAX_COMMAND_SIZE];
    MemoryArray* memoryArray;
    bool is_inited = 0;
    while (true) {
        //odczyt ze standardowego wejscia
        fgets(buffer, MAX_COMMAND_SIZE, stdin);

        //podzial wprowadzonych znakow na komende i argument
        char *command = strtok(buffer, " \n");
        char *arg = strtok(NULL, " \n");

        //pomiar czasu
        clock_t start_time,end_time;
        struct tms start_cpu,end_cpu;
        start_time = times(&start_cpu);
//        printf("%s", command);
        if (strcmp(command,"init")==0 && is_inited==0) {
            if(arg != NULL) {
                char *endpoint;
                int argument = strtol(arg, &endpoint, 10);
                memoryArray = create_MemoryArray(argument);
                is_inited = 1;
            } else printf("Needed argument\n");
        }
        else if (strcmp(command,"count")==0) {
            wc_file(memoryArray, arg);
        }
        else if (strcmp(command,"show")==0){
            if (arg != NULL) {
                char *endpoint;
                int argument = strtol(arg, &endpoint, 10);
                printf("%s\n", getValue_at(memoryArray, argument));
            } else printf("Needed argument\n");
        }
        else if (strcmp(command,"delete")==0) {
            if (arg != NULL) {
            char *endpoint;
            int argument = strtol(arg, &endpoint, 10);
            clear_block(memoryArray, argument);
        }
            else printf("Needed argument\n");
        }
        else if (strcmp(command,"destroy")==0){
            free_MemoryArray(memoryArray);
            is_inited = 0;
        }
        else if (strcmp(command,"exit")==0){
            break;
        }
        else{
            printf("Invalid command\n");
        }
        end_time = times(&end_cpu);
        double real_time = (double)(end_time-start_time)/ sysconf(_SC_CLK_TCK);
        double user_time = (double)(end_cpu.tms_utime-start_cpu.tms_utime)/sysconf(_SC_CLK_TCK);
        double system_time = (double)(end_cpu.tms_stime-start_cpu.tms_stime)/ sysconf(_SC_CLK_TCK);

        printf("Real time: %10f\n",real_time);
        printf("User time: %10f\n",user_time);
        printf("System time: %10f\n",system_time);
    }
    return 0;
}


