#include <stdio.h>
#include <stdlib.h>

clear_display()
{
  printf("\033[H\033[2J");fflush(stdout);
}

display(int highlight, int *numbers, int num)
{
  int i;
  for (i=0;i<num;i++){
    if (i==highlight) printf("\033[7m");
    if (i==highlight+1) printf("\033[m");
    printf("%8d\n",numbers[i]);
  }
}

delay(int msec)
{
  char buffer[120];fgets(buffer,120,stdin);
}

myRnd(int *numbers, int num) // randomize an array
{
  int i,temp,i1,i2;
  for (i=0;i<num;i++){
    numbers[i]=i;
  }
// shuffle
  for (i=0;i<1000;i++){
    i2=rand() % 32;
    i1=rand() % 32;
    temp=numbers[i1];
    numbers[i1]=numbers[i2];
    numbers[i2]=temp;
  }
}

int done() // wait for ^D
{
  char buffer[120];
  while (NULL != fgets(buffer,120,stdin));
}
