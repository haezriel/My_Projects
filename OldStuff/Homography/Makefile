CC=gcc
COPTS=-g -Wall -std=c99

homography: homography.o LUdecomp.o
	$(CC) $(COPTS) $^ -lm -o $@

homography.o: homography.c LUdecomp.h
LUdecomp.o: LUdecomp.c LUdecomp.h

clean:
	-rm homography LUdecomp.o homography.o

