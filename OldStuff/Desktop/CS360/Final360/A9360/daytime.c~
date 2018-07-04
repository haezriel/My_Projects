//Michael Allen-Bond
//CS 360
//Dr. Lang
//Assignment 9

#define _BSD_SOURCE
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
#include <sys/wait.h>
#define MY_PORT_NUMBER 49999

int main(int argc, char **argv){
if(argc!=2){
	printf("Please enter a hostname.\n");
	exit(0);
}

char *name=argv[1];
int socketfd;
int child;
char message[500];
int read=0;
socketfd=socket(AF_INET,SOCK_STREAM,0);

struct sockaddr_in servaddr;
struct hostent *hostEntry;
struct in_addr **pptr;


memset (&servaddr, 0, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(MY_PORT_NUMBER);


if((hostEntry = gethostbyname(name))==NULL){
	herror("gethostbyname error: ");
	exit(1);
}
pptr = (struct in_addr **) hostEntry->h_addr_list;
memcpy (&servaddr.sin_addr, *pptr, sizeof(struct in_addr));

if(0>(connect(socketfd, (struct sockaddr *) &servaddr, sizeof(servaddr)))){

	perror("Bad connection");
	exit(1);
}


if ((child=fork())==0){
	while(read<=0){
	read=recv(socketfd,(char*) message,sizeof(message),0);
}	
	message[read]='\0';
	char *datetime=message;
	printf("%s",datetime);
	send(socketfd,"exit",sizeof("exit"),0);
	exit(0);

}	


else {
	wait(&child);
	exit(0);
}
wait(&child);
exit(0);
}
