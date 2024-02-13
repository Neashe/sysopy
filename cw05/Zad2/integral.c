#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define BUFFER_SIZE 64

char buffer[BUFFER_SIZE];
double current_pos = 0.0;

double f(double x) {
    return 4/(x*x+1);
}

double integral(double a, double b, double dx) {
    double acc = 0.0;
    for (double x = a; x < b; x += dx)
        acc += f(x)*dx;
    return acc;
}
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

    int fds[n];

    for (int i = 0; i < n; i++) {
        int fd[2];
        pipe(fd);
        if (fork() == 0) {
            close(fd[0]);
            double result = integral(i*n_space, (i+1)*n_space, dx);
            ssize_t size = snprintf(buffer, BUFFER_SIZE, "%f", result);
            write(fd[1], buffer, size);
            exit(EXIT_SUCCESS);
        }
        else {
            close(fd[1]);
            fds[i] = fd[0];
        }
    }

    while(wait(NULL) > 0);

    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        ssize_t size = read(fds[i], buffer, BUFFER_SIZE);
        buffer[size] = '\0';
        sum += strtod(buffer, NULL);
    }

    clock_gettime(CLOCK_REALTIME, &timespec_buff_end);
    struct timespec diff = timespec_diff(timespec_buff_start, timespec_buff_end);

    printf("Result: %lf\nn = %d\ndx = %lf\n", sum, n, dx);
    printf("Time: %lds %ldns\n", diff.tv_sec, diff.tv_nsec);
    printf("-------------\n");
    exit(EXIT_SUCCESS);
}