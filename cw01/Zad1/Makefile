#static
all: library_static library_shared

library_static: library.c
	gcc -Wall -c -o library.o library.c
	ar cr library.a library.o

library_shared: library.c
	gcc -Wall -c -fPIC library.c
	gcc -Wall -shared -o library.so library.o

clean:
	rm -f *.o *.gch *.a *.so
