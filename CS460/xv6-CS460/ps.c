#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "uproc.h"

#define MAX 50

int main(int argc, char *argv[]){
 struct uproc table[MAX];
getprocs(MAX,table);

static char *states[] = {
  [0]    "unused",
  [1]    "embryo",
  [2]  "sleep ",
  [3]  "runble",
  [4]   "run   ",
  [5]    "zombie"
  };
printf(2,"|PID|PPID|  STATE   |  SIZE | NAME \n");
 int i=0;
 for(;i<MAX;i++){
 	if(table[i].name[0]!=0)
 		printf(2,"| %d | %d  |  %s  | %d | %s \n",table[i].pid,table[i].ppid,states[table[i].state],table[i].sz,table[i].name);
 }
 exit();


}