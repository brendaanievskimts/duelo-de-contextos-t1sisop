CC=gcc
CFLAGS=-Wall -pthread

all: threads processos

threads:
	$(CC) src/threads.c -o threads $(CFLAGS)

processos:
	$(CC) src/processos.c -o processos $(CFLAGS)

clean:
	rm -f threads processos