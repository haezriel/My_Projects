//Michael Allen-Bond
//CS 360
//Dr. Lang
//Final Assignment

#include "mftp.h"



int socketfd;
char message[1000];
char incoming[1000];
char *cmd;
char *cmd2;
int readc;
struct sockaddr_in servaddr;
struct hostent *hostEntry;
struct in_addr **pptr;
FILE *fp;

void output()
{

	int check=0;
	fp = fopen("tmpfileforoutputm.allen-bond.007","r");
	char output[1000];

	
	while(NULL!=fgets(output,M_SIZE,fp))
	{
		printf("%s",output);
		check++;
		if(check==20)
		{
			printf ("Press enter for next 20 lines...");
			while (fgetc(stdin)!='\n')
			{
				
			}
			check=0;

		}
	}
	
	fclose(fp);
	unlink("tmpfileforoutputm.allen-bond.007");
}

void make_data_connection(char *arg)
{
	int key;
	int child;
	int socketfd2;
	char *tok;

	struct sockaddr_in servaddr2;
	send(socketfd,"D\n",sizeof("D\n"),0);
	readc=recv(socketfd,(int*)&message,M_SIZE,0);
	if(message[0]=='A')
	{
		cmd2=malloc(sizeof(message));
		strcpy(cmd2,message);
		cmd2++;
		sscanf(cmd2,"%d\n",&key);

	}
	else
		perror("error with connection..");

	socketfd2=socket(AF_INET,SOCK_STREAM,0);
	memset (&servaddr2, 0, sizeof(servaddr2));
	servaddr2.sin_family = AF_INET;
	servaddr2.sin_port = htons(key);
	memcpy (&servaddr2.sin_addr, *pptr, sizeof(struct in_addr));
	
	if(0>(connect(socketfd2, (struct sockaddr *) &servaddr2, sizeof(servaddr2))))
	{
		perror("Bad connection");
		exit(1);
	}


	if ((child=fork())==0)
	{

		if(strcmp(arg,"L")==0)
		{

			int fd;
			if(0>(fd= open("tmpfileforoutputm.allen-bond.007", O_RDWR|O_TRUNC|O_CREAT|O_EXCL, 0777)))
			{
				perror("Error, Line 76.");
			}
			send(socketfd,"L\n",strlen("L\n"),0);
			while(1)
			{	
				readc=read(socketfd2,message,999);
				write(fd ,message , readc);
				if(readc==0)
					break;
			}
			close(fd);
			output();
			exit(0);
		}
		else if (strcmp(arg,"G")==0)
		{
			strcpy(message,"G");
			strcat(message,cmd);
			tok=strtok(cmd, "/\n");
			while(NULL!=(tok=strtok(NULL, "/\n")))
			{
				strcpy(cmd,tok);
			}
			int fd;
			if(0>(fd= open(cmd, O_RDWR|O_TRUNC|O_CREAT|O_EXCL, 0777)))
			{
				send(socketfd,"bad",strlen("bad"),0);
				perror("File Creation Error: File already exists.");
				exit(0);
			}
			message[strlen(message)]='\n';
			send(socketfd,message,strlen(message),0);
			while(1)
			{
				readc=read(socketfd2,message,999);
				write(fd ,message , readc);
				if(readc==0)
					break;
			}
			close(fd);

			exit(0);
		}
		else if(strcmp(arg,"P")==0)
		{
			strcpy(message,"P");
			strcat(message,cmd);
			message[strlen(message)]='\n';
			send(socketfd,message,strlen(message),0);
			int fd;
			if(0>(fd = open(cmd, O_RDONLY)))
			{
				perror("Invalid Path");

			}
			while(1)
			{
				readc=read(fd,message,999);
				write(socketfd2 ,message , readc);
				if(readc==0)
					break;
			}
			printf("are we getting here?\n");
			close(fd);
			exit(0);
		}
		else if(strcmp(arg, "S")==0)
		{
			strcpy(message,"G");
			strcat(message,cmd);
			int fd;
			if(0>(fd= open("tmpfileforoutputm.allen-bond.007", O_RDWR|O_TRUNC|O_CREAT|O_EXCL, 0777)))
			{
				perror("Error, Line 76.");
			}
			message[strlen(message)]='\n';
			send(socketfd,message,strlen(message),0);
			while(1)
			{
				readc=read(socketfd2,message,999);
				write(fd ,message , readc);
				if(readc==0)
					break;
			}
			close(fd);
			output();

			exit(0);

		}

	}
	else 
	{
	recv(socketfd,incoming,999,0);
	if(incoming[0]=='E')
	{
		fprintf(stderr,"%s",&incoming[1]);
	}
	}

return;
}

int main(int argc, char **argv){
cmd=malloc(M_SIZE*sizeof(char));


if(argc!=2){
	printf("Please enter a hostname.\n");
	exit(0);
}

char *name=argv[1];
//int child;
socketfd=socket(AF_INET,SOCK_STREAM,0);

memset (&servaddr, 0, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(MY_PORT_NUMBER);


if((hostEntry = gethostbyname(name))==NULL)
{
	herror("gethostbyname error: ");
	exit(1);
}
pptr = (struct in_addr **) hostEntry->h_addr_list;
memcpy (&servaddr.sin_addr, *pptr, sizeof(struct in_addr));

if(0>(connect(socketfd, (struct sockaddr *) &servaddr, sizeof(servaddr))))
{

	perror("Bad connection");
	exit(1);
}


//if ((child=fork())==0)
//{

	char *tok;
	char buffer[1000];


	printf("Please enter a Command: ");
	while (NULL!=(fgets(buffer, 1000, stdin)))
	{

		if((tok=strtok(buffer, " \n"))==NULL)
			tok="wrong";

		if(strcmp(tok,"exit")==0)
		{
			send(socketfd,"Q\n",sizeof("Q\n"),0);
			readc=recv(socketfd,(char*) message,sizeof(message),0);
			if(message[0]=='A')
			{
				printf("Exiting\n");
				exit(0);
			}
		}
		else if(strcmp(tok,"cd")==0)
		{
			printf("changing directories..\n");
			tok=strtok(NULL," \n");
			if (0>chdir(tok))
				fprintf(stderr,"Error: %s\n",strerror(errno));

		}
		else if(strcmp(tok, "rcd")==0)
		{
			if((tok=strtok(NULL, " \n"))==NULL)
				tok="1null1";
			
			strcpy(message,"C");
			strcpy(cmd,tok);
			strcat(message,cmd);
			strcat(message,"\n");
			printf("%s",message);
			write(socketfd,message,strlen(message));
			readc=read(socketfd,(char*)message,sizeof(message));
			if(message[0]=='E')
			{
				fprintf(stderr,"%s",&message[1]);
			}
			

		}
		else if(strcmp(tok, "ls")==0)
		{
			cmd="ls -l | more -f -20";
   			system(cmd);
		}
		else if(strcmp(tok, "rls")==0)
		{
			make_data_connection("L");
		}
		else if(strcmp(tok, "get")==0)
		{
			tok=strtok(NULL," \n");
			if(tok!=NULL)
			{
				
				strcpy(cmd,tok);
				make_data_connection("G");

			}
		}
		else if(strcmp(tok, "show")==0)
		{
			tok=strtok(NULL," \n");
			if(tok!=NULL)
			{
				
				strcpy(cmd,tok);
				make_data_connection("S");

			}
		}
		else if(strcmp(tok, "put")==0)
		{
			tok=strtok(NULL," \n");
			if(tok!=NULL)
			{
				
				strcpy(cmd,tok);
				make_data_connection("P");

			}
		}
		else{
			printf("Invalid input\n");
		}
		printf("Please enter a Command: ");
	}

free(cmd);
}
