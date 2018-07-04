CC=gcc
CFLAGS=-g -std=c99 -pedantic -Wall

main: philo2.o random_r.o random_r.h
	$(CC) $(CFLAGS) -o philo2 philo2.o random_r.o -lm -pthread
philo2.o: philo2.c random_r.h
	$(CC) $(CFLAGS) -c philo2.c -pthread
clean:
	rm philo2 philo2.o
