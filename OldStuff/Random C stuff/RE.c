#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

//This program has 5 functions, reads in from stdin (easily switched to file IO), and rapes my soul.
// gcc -g -Wall -o RE RE.c -lm to compile, yeah I know it doesn't need the math library.


//Parent Struct
struct FA{
	int start;
	int final;
	struct NFA *next;
};

//Node Struct
struct NFA{
	int state;
	int state2;
	char letter;
	struct NFA *next;
};

//Operator functions
int print(struct FA *list, struct NFA *sentinel, int count);
int join(struct FA *list, struct NFA *sentinel,int top, int count);
int make(struct FA *list, char c,int top, int count);
int or(struct FA *list, struct NFA *sentinel, int top, int count);
int kleene(struct FA *list, struct NFA *sentinel, int top, int count);

//Main block

int main(void){
FILE *key;
char regexp[1024];
char buffer[1024];
struct NFA *sentinel;
struct NFA *cleaner;
char c;

int top,count,i,j;
j=0;
struct FA *list; //Declare a array of pointer to structures  
		//allocate memory for each element in the array
cleaner=malloc(sizeof(struct NFA));
sentinel=malloc(sizeof(struct NFA));
list=malloc(10*sizeof(struct FA)); 		//10 isn't necessary but I did it anyways.

key=fopen("postfix.txt", "r");

while(NULL!=fgets(buffer,1024,key)){
	j++;
	top=count=i=0;
	sscanf(buffer,"%s",regexp);
	
	while (regexp[i]!='\n') { 
		c = regexp[i];
		i++;
		if (c=='a'||c=='b'||c=='c'||c=='d'||c=='e'||c=='E'){
			if(top<0){
                                printf("Input Error in one of the postfix strings.\n");
                                exit(0);
                        }

			make(list, c, top, count);
			top++;
			count=count+2;						//input parsing
		}
		else if (c=='&'){
			if(top-2<0){
				printf("Input Error in one of the postfix strings.\n");
				exit(0);	
			}
			join(list,sentinel,top,count);
			top--;
		}
		else if (c=='+'){
                        if(top-2<0){
                                printf("Input Error in one of the postfix strings.\n");
                                exit(0);
                        }
			or(list,sentinel,top,count);
			top--;
		}
		else if (c=='*'){
                        if(top-1<0){
                                printf("Input Error in one of the postfix strings.\n");
                                exit(0);
                        }
			kleene(list,sentinel,top,count);
			count++;
		}
	}
	printf("RE #%d\n",j);
	print(list, sentinel, count);
}	
for(i=0;i<10;i++){
	sentinel->next=list[i].next;
	while(sentinel->next!=NULL){
		cleaner->next=sentinel->next;
		sentinel->next=sentinel->next->next;
		free(cleaner->next);
	}

list[i].next=NULL;
}
sentinel->next=NULL;
free (cleaner);
free (sentinel);
free (list);

return 0;
}

//letter input function


int make(struct FA *list,char c,int top,int count){

struct NFA *NFA;
NFA=malloc(sizeof(struct NFA));

list[top].next=NFA;

list[top].start=NFA->state=count;					//count tracks my # of states
list[top].final=NFA->state2=count+1;

NFA->letter=c;
NFA->next=NULL;

return 0;
}

//Concatenate function

int join(struct FA *list, struct NFA *sentinel,int top, int count){

struct NFA *NFA;
NFA=malloc(sizeof(struct NFA));

sentinel->next=list[top-2].next;					
while(sentinel->next->next!=NULL){
	sentinel->next=sentinel->next->next;
}

sentinel->next->next=list[top-1].next;

NFA->letter='E';
NFA->next=NULL;
NFA->state=list[top-2].final;
NFA->state2=list[top-1].start;
list[top-2].final=list[top-1].final;
while(sentinel->next->next!=NULL){
	sentinel->next=sentinel->next->next;
}
	sentinel->next->next=NFA;

	return 0;
}


//Or function


int or(struct FA *list, struct NFA *sentinel, int top, int count){

struct NFA *NFA1;
struct NFA *NFA2;

NFA1=malloc(sizeof(struct NFA));
NFA2=malloc(sizeof(struct NFA));

sentinel->next=list[top-2].next;

while(sentinel->next->next!=NULL){
	sentinel->next=sentinel->next->next;
}

sentinel->next=sentinel->next->next=list[top-1].next;

while(sentinel->next->next!=NULL){
	sentinel->next=sentinel->next->next;
}

sentinel->next->next=NFA1;
NFA1->next=NFA2;
NFA2->next=NULL;
NFA1->letter='E';
NFA2->letter='E';
NFA1->state=list[top-2].start;
NFA1->state2=list[top-1].start;
NFA2->state=list[top-1].final;
NFA2->state2=list[top-2].final;
return 0;
}

//Kleene star function

int kleene(struct FA *list, struct NFA *sentinel, int top, int count){

struct NFA *NFA1;
struct NFA *NFA2;
struct NFA *NFA3;

NFA1=malloc(sizeof(struct NFA));
NFA2=malloc(sizeof(struct NFA));
NFA3=malloc(sizeof(struct NFA));

sentinel->next=list[top-1].next;

while(sentinel->next->next!=NULL){
        sentinel->next=sentinel->next->next;
}

sentinel->next->next=NFA1;
NFA1->next=NFA2;
NFA2->next=NFA3;
NFA3->next=NULL;
NFA1->letter='E';
NFA2->letter='E';
NFA3->letter='E';
NFA1->state=list[top-1].final;
NFA1->state2=list[top-1].start;
NFA2->state=list[top-1].final;
NFA2->state2=count;
NFA3->state=list[top-1].start;
NFA3->state2=count;
list[top-1].final=count;

return 0;

}

//Print Function

int print(struct FA *list, struct NFA *sentinel, int count){	
int i,c;
sentinel->next=list[0].next;

int array[count+1][6];

for (i=0;i<=count;i++)
	for(c=0;c<6;c++)
		array[i][c]=-1;

while(sentinel->next!=NULL){
	if (sentinel->next->letter=='a')
		array[sentinel->next->state][0]=(sentinel->next->state2);
	else if (sentinel->next->letter=='b')
		array[sentinel->next->state][1]=(sentinel->next->state2);
	else if (sentinel->next->letter=='c')
		array[sentinel->next->state][2]=(sentinel->next->state2);
	else if (sentinel->next->letter=='d')
		array[sentinel->next->state][3]=(sentinel->next->state2);
	else if (sentinel->next->letter=='e')
		array[sentinel->next->state][4]=(sentinel->next->state2);
	else if (sentinel->next->letter=='E')
		array[sentinel->next->state][5]=(sentinel->next->state2);
	sentinel->next=sentinel->next->next;
}

printf("State|  a  |  b  |  c  |  d  |  e  |  E  |\n");

for(i=0;i<count;i++){
	if(i==list[0].final)
		printf("q%dF  |",i);
	else
		printf("q%d   |",i);
	
	for(c=0;c<6;c++){
		if(array[i][c]>=0)
			printf(" q%d  |",array[i][c]);
		else
			printf("     |");
	}
	
	printf("\n");
}


return 0;
}

