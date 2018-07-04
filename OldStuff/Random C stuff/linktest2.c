#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *next;
};


main(){
	struct node *list, *header, *new;
	list=malloc(sizeof(struct node));
	insert(list, 7);
	insert(list, 11);
	print(list->next);	
}


insert(struct node *L, int num){
	
	struct node *new;
	new=malloc(sizeof(struct node));
	new->data=num;
	new->next=L->next;
	L->next=new;
	

}

print(struct node *p)
{
while (p != NULL){
    printf("%d ",p->data);
    p=p->next;
  }
  printf("\n");
}

