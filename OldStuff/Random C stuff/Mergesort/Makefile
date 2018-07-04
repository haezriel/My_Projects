CC=gcc
CFLAGS=-g
DEPS=extra.h

P7:	P7.o extra.o $(DEPS)
	$(CC) $(CFLAGS) -o P7 P7.o extra.o -lm

P7.o:	P7.c $(DEPS)
	$(CC) $(CFLAGS) -c P7.c

extra.o: extra.c $(DEPS)
	$(CC) $(CFLAGS) -c extra.c

clean:
	rm P7 P7.o extra.o

