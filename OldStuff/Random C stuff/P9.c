
//Michael Allen-Bond
//CSE 222
//03/07/2014
//Programming Assignment 9
//This program accepts 2 integer arguments (<128), reads an adjacency matrix out of adj.data,
//and then finds the shortest path (# of hops) from node1 to node2 (int arg1 to int arg2).
//To use, type "make" and then "./p9 <integer> <integer>"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#define MAX 128

//Using structs for my adj. matrix and my queue. The matrix struct holds the node connection flags,
//as well as the visited flags. The queue struct holds the node, as well as the hops required to reach it.

struct matrix{
	int flag;
	int node[MAX];
};

struct queue{
	int node;
	int hop;
}

//Main block. matrix declared, queue declared, int node1 and node2 hold argv1 and argv2, respectively.
//i and j hold the two components of the matrix entry, f is a counter, and y holds the sscanf value (helps with error checking).
//count holds the integer returned from hops function call. nope[32] holds input for error checking adj.data,
//buffer holds input from fgets, and *list is the file pointer for input.

main(int argc, char **argv){
struct matrix *matrix;
int node1,node2;
struct queue *queue;
int i,j,f,y,count;
char nope[32],buffer[1000];
FILE *list;

//Allocating memory to queue and matrix, could also be done dynamically to save space.
//Initializing matrix to 0.

queue=malloc(MAX*sizeof(struct queue));
matrix=malloc(MAX*sizeof(struct matrix));
f=0;

for(i=0;i<MAX;i++){
	matrix[i].flag=0;
	for(j=0;j<MAX;j++)
		matrix[i].node[j]=0;
}

//Checks for 3 args.

if(argc!=3){
        printf("Please type ./P9 <integer> <integer>.\n");
        exit(0);
}

//Checks for integer entries for argv1 and argv2.

if(1!=sscanf(argv[1],"%d",&node1)){
	printf("Must be an integer entry.\n");
	exit(0);
}
if(1!=sscanf(argv[2],"%d",&node2)){
        printf("Must be integer entry.\n");
        exit(0);
}

//Checks for integer entries over the MAX.

if(node1>MAX-1||node2>MAX-1){
	printf("Integer entries must be less than %d.\n",MAX);
	exit(0);
}

//Assigns *list to file, if there's no file, exits.

list=fopen("adj.data", "r");

if(list<=0){
        printf("There's nothing in your adjacency list.\n");
        exit(0);
}

printf("\nReading list.\n");

//while file is not empty, reads into buffer, scans for 2 integers per line (and error, if present),
//if integers are under MAX, stores them appropriately in the adjacency matrix.
//increments f counter. If format is incorrect, prints error and exits, and if array is full,
//prints error and exits.  If adj.data exists but is empty and f==0 (no entries read),
//prints error and exits.

while(NULL!=fgets(buffer,1000,list)){
	if(2==(y=sscanf(buffer,"%d %d %s\n", &i, &j, nope))){
        	if(i>MAX-1||j>MAX-1){
			printf("Integer is too large to insert into matrix.\n");
			exit(0);
		}
		matrix[i].node[j]=1;
		f++;
	}
        else{
                printf("Bad data in list.\n");
                exit(0);
        }
        if(f>MAX-1){
                printf("List has too many items.\n");
                exit(0);
        }
}
if(f==0){
	printf("List is empty.\n");
	exit(0);
}

//Call hops function, return int to count, prints out nodes and # of hops.

count=hops(node1,node2,queue,matrix);

if(count!=-1) printf("%d reaches %d in %d hops.\n",node1,node2,count);

else printf("No path could be found from %d to %d.\n",node1,node2);
free(matrix);
free(queue);

}

//hops function, calculates number of hops to get from node1 to node2. Takes in node1, node2, queue, and matrix.
//adds node1 to queue, starts while loop for reading out of queue, sets head.node to s, head.hop to h.
//if s==node2, returns hops, otherwise puts all attached nodes into queue, flags them as 1, and repeats.
//if there are no more nodes in the queue, returns -1 (cannot be reached).

int hops(int node1, int node2,struct queue *queue, struct matrix *matrix){
int i,h,s,head,tail;
head=tail=h=0;

tail=add(queue,tail,node1,h);
while(queue!=NULL&&head!=tail){
	s=queue[head].node;
	h=queue[head].hop;
	head=rem(queue,head,s);
	if (s==node2) return h;
	else{
		for(i=0;i<MAX;i++){
			if(matrix[s].node[i]==1&&matrix[i].flag!=1){
				matrix[i].flag=1;
				tail=add(queue,tail,i,h+1);
			}
		}
	}
}
return -1;
}

//Add function, adds num and h to queue, increments tail.

int add(struct queue *queue,int tail, int num,int h){
        queue[tail].node=num;
	queue[tail].hop=h;
	tail=(tail+1)%MAX;
return tail;
}

//Rem function, removes num, increments head.

int rem(struct queue *queue, int head, int num){
        head=(head+1)%MAX;
return head;
}//potato
