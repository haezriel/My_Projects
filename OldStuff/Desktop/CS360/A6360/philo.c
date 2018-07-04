//Michael Allen-Bond
//CS 360
//Dr. Lang
//Assignment 6
//To compile, type "make". to run, type ./philo. Be warned, this thing runs for at least 500 seconds before finishing, unless you interrupt it.

#define _XOPEN_SOURCE 700
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include "random.h"


union semun {
int              val;    //Copied directly from man pages, because why not.
struct semid_ds *buf;  
unsigned short  *array; 
struct seminfo  *__buf;  

} ;

int main(){
struct sembuf hashi[4];		//This holds our semaphore operations in a buffer, so that they can all be executed in an atomic set
int count1,count2,count3,count4,count5;  //This is our seconds counter for each philosopher
count1=count2=count3=count4=count5=0;
int ID;						//This is our Semaphore ID
int think[5];				//This is our thinking array, which holds an int for each philosopher
int eat[5];					//This is our eating array, same as the thinking array
int key=getuid();			//This is our key for the semaphore, I'm just using our userid for it
ID = semget((key_t)key,5, 0666 | IPC_CREAT);  //This initializes our semaphore array
int child1,child2,child3,child4,child5;		//This initializes our child ID ints

for(int i=0; i<5; i++)				//This sets all the semaphores values to 0
	semctl(ID, i, SETVAL, 0);

/* Each Child's code is identical, save the semaphore numbers used in the semops, and the eat,think, and count integers. I'm aware that this could be done more efficiently using a 'for' loop to reference the various children (I saw it in an example), but this was much more readable to me, and when coding, I needed to be able to understand exactly what I was doing with the semaphores, without any extra complications. As such, I'm commenting the first child's code only, as the rest would be the exact same comments.*/

if((child1=fork())==0){
while(1){
	hashi[0].sem_num=0;				//This references the semaphore number, in this case, the first semaphore (out of 5)
	hashi[0].sem_op=0;				//This references what we are doing (in this case,checking if the value is 0)
	hashi[0].sem_flg=0;				
	
	hashi[1].sem_num=1;				//So in this case, I'm checking the 2nd semaphore for a 0 value
	hashi[1].sem_op=0;
	hashi[1].sem_flg=0;

	hashi[2].sem_num=0;				//here, I change the 1st semaphore value to 1
	hashi[2].sem_op=1;
	hashi[2].sem_flg=0;

	hashi[3].sem_num=1;				//here, I change the 2nd semaphore value to 1
	hashi[3].sem_op=1;
	hashi[3].sem_flg=0;
	
if (semop(ID, hashi, 4) == -1) {		//This executes all of the above operations in an atomic set.
	perror("semop");
	exit(EXIT_FAILURE);
}

	eat[0]=randomGaussian(9,3);		//This gets a random eating time
	think[0]=randomGaussian(11,7);	//random thinking time
	if(eat[0]<0) eat[0]=0;			//sets to 0 if bad(negative) value
	if(think[0]<0) think[0]=0;		//same^
	
	printf("Philosopher #1 is eating for %d seconds.\n",eat[0]);
	sleep(eat[0]);
	printf("Philosopher #1 is done eating, thinking for %d seconds.\n", think[0]);

	hashi[0].sem_num=0;			//setting semaphore 1([0]) back to 0
	hashi[0].sem_op=-1;
	hashi[0].sem_flg=0;
	
	hashi[1].sem_num=1;			//setting semaphore 2([1]) back to 0
	hashi[1].sem_op=-1;
	hashi[1].sem_flg=0;

if (semop(ID, hashi, 2) == -1) {	//This executes all of the above operations in an atomic set.
	perror("semop");
	exit(EXIT_FAILURE);
}

	sleep(think[0]);			
	count1=count1+eat[0];			//This keeps count of how many seconds we've eaten, and then leaves once we reach 100+
	if(count1>=100){
		printf("Philosopher #1 is full, and leaving. Bye.\n");
		exit(0);
	}
}
	printf("1\n");
	exit(0);
}
//CHILD 2
if((child2=fork())==0){
while(1){
	hashi[0].sem_num=1;
	hashi[0].sem_op=0;
	hashi[0].sem_flg=0;
	
	hashi[1].sem_num=2;
	hashi[1].sem_op=0;
	hashi[1].sem_flg=0;

	hashi[2].sem_num=1;
	hashi[2].sem_op=1;
	hashi[2].sem_flg=0;

	hashi[3].sem_num=2;
	hashi[3].sem_op=1;
	hashi[3].sem_flg=0;
	
if (semop(ID, hashi, 4) == -1) {
	perror("semop");
	exit(EXIT_FAILURE);
}
	eat[1]=randomGaussian(9,3);
	think[1]=randomGaussian(11,7);
	if(eat[1]<0) eat[1]=0;
	if(think[1]<0) think[1]=0;
	printf("Philosopher #2 is eating for %d seconds.\n",eat[1]);
	sleep(eat[1]);
	printf("Philosopher #2 is done eating, thinking for %d seconds.\n", think[1]);
	hashi[0].sem_num=1;
	hashi[0].sem_op=-1;
	hashi[0].sem_flg=0;
	
	hashi[1].sem_num=2;
	hashi[1].sem_op=-1;
	hashi[1].sem_flg=0;
if (semop(ID, hashi, 2) == -1) {
	perror("semop");
	exit(EXIT_FAILURE);
}
	sleep(think[1]);
	count2=count2+eat[1];
	if(count2>=100){
		printf("Philosopher #2 is full, and leaving. Bye.\n");
		exit(0);
	}
}
	printf("2\n");
	exit(0);
}
if((child3=fork())==0){
while(1){
	hashi[0].sem_num=2;
	hashi[0].sem_op=0;
	hashi[0].sem_flg=0;
	
	hashi[1].sem_num=3;
	hashi[1].sem_op=0;
	hashi[1].sem_flg=0;

	hashi[2].sem_num=2;
	hashi[2].sem_op=1;
	hashi[2].sem_flg=0;

	hashi[3].sem_num=3;
	hashi[3].sem_op=1;
	hashi[3].sem_flg=0;
	
if (semop(ID, hashi, 4) == -1) {
	perror("semop");
	exit(EXIT_FAILURE);
}
	eat[2]=randomGaussian(9,3);
	think[2]=randomGaussian(11,7);
	if(eat[2]<0) eat[2]=0;
	if(think[2]<0) think[2]=0;
	printf("Philosopher #3 is eating for %d seconds.\n",eat[2]);
	sleep(eat[2]);
	printf("Philosopher #3 is done eating, thinking for %d seconds.\n", think[2]);
	hashi[0].sem_num=2;
	hashi[0].sem_op=-1;
	hashi[0].sem_flg=0;
	
	hashi[1].sem_num=3;
	hashi[1].sem_op=-1;
	hashi[1].sem_flg=0;
if (semop(ID, hashi, 2) == -1) {
	perror("semop");
	exit(EXIT_FAILURE);
}
	sleep(think[2]);
	count3=count3+eat[2];
	if(count3>=100){
		printf("Philosopher #3 is full, and leaving. Bye.\n");
		exit(0);
	}
}
	printf("3\n");
	exit(0);
}
if((child4=fork())==0){
while(1){
	hashi[0].sem_num=3;
	hashi[0].sem_op=0;
	hashi[0].sem_flg=0;
	
	hashi[1].sem_num=4;
	hashi[1].sem_op=0;
	hashi[1].sem_flg=0;

	hashi[2].sem_num=3;
	hashi[2].sem_op=1;
	hashi[2].sem_flg=0;

	hashi[3].sem_num=4;
	hashi[3].sem_op=1;
	hashi[3].sem_flg=0;
	
if (semop(ID, hashi, 4) == -1) {
	perror("semop");
	exit(EXIT_FAILURE);
}
	eat[3]=randomGaussian(9,3);
	think[3]=randomGaussian(11,7);
	if(eat[3]<0) eat[3]=0;
	if(think[3]<0) think[3]=0;
	printf("Philosopher #4 is eating for %d seconds.\n",eat[3]);
	sleep(eat[3]);
	printf("Philosopher #4 is done eating, thinking for %d seconds.\n", think[3]);
	hashi[0].sem_num=3;
	hashi[0].sem_op=-1;
	hashi[0].sem_flg=0;
	
	hashi[1].sem_num=4;
	hashi[1].sem_op=-1;
	hashi[1].sem_flg=0;
if (semop(ID, hashi, 2) == -1) {
	perror("semop");
	exit(EXIT_FAILURE);
}
	sleep(think[3]);
	count4=count4+eat[3];
	if(count4>=100){
		printf("Philosopher #4 is full, and leaving. Bye.\n");
		exit(0);
	}
}
	printf("4\n");
	exit(0);
}
if((child5=fork())==0){
while(1){
	hashi[0].sem_num=4;
	hashi[0].sem_op=0;
	hashi[0].sem_flg=0;
	
	hashi[1].sem_num=0;
	hashi[1].sem_op=0;
	hashi[1].sem_flg=0;

	hashi[2].sem_num=4;
	hashi[2].sem_op=1;
	hashi[2].sem_flg=0;

	hashi[3].sem_num=0;
	hashi[3].sem_op=1;
	hashi[3].sem_flg=0;
	
if (semop(ID, hashi, 4) == -1) {
	perror("semop");
	exit(EXIT_FAILURE);
}
	eat[4]=randomGaussian(9,3);
	think[4]=randomGaussian(11,7);
	if(eat[4]<0) eat[4]=0;
	if(think[4]<0) think[4]=0;
	printf("Philosopher #5 is eating for %d seconds.\n",eat[4]);
	sleep(eat[4]);
	printf("Philosopher #5 is done eating, thinking for %d seconds.\n", think[4]);
	hashi[0].sem_num=4;
	hashi[0].sem_op=-1;
	hashi[0].sem_flg=0;
	
	hashi[1].sem_num=0;
	hashi[1].sem_op=-1;
	hashi[1].sem_flg=0;
if (semop(ID, hashi, 2) == -1) {
	perror("semop");
	exit(EXIT_FAILURE);
}
	sleep(think[4]);
	count5=count5+eat[4];
	if(count5>=100){
		printf("Philosopher #5 is full, and leaving. Bye.\n");
		exit(0);
	}
}
	printf("5\n");
	exit(0);
}
wait(&child1);
wait(&child2);
wait(&child3);
wait(&child4);
wait(&child5);
for(int i=0;i<5;i++)
	semctl(ID, i, IPC_RMID);
printf("All Done, Bye!\n");
exit(0);
}
