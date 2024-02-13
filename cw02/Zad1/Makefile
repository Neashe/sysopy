CLAGS = -Wall
CC=gcc
all: lib sys

lib:
	$(CC) $(CFLAGS) -c main_lib.c
	$(CC) main_lib.o -o lib

sys:
	$(CC) $(CFLAGS) -c main_sys.c
	$(CC) main_sys.o -o sys
test: lib sys test.txt
	(./lib a O test.txt changed.txt )>>pomiar_zad_1.txt 2>&1
	(./sys a O test.txt changed.txt )>>pomiar_zad_1.txt 2>&1
clean:
	rm -f *.o sys lib changed.txt