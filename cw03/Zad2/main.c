#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Program requires exactly one argument\n");
        return EXIT_FAILURE;
    }
//    printf("%s", argv[0])
    printf("Program name: %s",basename(argv[0]));
    fflush(stdout);
    execl("/bin/ls", "ls", argv[1], NULL);
    perror("Error calling execl");
    return EXIT_FAILURE;
}
