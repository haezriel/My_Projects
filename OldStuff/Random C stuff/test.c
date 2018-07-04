#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>

int main(){
int *num;
void *bob;

num=1;
bob=num;
printf("%d", bob);
}

