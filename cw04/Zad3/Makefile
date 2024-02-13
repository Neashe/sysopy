CFLAGS = -Wall

all: catcher sender

catcher: catcher.c
	gcc $(CFLAGS) catcher.c -o catcher

sender: sender.c
	gcc $(CFLAGS) sender.c -o sender
clean:
	rm -f catcher sender