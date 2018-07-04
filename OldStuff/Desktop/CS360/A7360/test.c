#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h> 
#include "random.h"

	pthread_t philo;
	pthread_mutex_t sticks;

void *philo1(){
	while(1){
	int i;
	pthread_mutex_lock(&sticks);
	i=pthread_mutex_lock(&sticks);
	printf("%d\n",i);
	pthread_exit(NULL);
	}
}
main(){
	pthread_mutex_init(&sticks, NULL);
	pthread_create(&philo, NULL,philo1, 0);
	pthread_join(philo, NULL);

}