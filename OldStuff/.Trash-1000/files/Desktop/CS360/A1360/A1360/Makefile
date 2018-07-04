GETWORD=/encs_share/CS/class/cs360
CC=gcc
CFLAGS=-g -std=c99 -pedantic -Wall
CLINKS=-c -g -std=c99 -pedantic -Wall
#-c is used for compiling files before linking them (.o files)

main: main.o hash.o 
	$(CC) $(CFLAGS) -o wordpairs -L${GETWORD}/lib main.o hash.o -lget

hash.o: hash.c hash.h
	$(CC) $(CLINKS) -I${GETWORD}/include hash.c 

main.o: main.c hash.h
	$(CC) $(CLINKS) -I${GETWORD}/include main.c 

clean:
	rm hash.o main.o wordpairs


