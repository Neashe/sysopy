CFLAGS = -Wall
all: main

main.o: main.c
	gcc $(CFLAGS) -c -o main.o main.c
main: main.o
	gcc main.o -o main
clean:
	rm -f *.o main