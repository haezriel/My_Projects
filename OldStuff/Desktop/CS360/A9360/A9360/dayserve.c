//Michael Allen-Bond
//CS 360
//Dr. Lang
//Assignment 9

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

struct sockaddr_in servAddr;



int main(){

	char messagein[500];
	int recieved;

	int listenfd;
	int child;
	listenfd=socket(AF_INET, SOCK_STREAM,0);

	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(MY_PORT_NUMBER);
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);

	if (bind(listenfd,
		(struct sockaddr *) &servAddr, sizeof(servAddr))<0){
		perror("bind");
		exit(1);
	}


	listen(listenfd,1);

	int connectfd;
	socklen_t length=sizeof(struct sockaddr_in);
	struct sockaddr_in clientAddr;
	while(1){
		connectfd = accept(listenfd, (struct sockaddr *) &clientAddr,
						&length);
		if (0>connectfd){
			perror("bad");
			exit(1);
		}
		struct hostent *hostEntry;
		char *hostName;

		hostEntry = gethostbyaddr(&(clientAddr.sin_addr),
					sizeof(struct in_addr), AF_INET);
		hostName=hostEntry->h_name;
		if ((child=fork())==0){

			time_t curtime;

			time(&curtime);
			char* message=ctime(&curtime);
			strcat(message,"\0");
			printf("%s\n",hostName);
			//while(1){
				recieved=0;
				if(message!=NULL){
					send(connectfd,(char*)message,strlen(message),0);
					message=NULL;
				}
				
			//}
			exit(0);					
		}	


		else {
			close(connectfd);
			}
	}


}
