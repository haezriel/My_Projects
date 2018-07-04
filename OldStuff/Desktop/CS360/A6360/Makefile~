CC=gcc
CFLAGS=-g -std=c99 -pedantic -Wall

main: philo.o random.o random.h
	$(CC) $(CFLAGS) -o philo philo.o random.o -lm
philo.o: philo.c random.h
	$(CC) $(CFLAGS) -c philo.c
clean:
	rm philo philo.o
