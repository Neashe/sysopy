#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void sig_handler(int signum, siginfo_t *info, void *context){
    printf("Received confirmation\n");
}

void send_signal(pid_t pid, int mode){
    union sigval val;
    val.sival_int = mode;
    sigqueue(pid, SIGUSR1, val);
    printf("Sending SIGUSR1 with mode %d\n", mode);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Wrong number of arguments");
        return 1;
    }
    pid_t catcher_pid = atoi(argv[1]);

    struct sigaction sa;
    sa.sa_sigaction = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    sigset_t set;
    for (int i = 2; i < argc; i++) {
        sigemptyset(&set);
        sigaddset(&set, SIGUSR1);

        int mode = atoi(argv[i]);
        send_signal(catcher_pid, mode);

        printf("Waiting for confirmation from catcher...\n");
        sigsuspend(&sa.sa_mask);
    }

    return 0;
}


