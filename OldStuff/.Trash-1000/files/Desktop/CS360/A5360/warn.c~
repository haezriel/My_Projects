//Michael Allen-Bond
//CS 360
//Dr. Lang
//Assignment 5


#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <signal.h>



int x,y;
int fd[2];							//pipes for in/out
int reader, writer;					//colloquial for readability of pipes

void handler(){
//	printf("handler 1\n");
	x=1;
	y=0;
	
	return;
}
void handler2(){
//	printf("handler 2\n");
	y=1;
	return;
}
void handler3(){
//	printf("handler 3\n");
	return;
}
void handler4(){
//	printf("handler 4 \n");
	y=0;
	return;
}

int main (int argc, char **argv){
pipe (fd);							//initializing pipe
reader=fd[0];
writer=fd[1];
char buffer[5000];
char buffer2[5000];
char stmt[5000];
char exitcheck[5000];
char exitcheck2[5000];
int delay;
int child;
x=0;
y=0;
if ((child=fork())){
	while(1){
		signal(SIGINT,handler);
		if(x==1){
			signal(SIGINT,SIG_IGN);
			x=0;
			printf("Input New Message Now:\n");
			fgets(buffer,5000,stdin);
			sscanf(buffer,"%[^\n]s",exitcheck);
			close(reader);
			write(writer, buffer, sizeof(exitcheck));
			kill(child,SIGFPE);	
			if(strcmp(exitcheck,"exit")==0){
				printf("Exiting\n");
				exit(0);
			}
		}	
	}
}

else {

	close(writer);
	while(1){
		signal(SIGINT,SIG_IGN);
		signal(SIGFPE,handler2);
		if(y==1){
			read(reader,buffer2,sizeof(buffer2));
			sscanf(buffer2,"%s", exitcheck2);
			if(strcmp(exitcheck2,"exit")==0)
					exit(0);
			if(2==(sscanf(buffer2, "%d %[^\n]s", &delay, stmt))){
				while(y==1){
				signal(SIGINT,handler4);
					if(delay>-1){				
						signal (SIGALRM, handler3);			
						if(y==1)							
						alarm(delay);
						if(y==1)
						pause();
						if(y==1)	{		
						fputs(stmt,stdout); fflush(stdout);
						printf("\n");}
					}
					else{
						if(y==1)
						signal (SIGALRM, handler3);
						if(y==1)			
						alarm(5);			
						if(y==1)
						pause();			
						if(y==1){
						fputs(stmt,stdout); fflush(stdout);
						printf("\n");		}		
					}
				}			
			}
			else{
				while(y==1){
					signal(SIGINT,handler4);
					if(y==1)
					signal (SIGALRM, handler3);			
					if(y==1)
					alarm(5);			
					if(y==1)
					pause();			
					if(y==1)
					fputs(buffer2,stdout); fflush(stdout);			
				}
			}
			}	
		}	
}
close(writer);
close(reader);
}

