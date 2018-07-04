#include "sort.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <math.h>

#define SORT_THRESHOLD      40

static void *quickSort(void* p);

typedef struct _sortParams {
    char** array;
    int left;
    int right;
} SortParams;
static int maximumThreads = 10;
SortParams **Queue=NULL;
int front=0;
int End=0;
int Max=0;
int Done=0;
int Key=0;
int *TC;
pthread_mutex_t mutex;


            /* maximum # of threads to be used */

/* This is an implementation of insert sort, which although it is */
/* n-squared, is faster at sorting short lists than quick sort,   */
/* due to its lack of recursive procedure call overhead.          */


void *work(){
pthread_mutex_lock(&mutex);
int x=Key++;
pthread_mutex_unlock(&mutex);
while(1){

    SortParams *temp=NULL;

    pthread_mutex_lock(&mutex);

    if(Queue[front]==NULL){
        TC[x]=1;
        pthread_mutex_unlock(&mutex);
    }
    else {
        TC[x]=0;
        temp=Queue[front];

        Queue[front]=NULL;

        front=(front+1)%Max;
        pthread_mutex_unlock(&mutex);
        quickSort(temp);
    } 


}
return NULL;
}

static void insertSort(char** array, int left, int right) {
    int i, j;
    for (i = left + 1; i <= right; i++) {
        char* pivot = array[i];
        j = i - 1;
        while (j >= left && (strcmp(array[j],pivot) > 0)) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = pivot;
    }
}

/* Recursive quick sort, but with a provision to use */
/* insert sort when the range gets small.            */

static void *quickSort(void* p) {
    SortParams* params = (SortParams*) p;
    char** array = params->array;
    int left = params->left;
    int right = params->right;
    int i = left, j = right;
    
    if (j - i > SORT_THRESHOLD) {           /* if the sort range is substantial, use quick sort */
        int m = (i + j) >> 1;               /* pick pivot as median of         */
        char* temp, *pivot;                 /* first, last and middle elements */
        if (strcmp(array[i],array[m]) > 0) {
            temp = array[i]; array[i] = array[m]; array[m] = temp;
        }
        if (strcmp(array[m],array[j]) > 0) {
            temp = array[m]; array[m] = array[j]; array[j] = temp;
            if (strcmp(array[i],array[m]) > 0) {
                temp = array[i]; array[i] = array[m]; array[m] = temp;
            }
        }
        pivot = array[m];

        for (;;) {
            while (strcmp(array[i],pivot) < 0) i++; /* move i down to first element greater than or equal to pivot */
            while (strcmp(array[j],pivot) > 0) j--; /* move j up to first element less than or equal to pivot      */
            if (i < j) {
                char* temp = array[i];      /* if i and j have not passed each other */
                array[i++] = array[j];      /* swap their respective elements and    */
                array[j--] = temp;          /* advance both i and j                  */
            } else if (i == j) {
                i++; j--;
            } else break;                   /* if i > j, this partitioning is done  */
        }
        pthread_mutex_lock(&mutex);
        SortParams *first;
        first=malloc(sizeof(SortParams));
        first->array = array; first->left = left; first->right = j;
        Queue[End]=first;
        End=(End+1)%Max;

        SortParams *second;
        second=malloc(sizeof(SortParams));
        second->array = array; second->left = i; second->right = right;
        Queue[End]=second;
        End=(End+1)%Max;

        pthread_mutex_unlock(&mutex);


    } else insertSort(array,i,j); 
/* for a small range use insert sort */
return NULL;
}

/* user interface routine to set the number of threads sortT is permitted to use */

void setSortThreads(int count) {
    maximumThreads = count;
}

/* user callable sort procedure, sorts array of count strings, beginning at address array */

void sortThreaded(char** array, unsigned int count) {
    Queue=malloc(count*sizeof(SortParams*));
    SortParams *Link;
    Link=malloc(sizeof(SortParams));
    Link->array = array; Link->left = 0; Link->right = count - 1;
    Queue[0]=Link;
    End=1;
    Queue[End]=NULL;
    Max=count;
    TC=malloc(maximumThreads*sizeof(int));
    for(int i=0;i<maximumThreads;i++)
        TC[i]=0;
    pthread_t threads[maximumThreads]; //defaults to 10
    for(int i=0;i<maximumThreads;i++)
        pthread_create(&threads[i], NULL, 
        work, 
        NULL);
    while(Done==0){
        Done=1;
        for(int i =0; i<maximumThreads;i++)
            if (TC[i]==0){ Done=0;}

    }
    for(int i=0;i<maximumThreads;i++)
        pthread_cancel(threads[i]);
    return;
}