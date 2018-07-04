#include <stdio.h>
#include <string.h>
main()
{
  char s[512][32],temp[32];
  int i;

  for (i=0;i<5;i++){
    gets(s[i]);
  }

// now look for "hello"

  for (i=0;i<5;i++){
    printf("strcmp gives %d\n",strcmp(s[i],s[0]));
  }
}
ls

