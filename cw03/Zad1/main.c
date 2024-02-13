
//Napisz program, który przyjmuje jeden argument: argv[1].
//Program ma utworzyć argv[1] procesów potomnych.
//Każdy proces potomny ma wypisać na standardowym wyjściu w jednym wierszu dwa identyfikatory:
//identyfikator procesu macierzystego i swój własny.
//Na końcu standardowego wyjścia proces macierzysty ma wypisać argv[1].
//Wskazówka: aby program na pewno wypisywał argv[1] jako ostatni wiersz standardowego wyjścia,
//należy użyć funkcji systemowej wait.

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
    if (argc !=2){
        printf("Wrong number of arguments!\n");
        exit(EXIT_FAILURE);
    }
    int n = atoi(argv[1]);
    pid_t parent_pid =getpid();
    for (size_t i = 0;i < n; i++){
        if (parent_pid == getpid()){
            //jestesmy w procesie macierzystym
            fork();//tworzymy nowy proces
            if (parent_pid != getpid()){
                //jestesmy w procesie potomnym
                printf("ID macierzyste: %d, ID potomne: %d\n",(int)(getppid()),(int)(getpid()));
                exit(EXIT_SUCCESS);
            }
        }
    }
    for (int i = 0;i<n;i++){
        wait(NULL);
    }

    printf("%d\n",n);
//    if (parent_pid == getpid()){
//        wait(&parent_pid);
//
//    }


}
