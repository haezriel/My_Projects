//Michael Allen-Bond
//CS 360
//Dr. Lang
//Final Assignment

#include "mftp.h"

struct sockaddr_in servAddr;
struct sockaddr_in clientAddr;
socklen_t length;

char cmd[1000];
char buffer[1000];
char message[1000];
char *confirm="A\n";

int listenfd;
int connectfd;
int readc=0;
int debug;

void errMessage(int error)
{
	char *errorout;
	errorout=malloc(M_SIZE*(sizeof(char)));
	strcpy(errorout,"E");
	if(debug) printf("(debug): Sending Server Response: %s\n",errorout);
	switch(error)
	{
	case 1:
		strcat(errorout,"File Doesn't Exist.\n");
		send(connectfd,errorout,strlen(errorout),0);
		break;
	case 2:
		strcat(errorout,"File Already Exists.\n");
		send(connectfd,errorout,strlen(errorout),0);
		break;
	case 3:
		strcat(errorout,"Invalid Input.\n");
		send(connectfd,errorout,strlen(errorout),0);
		break;	
	case 4:
		strcat(errorout,"Bad Pathname.\n");
		send(connectfd,errorout,strlen(errorout),0);
		break;
	case 5:
		strcat(errorout,"Invalid Command.\n");
		send(connectfd,errorout,strlen(errorout),0);
		break;
	}
}

void getSock(){
	struct sockaddr_in servAddr2;
	struct sockaddr_in clientAddr2;
	socklen_t length2;
	int connectfd2;
	int listenfd2;
	int child;
	char *tok;


	listenfd2=socket(AF_INET, SOCK_STREAM,0);
	memset(&servAddr2,0,sizeof(servAddr2));
	servAddr2.sin_family=0;
	servAddr2.sin_port=0;
	servAddr2.sin_addr.s_addr=0;
	
	if (bind(listenfd2,
		(struct sockaddr *) &servAddr2, sizeof(servAddr2))<0){
		perror("bind");
		exit(1);
	}
	socklen_t serv_len=sizeof(servAddr2);
	int check=getsockname(listenfd2,(struct sockaddr *)&servAddr2,&serv_len);
	
	if(check==-1)
		perror("Connection Error.");

	int key=ntohs(servAddr2.sin_port);

	char address[50];

	sprintf(address,"%d",key);
	memset(&message[0],0,sizeof(message));
	strcpy(message,"A");
	strcat(message,address);
	strcat(message,"\n");
	if(debug) printf("(debug): Sending Server Response: %s\n",message);
	send(connectfd,message,strlen(message),0);
	printf("Sending Port Info: %s ",message);
	listen(listenfd2,1);
	length2=sizeof(struct sockaddr_in);


	connectfd2 = accept(listenfd2, (struct sockaddr *) &clientAddr2,
						&length2);	
	if (0>connectfd2){
		perror("bad");
		exit(1);
	}
	printf("Data Connection Established.\n");
	memset(&message[0],0,sizeof(message));
	readc=recv(connectfd,message,M_SIZE,0);
	if(debug) printf("(debug): Incoming Command: %s",message);
	if(readc<=0)
	{
		printf("Socket Closed.\n");
		return;
	}

	if ((child=fork())==0){

		while (1){

			if(message[0]=='L')
			{
				printf("executing ls -l\n");
				if(debug) printf("(debug): Sending Server Response: %s",confirm);
				send(connectfd,confirm,strlen(confirm),0);
				printf("Sending Confirmation Message: %s",confirm);
				close(1);
				dup(connectfd2);
				execlp("ls","ls","-l",(char*)NULL);
				exit(0);
			}
			else if(message[0]=='G')
			{
				sscanf(message,"G%s\n",cmd);

				int fd;
				struct stat path_stat;  
				stat (cmd, &path_stat); 
  				if (!S_ISREG(path_stat.st_mode))
  				{
  					printf("Not a regular file.\n");
					errMessage(4);
					exit(0);
				}
				if(access (cmd, F_OK)<0)
				{
  					
					errMessage(4);
					exit(0);
				}
				if(0>(fd = open(cmd, O_RDONLY)))
				{
					
					errMessage(4);
					exit(0);
				}
				while(1)
				{
					readc=read(fd,message,999);
					write(connectfd2 ,message , readc);
					if(readc==0)
						break;
				}
				printf("Transfer Successful\n");
				if(debug) printf("(debug): Sending Server Response: %s",confirm);
				send(connectfd,confirm,strlen(confirm),0);
				printf("Sending Confirmation Message: %s",confirm);
				exit(0);
			}
			else if(message[0]=='P')
			{
				sscanf(message,"P%s\n",cmd);

				tok=strtok(cmd, "/\n");
				while(NULL!=(tok=strtok(NULL, "/\n")))
				{
					strcpy(cmd,tok);
				}
				int fd;
				if(0>(fd= open(cmd, O_RDWR|O_TRUNC|O_CREAT|O_EXCL, 0777)))
				{
					errMessage(2);
					exit(0);
				}
				if(debug) printf("(debug): Sending Server Response: %s",confirm);
				send(connectfd,confirm,strlen(confirm),0);
				while(1)
				{
					readc=read(connectfd2,message,999);
					write(fd ,message , readc);
					if(readc==0)
						break;
				}
				close(fd);
				printf("Transfer Successful\n");
				printf("Sending Confirmation Message: %s",confirm);
				exit(0);
			}
			else
			{
				errMessage(3);
				exit(0);
			}
		}
	}	


	else 
	{	
		wait(&child);
		if(debug) printf("(debug): Data Connection Closed. \n");
		close(connectfd2);
	}
	return;


}

int main(int argc, char **argv){
	pid_t child;
	struct hostent *hostEntry;
	char *hostName;
	
	if(argc==2 && strcmp(argv[1],"-d")==0)
	{
		debug=1;
		printf ("Debug Mode On.\n");
	}

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

	listen(listenfd,4);

	length=sizeof(struct sockaddr_in);

	while(1){

		connectfd = accept(listenfd, (struct sockaddr *) &clientAddr,
						&length);
		
		if (0>connectfd){
			perror("bad");
			exit(1);
		}

		hostEntry = gethostbyaddr(&(clientAddr.sin_addr),
					sizeof(struct in_addr), AF_INET);
		hostName=hostEntry->h_name;
		if (debug) printf("(debug): Host: %s\n",hostName);

		child=fork();
		if (child==0){

			while (1)
			{	
				readc=recv(connectfd,&buffer[0],M_SIZE,0);
				if(readc<=0)
				{
					printf("Socket Closed.\n");
					exit(0);
				}
				if(debug) printf("(debug): Incoming Command: %s",buffer);
				strcpy(message,buffer);

				if(message[0]=='Q')
				{
					printf("Recieved Exit Command, exiting.\n");
					if(debug) printf("(debug): Sending Server Response: %s",confirm);
					send(connectfd,confirm,strlen(confirm),0);
					exit(0);
				}
				else if(message[0]=='C')
				{
					sscanf(&message[0],"C%s\n",cmd);
					printf("Chdir Parameter: %s\n",cmd);
					if (chdir(cmd)<0)
					{
						errMessage(4); //bad pathname
					}
					else
					{
						printf("Directory Change Successful\n");
						system("pwd");
						if(debug) printf("(debug): Sending Server Response: %s",confirm);
						send(connectfd,confirm,strlen(confirm),0);
					}

				}
				else if(buffer[0]=='D')
				{
					if(debug) printf("(debug): Initiating Data Socket.\n");
					getSock();
				}
				else
					errMessage(5);
				memset(&message[0],0,sizeof(message));
				memset(&buffer[0],0,sizeof(buffer));
			}
				
					
		}	


		else 
		{
			int status;
			close(connectfd);
			while(1)
			{
				waitpid(child, &status, WUNTRACED | WCONTINUED);
				if (WIFEXITED(status)) 
				{
					printf("Child Has Exited.\n");
					kill(child,0);
					break;
            	} 
            	else if (WIFSIGNALED(status)) 
            	{
            		printf("Child Was Interrupted.\n");
					kill(child,0);
					break;
           		} 
           		else if (WIFSTOPPED(status)) 
           		{
           			printf("Child Was Stopped.\n");
					break;
            	} 
			}
		}
	}


}
