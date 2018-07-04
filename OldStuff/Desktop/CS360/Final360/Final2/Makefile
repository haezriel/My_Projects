CC=gcc
CFLAGS=-g -std=c99 -pedantic -Wall

all: mftp mftpserv

mftp: mftp.c mftp.h
	$(CC) $(CFLAGS) -o mftp mftp.c -lm
mftpserv: mftpserv.c mftp.h
	$(CC) $(CFLAGS) -o mftpserv mftpserv.c -lm
clean:
	rm mftpserv mftp
