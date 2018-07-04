GETWORD=
CC=gcc
CFLAGS=-g -std=c99 -pedantic -Wall
CLINKS=-c -g -std=c99 -pedantic -Wall
#-c is used for compiling files before linking them (.o files)

main: main.o hash.o 
	$(CC) $(CFLAGS) -o words -L${GETWORD}/lib main.o hash.o -lget

hash.o: hash.c hash.h getWord.h
	$(CC) $(CLINKS) -I${GETWORD}/include hash.c 

main.o: main.c hash.h getWord.h
	$(CC) $(CLINKS) -I${GETWORD}/include main.c 

getWord.o: getWord.c
clean:
	rm hash.o main.o words make


