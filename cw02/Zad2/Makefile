CLAGS = -Wall
CC=gcc
all: main_1024 main_char

main_char:
	$(CC) $(CFLAGS) -c main_char.c
	$(CC) main_char.o -o main_char
main_1024:
	$(CC) $(CFLAGS) -c main_1024.c
	$(CC) main_1024.o -o main_1024
test.txt:
	printf "to jest test funkcji ktora powinna odwrocic ten tekst"
test: main_char main_1024 test.txt
	(./main_char test.txt reversed.txt )>>pomiar_zad_2.txt 2>&1
	(./main_1024 test.txt reversed.txt )>>pomiar_zad_2.txt 2>&1
clean:
	rm -f *.o main_char main_1024 reversed.txt