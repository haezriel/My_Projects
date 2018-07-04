CC=gcc
CFLAGS= -g -std=c99 -pedantic -Wall 

main: daytime.c dayserve.c
	$(CC) $(CFLAGS) -o daytime daytime.c 
	$(CC) $(CFLAGS) -o dayserve dayserve.c 
clean:
	rm daytime dayserve