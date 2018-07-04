
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

int kill(pid_t pid, int sig);

int main(){
	int child1,status;
	int child2;
	time_t timer=time(NULL);

	if((child1=fork())==0){
		while(1){
			if(time(NULL)>timer+10){
			printf("I'm child 1, I'm dead now.\n");
			exit(0);
		}
		}
	}
	if((child2=fork())==0){
		while(1){
			if(time(NULL)> timer+5){
				timer=time(NULL);
			printf("I'm child 2, I'll keep spamming until my parents kill me.\n");
		}
		}
	}
while(1){
if(child1==waitpid(child1,&status,WNOHANG)){
printf("Child1 dead, killing Child2.\n");
kill(child2,SIGKILL);
printf("Child2 is dead. Exiting Parent.\n");
exit(0);}
}
}