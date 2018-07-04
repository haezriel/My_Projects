#include <stdio.h>
#include <string.h>
main()
{
  char s1[32],s2[32];
  char *temp;

  strcpy(s1,"Hello");
  strcpy(s2,"Bye");

  temp=s1;
  //strcpy(temp,s1);
  printf("temp=%s\n",temp);
  strcpy(temp,"Ooops");
  printf("now s1=%s\n",s1);
}
ls
