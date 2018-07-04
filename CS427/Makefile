CC=gcc
CFLAGS=-g -std=c99 -pedantic -Wall

all: encrypt decrypt
encrypt: encrypt.c
	$(CC) $(CFLAGS) -o encrypt encrypt.c -lm 
decrypt: decrypt.c
	$(CC) $(CFLAGS) -o decrypt decrypt.c -lm 
clean:
	rm encrypt decrypt
