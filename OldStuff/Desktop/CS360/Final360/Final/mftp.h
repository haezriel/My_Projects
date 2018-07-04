//Michael Allen-Bond
//CS 360
//Dr. Lang
//Final Assignment

#define _XOPEN_SOURCE
#define _BSD_SOURCE
#include <errno.h>
#include <features.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/signal.h>
#define MY_PORT_NUMBER 49999
#define M_SIZE 999