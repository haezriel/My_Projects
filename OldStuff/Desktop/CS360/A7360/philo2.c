//Michael Allen-Bond
//CS 360
//Dr. Lang
//Assignment 7
//To compile, type "make". to run, type ./philo2. Be warned, this thing runs for at least 500 seconds before finishing, unless you interrupt it.

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h> 
#include "random_r.h"


	pthread_t philo[5];
	pthread_mutex_t sticks[5];
	unsigned int state[5];
	int eat[5];
	int think[5];
	int count[5];

void *philos(void *n){
	state[*(int *)n]=*(int *)n;
	while(1){
		int i= *(int *)n;
		int left,right;
		right=i+1;
		if(right>4) right=0;
		left=i;
		pthread_mutex_lock(&sticks[left]);
		if(pthread_mutex_trylock(&sticks[right])==0){
			eat[i]=randomGaussian_r(9,3, state);		
			think[i]=randomGaussian_r(11,7, state);

			if(eat[i]<0) eat[i]=0;			
			if(think[i]<0) think[i]=0;		
			printf("Philosopher #%d is eating for %d seconds.\n",i+1,eat[i]);
			sleep(eat[i]);
			printf("Philosopher #%d is done eating, thinking for %d seconds.\n",i+1, think[i]);
			pthread_mutex_unlock(&sticks[left]);
			pthread_mutex_unlock(&sticks[right]);
			sleep(think[i]);			
			count[i]=count[i]+eat[i];
			if(count[i]>=100){
				printf("Philosopher #%d is full, and leaving. Bye.\n",i+1);
				pthread_exit(NULL);
			}
		}
		else
			pthread_mutex_unlock(&sticks[left]);

	}
}

int main(){

	int i;
	int p[5];
	for (i=0;i<5;i++){
		p[i]=i;
		pthread_mutex_init(&sticks[i], NULL);
		pthread_create(&philo[i], NULL, 
			philos, 
			&p[i]);
	}




pthread_join(philo[0], NULL);
pthread_join(philo[1], NULL);
pthread_join(philo[2], NULL);
pthread_join(philo[3], NULL);
pthread_join(philo[4], NULL);
printf("All Done, Bye!\n");
exit(0);
}
