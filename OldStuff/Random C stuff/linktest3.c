#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// simple linked-list example - njm

struct node{
  int data;
  struct node *next;
};

main()
{
  struct node *myList,*newNode;
  char buffer[120]; // temporary storage
  int num; // this is the number we're going to add to the list

  myList=NULL; // this shows that we don't have any nodes yet...

  while (NULL != fgets(buffer,120,stdin)){ // read a line with a number
    sscanf(buffer,"%d",&num); //convert to an integer

// make a new node
    newNode=malloc(sizeof(struct node)); // store things in here
    newNode->data=num; // save the number in the data piece
    newNode->next=myList; // point to the start of the old list
    myList=newNode; // and make this node the first node

// node is added: print out the list now
    print(myList);
  }
}

// print an entire list
print(struct node *p)
{
  while (p != NULL){
    printf("%d ",p->data);
    p=p->next; // move down the list
  }
  printf("\n\n");
}
