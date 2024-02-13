#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE] = "";
char begin[BUFFER_SIZE] = "";
char end[BUFFER_SIZE] = "";
struct timespec timespec_diff(struct timespec start, struct timespec end) {
    struct timespec out;

    if ((end.tv_nsec-start.tv_nsec)<0) {
        out.tv_sec = end.tv_sec-start.tv_sec-1;
        out.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    }
    else {
        out.tv_sec = end.tv_sec-start.tv_sec;
        out.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return out;
}
int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Wrong number of arguments!\n");
        exit(EXIT_FAILURE);
    }

    struct timespec timespec_buff_start, timespec_buff_end;
    clock_gettime(CLOCK_REALTIME, &timespec_buff_start);

    double dx = strtod(argv[1], NULL);
    int n = atoi(argv[2]);
    if (n*dx > 1) {
        n = 1 / dx;
    }

    double n_space = 1.0 / n;

    mkfifo("/tmp/int_q", 0666);

    for (int i = 0; i < n; i++) {
        if (!fork()) {
            snprintf(begin, BUFFER_SIZE, "%lf", i*n_space);
            snprintf(end, BUFFER_SIZE, "%lf", (i+1)*n_space);
            execl("./sub", "sub", begin, end, argv[1], NULL);
        }
    }

    double sum = 0.0;

    int fifo = open("/tmp/int_q", O_RDONLY);
    int read_count = 0;

    while (read_count < n) {
        wait(NULL);
        ssize_t size = read(fifo, buffer, BUFFER_SIZE);
        buffer[size] = '\0';

        char* token = strtok(buffer, "\n");
        while (token != NULL) {
            sum += strtod(token, NULL);
            read_count++;
            token = strtok(NULL, "\n");
        }
    }

    close(fifo);

    clock_gettime(CLOCK_REALTIME, &timespec_buff_end);
    struct timespec diff = timespec_diff(timespec_buff_start, timespec_buff_end);

    printf("Result: %lf\nn = %d\ndx = %lf\n", sum, n, dx);
    printf("Time: %lds %ldns\n", diff.tv_sec, diff.tv_nsec);
    printf("-------------\n");
    exit(EXIT_SUCCESS);
}