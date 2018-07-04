#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct node{
        int data;
        struct node *next;
        struct node *prev;
};


main(){
        int i;
	struct node *list, *node1, *node2;
        list=NULL;

	node1=malloc(sizeof(struct node));
	node2=malloc(sizeof(struct node));
	node1->next=list;
	node1->prev=node2;
	node1->data=7;
	node2->next=node1;
	node2->prev=NULL;
	node2->data=11;
	list=node2;
	print(list);
       }

print(struct node *p)
{
while (p != NULL){
    printf("%d ",p->data);
    p=p->next;
  }
  printf("\n");
}

