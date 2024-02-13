CFLAGS = -Wall
PROGRAM_FORK = "main_fork"
PROGRAM_EXECL = "main_exec"
REPORT_OUT = "raport2.txt"


all: main_fork main_exec

main_exec.o: main_exec.c
	gcc $(CFLAGS) -c -o main_exec.o main_exec.c
main_fork.o: main_fork.c
	gcc $(CFLAGS) -c -o main_fork.o main_fork.c
main_exec: main_exec.o
	gcc main_exec.o -o main_exec
main_fork: main_fork.o
	gcc main_fork.o -o main_fork

test: all

	echo ">>> FORK <<<" > $(REPORT_OUT)
	echo "HANDLER:" >> $(REPORT_OUT)
	./main_fork handler >> $(REPORT_OUT)
	echo "IGNORE:" >> $(REPORT_OUT)
	./main_fork ignore >> $(REPORT_OUT)
	echo "MASK:" >> $(REPORT_OUT)
	./main_fork mask >> $(REPORT_OUT)
	echo "PENDING:" >> $(REPORT_OUT)
	./main_fork pending >> $(REPORT_OUT)

	echo "\n>>> EXECL <<<" >> $(REPORT_OUT)
	echo "IGNORE:" >> $(REPORT_OUT)
	./main_exec ignore >> $(REPORT_OUT)
	echo "MASK:" >> $(REPORT_OUT)
	./main_exec mask >> $(REPORT_OUT)
	echo "PENDING:" >> $(REPORT_OUT)
	./main_exec pending >> $(REPORT_OUT)

clean:
	rm -f *.o main_fork main_exec