CC=gcc
CFLAGS=-g -std=c99 -pedantic -Wall

main: test.o sort.o sort.h
	$(CC) $(CFLAGS) -o test test.o sort.o -lm -pthread
test.o: test.c sort.h
	$(CC) $(CFLAGS) -c test.c -pthread
clean:
	rm test test.o
