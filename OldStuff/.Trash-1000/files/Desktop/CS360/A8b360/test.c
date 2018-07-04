#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sort.h"



int main(){
    clock_t start,end;
    double total;
    char *states[900000];
    char buffer[100];
    char buf[100];
    FILE *fp;
    int i=0;
    fp = fopen("bible.txt","r");
    while (NULL!=fgets(buffer, 100, fp) && i<900000){
        sscanf(buffer,"%s",buf);
        states[i]=malloc(sizeof(buf));
        strcpy(states[i],buf);
        i++;
    }
    int max=i;
    i=0;
    setSortThreads(5);
    start=clock();
    sortThreaded(states, max);
    end=clock();
    while (i<max){
    	printf ("%s\n", states[i]);
    	i++;
    }
    total= (end-start);
    printf("%lf\n", total);

}