CC=gcc
CFLAGS =-Wall


all: main

main:
	$(CC) $(CFLAGS) -c client.c server.c
	$(CC) client.o -o client -lm
	$(CC) server.o -o server -lm
clean:
	rm *.o server client records records.txt