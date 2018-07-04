CC=gcc
CFLAGS=-g -std=c99 -pedantic -Wall

all: procon
procon: procon.c buffer.h
	$(CC) $(CFLAGS) -o procon procon.c -lm -pthread
clean:
	rm procon