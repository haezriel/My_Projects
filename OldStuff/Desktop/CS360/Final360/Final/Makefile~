CC=gcc
CFLAGS=-g -std=c99 -pedantic -Wall

all: mftp mftpserve

mftp: mftp.c mftp.h
	$(CC) $(CFLAGS) -o mftp mftp.c -lm
mftpserve: mftpserve.c mftp.h
	$(CC) $(CFLAGS) -o mftpserve mftpserve.c -lm
clean:
	rm mftpserve mftp
