#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include "buffer.h"
#define THREAD_MAX 200


struct counter{
     int count;
     int in;
     int out;
     pthread_mutex_t lock;
}key;


buffer_item buffer[BUFFER_SIZE];
int the_murder_flag;
pthread_t producer_t[THREAD_MAX];
pthread_t consumer_t[THREAD_MAX];

int p,c,s,debug;

int insert_item(buffer_item item) {
     if(pthread_mutex_trylock(&key.lock)==0){
          
          if(key.count<BUFFER_SIZE){
               buffer[key.in]=item;
               int i = key.in;
               key.in=(i+1)%BUFFER_SIZE;
               int n = key.count;
               key.count = n + 1;
               if(debug)
                    printf("Producer produced %d \n",item);
               pthread_mutex_unlock(&key.lock);

               return 0;
          }

          pthread_mutex_unlock(&key.lock);

          return 1;
     }
     return 1;
}


int remove_item(buffer_item *item){

     if(pthread_mutex_trylock(&key.lock)==0){

          if(key.count>0){
               *item=(buffer[key.out]);
               int n = key.count;
               key.count = n-1;
               int i=key.out;
               key.out=(i+1)%BUFFER_SIZE;
               if(debug)
                    printf("Consumer consumed %d \n",*item);
               pthread_mutex_unlock(&key.lock);

               return 0;
          }

          pthread_mutex_unlock(&key.lock);

          return 1;
     }
     return 1;
}

void *producer(void *param) {
     buffer_item item;
     int p=*(int*)param;
     sleep((time_t)(rand()%s));
     while (the_murder_flag) {
          item = rand();
          if (insert_item(item)==0){
               if(!debug)
               printf("Producer #%d produced %d \n",p,item);
               sleep((time_t) s);
          }
     }
     printf("Producer #%d shutting down, good night sweet prince.\n",p);
     pthread_exit(NULL);
}

void *consumer(void *param) {
     int c=*(int*)param;
     buffer_item item;
     sleep((time_t)(rand()%s));
     while (the_murder_flag) {
          if (remove_item(&item)==0){
               if(!debug)
               printf("Consumer #%d consumed %d \n",c,item);
               sleep((time_t) s);
          }
     }
     printf("Consumer #%d shutting down, good night sweet prince.\n",c);
     pthread_exit(NULL);
}
void handler(){
  printf("\nInterrupt Signal Detected, setting kill flag. \n");
  the_murder_flag=0;

}

int main(int argc, char**argv)
{
     srand(time(NULL));
     the_murder_flag=1;
     signal(SIGINT,handler);
     key.in=0;
     key.out=0;
     key.count=0;
     debug=0;
     char d;
     if(argc>4){
     sscanf(argv[4],"%c",&d);
     if(d=='d')
          debug=1;
     }
     if(argc<4){
          printf("Incorrect input parameters.\n");
          printf("Correct Input: <program call> <sleep time> <# of producer threads> <# of consumer threads>\n");
          exit(1);
     }
     sscanf(argv[1],"%d",&s);
     sscanf(argv[2],"%d",&p);
     sscanf(argv[3],"%d",&c);
     if(p>THREAD_MAX){
          printf("Creating over %d producer threads is NOT IDEAL. Try again.\n",THREAD_MAX);
          exit(1);
     }
     if(c>THREAD_MAX){
          printf("Creating over %d consumer threads is NOT IDEAL. Try again.\n",THREAD_MAX);
          exit(1);
     }
     if(s>100000000){
          printf("Seriously? You want a sleep cycle over 3.2 years long? Ok champ.\n");
          exit(1);
     }
     pthread_mutex_init(&key.lock, NULL);
     int pr[p];
     int cr[c];

     for (int i=0;i<p;i++){
          pr[i]=i;

          pthread_create(&producer_t[i], NULL, 
               producer, 
               &pr[i]);
     }
     for (int i=0;i<c;i++){
          cr[i]=i;


          pthread_create(&consumer_t[i], NULL, 
               consumer, 
               &cr[i]);
     }


     for (int i=0;i<p;i++){

          pthread_join(producer_t[i], NULL);

     }

     for (int i=0;i<c;i++){

          pthread_join(consumer_t[i], NULL);

     }

pthread_mutex_destroy(&key.lock);
printf("All threads are closed, exiting.\n");
}

