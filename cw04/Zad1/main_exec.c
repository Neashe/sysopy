


#include <stdio.h>
#include <unistd.h>
#include <bits/types/sigset_t.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>

int is_parent = 1;
void signal_handler(int signal){
    printf("(%d) Received signal\n",getpid());
}

void print_signal_pending(){
    sigset_t sigset;
    sigpending(&sigset);
    if (sigismember(&sigset, SIGUSR1))
        printf("(%d) Signal pending.\n", getpid());
    else
        printf("(%d) Signal not pending.\n", getpid());
}

void mask_signal(){
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    sigaddset(&action.sa_mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &action.sa_mask, NULL);
}

void raise_signal(){
    printf("(%d) Raising signal.\n", getpid());
    raise(SIGUSR1);
}

void input_handler(char* option){
    if (strcmp(option,"ignore") == 0){
        signal(SIGUSR1,SIG_IGN);
        raise_signal();
    }
    else if (strcmp(option,"mask") == 0){
        if (is_parent){
            mask_signal();
            raise_signal();
        }
    }
    else if (strcmp(option,"pending") == 0){
        if (is_parent){
            mask_signal();
            raise_signal();
        }
        print_signal_pending();
    }
    else{
        fprintf(stderr,"Unkown command\n");
        exit(EXIT_FAILURE);
    }
    fflush(NULL);
}

int main(int argc, char** argv){
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Wrong arguments number!\n");
        exit(EXIT_FAILURE);
    }
    if (argc == 3 && strcmp(argv[2], "execl") != 0) {
        fprintf(stderr, "Wrong argv[2] set!\n");
        exit(EXIT_FAILURE);
    }
    if (argc == 3) {
        is_parent = 0;
    }
    input_handler(argv[1]);

    if (is_parent){
        execl(argv[0], argv[0], argv[1], "execl", NULL);
    }
    exit(EXIT_SUCCESS);

}