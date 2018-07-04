//Michael Allen-Bond
//CS 360
//Dr. Lang
//Final Assignment

#include "mftp.h"




struct sockaddr_in servaddr;
struct hostent *hostEntry;
struct in_addr **pptr;
FILE *fp;
int socketfd;
int debug;
int readc;
char message[1000];
char incoming[1000];
char cmd[1000];
char cmd2[100];

void output()
{
	int check=0;
	fp = fopen("tmpfileforoutputm.allen-bond.007","r");
	char output[1000];
	struct stat path_stat;
	lstat("tmpfileforoutputm.allen-bond.007", &path_stat);
	if (S_ISREG(path_stat.st_mode))
	{
		if(access ("tmpfileforoutputm.allen-bond.007", R_OK)==0)
		{
			while(NULL!=fgets(output,M_SIZE,fp))
			{
				printf("%s",output);

				check++;
				if(check>=20)
				{
					printf ("Press Enter for next 20 lines...");
					while (fgetc(stdin)!='\n')
					{
						
					}
					check=0;

				}
			}
		}
	}
	printf("\n");
	unlink("tmpfileforoutputm.allen-bond.007");
	fclose(fp);
}

void make_data_connection(char *arg)
{
	int key;
	int child;
	int socketfd2;
	char *tok;

	struct sockaddr_in servaddr2;

	if(debug) printf("(debug): Sending Command: D\n");
	send(socketfd,"D\n",strlen("D\n"),0);
	memset(&message[0],0,sizeof(message));
	readc=recv(socketfd,(int*)&message,M_SIZE,0);
	if(debug) printf("(debug): Server Response: %s",message);
	if(message[0]=='A')
	{
		strcpy(cmd2,message);
		sscanf(cmd2,"A%d\n",&key);

	}
	else
		fprintf(stderr,"Error: %s\n",strerror(errno));

	socketfd2=socket(AF_INET,SOCK_STREAM,0);
	memset (&servaddr2, 0, sizeof(servaddr2));
	servaddr2.sin_family = AF_INET;
	servaddr2.sin_port = htons(key);
	memcpy (&servaddr2.sin_addr, *pptr, sizeof(struct in_addr));
	
	if(0>(connect(socketfd2, (struct sockaddr *) &servaddr2, sizeof(servaddr2))))
	{
		fprintf(stderr,"Error: %s\n",strerror(errno));
		exit(1);
	}
	if(debug) printf("(debug):Data Connection Successful\n");
	memset(&message[0],0,sizeof(message));
	if(strcmp(arg,"S")==0)
		strcpy(message,"G");
	else
		strcpy(message,arg);
	
	strcat(message,cmd);
	message[strlen(message)]='\n';
	if(debug) printf("(debug): Sending Command: %s", message);
	send(socketfd,message,strlen(message),0);
	memset(&message[0],0,sizeof(message));

	if ((child=fork())==0)
	{

		if(strcmp(arg,"L")==0)
		{
			recv(socketfd,incoming,999,0);
			if(debug) printf("(debug): Server Response: %s",incoming);

			if(incoming[0]=='E')
			{
				fprintf(stderr,"%s",&incoming[1]);
				exit(0);
			}

			int fd;
			if(0>(fd= open("tmpfileforoutputm.allen-bond.007", O_RDWR|O_TRUNC|O_CREAT, 0777)))
			{
				fprintf(stderr,"Error: %s\n",strerror(errno));
			}
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
			recv(socketfd,incoming,999,0);
			if(debug) printf("(debug): Server Response: %s",incoming);
			if(incoming[0]=='E')
			{
				fprintf(stderr,"%s",&incoming[1]);
				exit(0);
			}

			int fd;
			tok=strtok(cmd, "/\n");
			while(NULL!=(tok=strtok(NULL, "/\n")))
			{
				strcpy(cmd,tok);
			}
			if(0>(fd= open(cmd, O_RDWR|O_TRUNC|O_CREAT|O_EXCL, 0777)))
			{
				fprintf(stderr,"Error: %s\n",strerror(errno));
				exit(0);
			}
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

			recv(socketfd,incoming,999,0);
			if(debug) printf("(debug): Server Response: %s",incoming);
			if(incoming[0]=='E')
			{
				fprintf(stderr,"%s",&incoming[1]);
				exit(0);
			}

			int fd;

			if(0>(fd = open(cmd, O_RDONLY)))
			{
				fprintf(stderr,"Error: Cannot Open File.\n");
				exit(0);
			}
		
			while(1)
			{
				readc=read(fd,message,999);
				write(socketfd2 ,message , readc);
				if(readc==0)
					break;
			}
			close(fd);
			exit(0);
		}
		else if(strcmp(arg, "S")==0)
		{
			recv(socketfd,incoming,999,0);
			if(debug) printf("(debug): Server Response: %s",incoming);
			if(incoming[0]=='E')
			{
				fprintf(stderr,"%s",&incoming[1]);
				exit(0);
			}
			int fd;
			if(0>(fd= open("tmpfileforoutputm.allen-bond.007", O_RDWR|O_TRUNC|O_CREAT, 0777)))
			{
				fprintf(stderr,"File Creation Error.");
			}
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

		wait(&child);
		close(socketfd2);
	}

return;
}

int main(int argc, char **argv){

	char *tok;
	char buffer[1000];
	char *name;
	if(argc<2){
		printf("Please enter a hostname.\n");
		exit(0);
	}

	if(strcmp(argv[1],"-d")==0 && argc==3)
	{
		debug=1;
		printf ("Debug Mode On.\n");
		name=argv[2];
	}

	else
	{
		debug=0;
		name=argv[1];
	}

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

		fprintf(stderr,"Error: %s\n",strerror(errno));
		exit(1);
	}

//Input Loop Starts Here

	printf("Please enter a Command: ");
	while (NULL!=(fgets(buffer, 1000, stdin)))
	{
		if(debug) printf("(debug): Input: %s",buffer);

		if((tok=strtok(buffer, " \n"))==NULL)
			tok="wrong";

		if(strcmp(tok,"exit")==0)
		{
			if(debug) printf("(debug): Sending Command: Q\n");

			send(socketfd,"Q\n",strlen("Q\n"),0);
			memset(&message[0],0,sizeof(message));
			readc=recv(socketfd, message,sizeof(message),0);

			if(debug) printf("(debug): Server Response: %s",message);
			printf("Exiting\n");
			exit(0);
		}
		else if(strcmp(tok,"cd")==0)
		{

			printf("Changing directories..\n");
			tok=strtok(NULL," \n");
			if (0>chdir(tok))
				fprintf(stderr,"Error: %s\n",strerror(errno));
			else
			{
				if(debug) system("pwd");
			}
				
		}
		else if(strcmp(tok, "rcd")==0)
		{
			if((tok=strtok(NULL, " \n"))==NULL)
			{
				fprintf(stderr,"Error: Must enter a pathname.\n");
			}
			else
			{
				strcpy(message,"C");
				strcpy(cmd,tok);
				strcat(message,cmd);
				strcat(message,"\n");
				if(debug) printf("(debug): Sending Command: %s",message);
				write(socketfd,message,strlen(message));
				memset(&message[0],0,sizeof(message));
				readc=read(socketfd,message,sizeof(message));
				if(debug) printf("(debug): Server Response: %s",message);
				if(message[0]=='E')
				{
					fprintf(stderr,"%s",&message[1]);
				}
			}

		}
		else if(strcmp(tok, "ls")==0)
		{
   			system("ls -l | more -f -20");
		}
		else if(strcmp(tok, "rls")==0)
		{
			if(debug) printf("(debug): Starting Data Connection With Input: L\n");
			make_data_connection("L");
		}
		else if(strcmp(tok, "get")==0)
		{
			tok=strtok(NULL," \n");

			if(tok!=NULL)
			{
				strcpy(cmd,tok);

				char check[500];
				strcpy(check,tok);
				tok=strtok(check, "/");
				while (NULL!=tok)
				{						
					strcpy(check,tok);
					tok=strtok(NULL, "/");
				}

				if  (access(check, F_OK)<0)
				{
					if(debug) printf("(debug): Starting Data Connection With Input: G\n");
					make_data_connection("G");
				}
				else
				{
					fprintf(stderr,"File Already Exists in Client Directory.\n");
				}
			}
			else
				fprintf(stderr,"Must include Pathname after 'get' command.\n");
		}
		else if(strcmp(tok, "show")==0)
		{
			tok=strtok(NULL," \n");
			if(tok!=NULL)
			{
				
				strcpy(cmd,tok);
				if(debug) printf("(debug): Starting Data Connection With Input: S->(G)\n");
				make_data_connection("S");

			}
			else
			{
				fprintf(stderr,"Must include Pathname after 'show' command.\n");
			}
		}
		else if(strcmp(tok, "put")==0)
		{
			tok=strtok(NULL," \n");
			if(tok!=NULL)
			{
				struct stat path_stat;  
				stat (tok, &path_stat); 
				if(access(tok, F_OK | R_OK)==0 && S_ISREG(path_stat.st_mode))
				{
					strcpy(cmd,tok);
					if(debug) printf("(debug): Starting Data Connection With Input: P\n");
					make_data_connection("P");
				}
				else

					fprintf(stderr,"Bad Pathname.\n");
			}
			else
				fprintf(stderr,"Must include Pathname after 'put' command.\n");

		}
		else{
			printf("Invalid input\n");
		}
		memset(&buffer[0],0,sizeof(buffer));
		memset(&message[0],0,sizeof(message));
		printf("Please enter a Command: ");
	}

}
