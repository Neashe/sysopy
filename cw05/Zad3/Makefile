CFLAGS=-Wall -O3

all: integral sub

integral: integral.c
	gcc $(CFLAGS) integral.c -o integral

sub: sub.c
	gcc $(CFLAGS) sub.c -o sub

report: all

	echo "" > report.txt
	./integral 0.000000001 6  >> report.txt
	./integral 0.000000005 8  >> report.txt
	./integral 0.0000000001 10 >> report.txt

clean:
	rm -f integral sub