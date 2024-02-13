#biblioteka statyczna
CFLAGS = -Wall
all: static shared dll

main.o: main.c
	gcc $(CFLAGS) -c -o main.o main.c

#static
static: main.o
	gcc $(CFLAGS) -c -o library.o library.c
	ar rcs library.a library.o
	gcc -o static main.o -L. -static -lrary
lib_shared.o: library.c
	gcc $(CFLAGS) -c -fPIC -o lib_shared.o library.c

library.so: lib_shared.o
	gcc -shared -o library.so lib_shared.o

#shared
shared: main.o lib_shared.o library.so
	gcc -o shared main.o -L. -lrary -Wl,-rpath=`pwd`

#dynamic
dll: library.c dll.h main.c
	gcc $(CFLAGS) main.c -o dll -ldl -D USE_DLL

clean:
	rm -f *.o *.gch *.a *.so *.exe static shared dll results*.txt test_input.txt
