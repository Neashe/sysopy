#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE] = "";

double f(double x) {
    return 4/(x*x+1);
}

double integral(double a, double b, double dx) {
    double acc = 0.0;
    for (double x = a; x < b; x += dx)
        acc += f(x)*dx;
    return acc;
}

int main(int argc, char** argv) {
    double begin = strtod(argv[1], NULL);
    double end = strtod(argv[2], NULL);
    double dx = strtod(argv[3], NULL);

    double res = integral(begin, end, dx);
    ssize_t size = snprintf(buffer, BUFFER_SIZE, "%f\n", res);

    int fifo = open("/tmp/int_q", O_WRONLY);
    write(fifo, buffer, size);
    close(fifo);
    exit(EXIT_SUCCESS);
}