/***
 *** Really good comments for this program
 *** NJM
 ***/
#include <stdio.h>
main(argc,argv)
int argc;
char **argv;
{
  int i;
  printf("argc=%d\n",argc);
  for (i=0;i<argc;i++){
    printf("argv[%d]=\"%s\"\n",i,argv[i]);
  }
}

