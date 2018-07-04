//Michael Allen-Bond
//CS 360
//Dr. Lang
//Assignment 2
/* To compile this file, just type make.
To run it, type ./ok <word>.
Thank you.
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int ok(int fd,char *word){
char have[16];              //before entering this function, <16 strlen is asserted.
char want[16];
int i=0;

while (i<strlen(word)){
    want[i]=word[i];        //this copies each character from the word
    i++;
}

while(i<15){
    want[i]=' ';            //this fills the rest with blanks
    i++;
}

want[i]='\0';               //this puts a null terminator on the end. not really useful for this exercise, but I did it anyways.

int limit=15;
int compare;
long bot,top;               
bot=0;
top=lseek(fd, 1, SEEK_END);
long mid=(bot+top)/2;
mid=mid-mid%16;

while(top>mid){
    lseek (fd, mid-mid%16, SEEK_SET);   //this makes sure that wherever mid is, we'll start at the beginning of a line.
    read(fd,have,limit);
    compare=strcmp(want,have);          //The rest is just compare done exactly as described in assignment.
    if(compare==0){
        return 1;}
    else if (compare<0)
        top=mid;
    else
        bot=mid+1;
    mid=(bot+top)/2;
}
return 0;
}

int main (int argc, char *argv []) {
int fd;
char *fname="/encs_share/cs/class/cs360/lib/webster";     //Dictionary directory here, should work by default if you're running this on the school server
int OK;
fd = open (fname, O_RDONLY, 0);
                                       
if (argc!=2){                   //This error is for no argument.
    fprintf(stderr,"%s: accepts program name, followed by single word argument. -- %s\n",argv[0],strerror(EINVAL));
    exit(1);
}

if (fd<0){                      //This error is for no file.
    fprintf(stderr,"%s: can't open %s for reading -- %s\n", argv[0],fname,strerror(2));
    exit(1);
}
                                //This error is for overly long string
if(strlen(argv[1])>=16){
    fprintf(stderr,"Argument string is too long.\n");
    exit(1);
}
OK=ok(fd,argv[1]);

if(OK==1){
    write(1,"yes\n",4);
}
else{
    write(1,"no\n",3);
}
}


