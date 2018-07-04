//Michael Allen-Bond
//CS 360
//Dr. Lang
//Assignment 4
/* To compile this file, just type make.
To run it, type ./connect <args> : <args>
Thank you for your time.
*/




#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>


int i=1;
char *args[2500];
char *args2[2500];
/* To make recursive
void piper(){

}
*/
int main(int argc, char **argv){
int fd[2];							//pipes for in/out
pipe (fd);							//initializing pipe
int reader, writer;					//colloquial for readability of pipes
reader=fd[0];
writer=fd[1];

if (argv [1] ==NULL){
	perror("Failure: No Arguments.");	//Checks for no args
	exit(1);
}
while (argv[i]!=NULL && strcmp(argv[i],":")){
		args[i-1]=argv[i];
		i++;

}

if (argv[i]==NULL){					//Checks for missing colon
	perror("Failure: no Colon separator followed by second clause.");
	exit(1);
}
i++;

int j=0;

while (argv[i]!=NULL){

		args2[j]=argv[i];
		j++;
		i++;


}


if (args2[0]==NULL){			//Checks for missing second set of args
	perror("Execution Failed: No second arg set");
	exit(1);
}


if (fork()){	

	close(0);					//Closes Stdin
	dup(reader);				//creates new stdin
	close(writer);				//closes writer(if open)
	close(reader);				//closes reader
	execvp(args2[0],args2);		//executes second argset
    perror("execvp failed");
	exit(1);	

}

else {

	close(1);					//closes stdout
	dup(writer);				//creates new stdout in writer
	close(reader);				//closes reader (stdin)
	close(writer);				//closes writer (stdout)
	execvp(args[0],args);    	//executes first argset
	perror("execvp failed");
	exit(1);
}



}


