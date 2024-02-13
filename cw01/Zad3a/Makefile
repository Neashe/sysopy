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

test: test_static test_shared test_dynamic

test_static: results_static.txt
test_shared: results_shared.txt
test_dynamic: results_dynamic.txt
test_input.txt:
	exec>"test_input.txt";\
	printf "init 10\n";\
	printf "count main.c\n";\
	printf "count library.c\n";\
	printf "show 0\n";\
	printf "show 1\n";\
	printf "delete 1\n";\
	printf "delete 0\n";\
	printf "destroy\n";\
	printf "exit\n"
results_static.txt: test_input.txt static
	./static < "test_input.txt" > "results_static.txt"
results_shared.txt: test_input.txt shared
	./shared < "test_input.txt" > "results_shared.txt"
results_dynamic.txt: test_input.txt dll
	./dll < "test_input.txt" > "results_dynamic.txt"

clean:
	rm -f *.o *.gch *.a *.so *.exe static shared dll results*.txt test_input.txt
