CC = gcc -Wall

all: clean main

main:
	$(CC) hairdresser.c -o hairdresser

test: main
	./hairdresser 6 4 2 5
clean:
	rm -f hairdresser