#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	int key;
	struct node *next;
	struct node *prev;
}

main(){

struct node *list, *node;
char buffer[100];
int num;

list=NULL;

while (NULL != fgets(buffer, 100, stdin){
	sscanf(buffer, "%d", &num);
	node = malloc(sizeof(struct node));//store things in here
	node->key=num;//save the number in the x piece
	newnode->next=list;//point to the start of the old list
list=newnode;//and make this node the first node
	
	print(list);
}
}
while(p!=NULL)	
