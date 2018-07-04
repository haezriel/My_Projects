/*Michael Allen-Bond
Programming Assignment 1
CS 360
Dr. Lang
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <getWord.h>
#include "hash.h"


Table *hash(int N){
	Table *Hashtable;								
	Hashtable=malloc(sizeof(Table));
   	Hashtable->size=N;
	Hashtable->array=malloc (N*sizeof(Node));		//allocates array of pointers to node structs.
	for(int i;i<Hashtable->size;i++)				//This loop just initializes all the nodes to NULL
		Hashtable->array[i].next=NULL;
	return Hashtable;
}

/*______________________________________________________________________*/

Table *hashadd(char *wordpair, Table *Hashtable){
	if((Hashtable->count)>(Hashtable->size*2))		//If wordpairs count doubles hashtable size,
		Hashtable=hashexpand(Hashtable);			//expands hashtable.
	
	unsigned long long hashkey;
	hashkey=(crc64(wordpair))%Hashtable->size;
	
	if(hashsearch(wordpair, hashkey, Hashtable)==0)		//searches for wordpair in hash, if found,
		return Hashtable;								//modifies value and returns hash.
	
	/*If all the above conditions are passed,
	then a new node is cast, malloced, and placed in the hashtable.*/	
	Node *addnode;									
	addnode=malloc(sizeof(Node));
	addnode->value=malloc(sizeof(void *));
	addnode->next=NULL;	
	*(int*)addnode->value=1;
	addnode->key=wordpair;
	addnode->next=Hashtable->array[hashkey].next;
	Hashtable->array[hashkey].next=addnode;
	Hashtable->count++;
	return Hashtable;
}

/*______________________________________________________________________*/

Table *hashexpand(Table *Hashtable){
	Table *Hashtable2=hash((Hashtable->size)*3);	//creates a hashtable 3 times larger than previous.
	Node *Sentinel;									//The Sentinel node traverses the hashtable,
	Node *Carry;									//while the Carry node actually holds and transfers nodes.
	Hashtable2->count=0;							//resets count to zero for node reallocation.
	unsigned long long hashkey;						
	Sentinel=malloc(sizeof(Node));	
	Carry=malloc(sizeof(Node));

	//This loop traverses the hashtable array
	for(int i=0; i<(Hashtable->size); i++){
		Sentinel->next=Hashtable->array[i].next;
		
		//And this loop traverses each linked list of nodes in the array.
		while(Sentinel->next!=NULL){
			Carry=Sentinel->next;
			Sentinel->next=Sentinel->next->next;
			hashkey=(crc64(Carry->key))%(Hashtable2->size);
			Carry->next=Hashtable2->array[hashkey].next;
			Hashtable2->array[hashkey].next=Carry;
			Hashtable2->count++;
		} //end of while loop
	}//end of for loop

	//No new nodes are made, the existing ones are simply re-assigned and linked in the new hashtable.
	//therefore, the only things to be freed are the Table itself, and the Sentinel and Carry nodes.
	Sentinel->next=NULL;	
	Carry=NULL;
	free(Sentinel);
	free(Carry);
	free(Hashtable);

	return Hashtable2;
	
}

/*______________________________________________________________________*/

int hashsearch(char *wordpair, unsigned long long hashkey, Table *Hashtable){
	Node *search;											//Allocates search node to traverse hash table
	search= malloc(sizeof(Node));			
	search->next=Hashtable->array[hashkey].next;			//since we have the key, we can immediately access the 		
															//appropriate bucket list.
	
	/*loop traversing to end of list, if match is found,
	iterates value, and returns, otherwise, returns false.*/
	while (search->next!=NULL){								
		if (strcmp(search->next->key,wordpair)==0){
			*(int*)search->next->value=*(int*)search->next->value+1;		
			return 0;		
		}		
		else	
			search->next=search->next->next;
	}
	free (search);								//After search is finished, the node is freed.
	
	return 1;	

}

/*______________________________________________________________________*/

void output(Table *Hashtable,int limit){
	Node Output[Hashtable->count];			//This makes a static array of nodes the size of the wordpair count,
	int k=0;								//which is the largest possible size necessary, assuming no collisions
	Node *Sentinel;							//in the hash table.
	Sentinel=malloc(sizeof(Node));			//Sentinel node is used the same way as before, to traverse the hash.
	
	//Loop for traversing hashtable array.
	for(int i=0;i<(Hashtable->size);i++){
		Sentinel->next=Hashtable->array[i].next;
		
		//Loop for traversing nodes and assigning values to the output array.		
		while(Sentinel->next!=NULL){
			Output[k].key=Sentinel->next->key;
			Output[k].value=Sentinel->next->value;
			Sentinel->next=Sentinel->next->next;
			k++;
		}//End of while loop.
	}//End of for loop.

	printf("______________________________________________________\n");
	
	//qsort does NOT like pointers to structs. That's all I have to say about that.	
	qsort(Output,k,(sizeof(Node)),(compfn)comparevalues);
	
	//This ensures that the print limit won't be negative, or go off the end of the array.	
	if(limit>0&&limit<k) k=limit;
	for(int i=0;i<k;i++){
		printf("%10d %s\n", *(int*)Output[i].value, Output[i].key);
	}
	printf("%d total wordpairs.\n",Hashtable->count);
	free(Sentinel);							//Freeing node memory.
	return;
}

/*______________________________________________________________________*/

void freehash(Table *Hashtable){
	Node *Sentinel;					
	Sentinel=malloc(sizeof(Node));	
	
	/*This loops through the entire hashtable array, and as Sentinel traverses the nodes,
	The hash frees them, and then is handed the next node by Sentinel.*/
	for(int i=0;i<Hashtable->size;i++){
		Sentinel->next=Hashtable->array[i].next;
		while(Hashtable->array[i].next!=NULL){
			Sentinel->next=Sentinel->next->next;
			Hashtable->array[i].next=NULL;
			free(Hashtable->array[i].next);
			Hashtable->array[i].next=Sentinel->next;
			}
	}
	Sentinel=NULL;
	free(Sentinel);
	//After all the nodes are freed, we free the Hashtable.
		
	free(Hashtable);
}

/*______________________________________________________________________*/

//This is the compare function for qsort.
int comparevalues(Node *a, Node *b){
	return *(int*)b->value-*(int*)a->value;	
}

/*______________________________________________________________________*/

#define CRC64_REV_POLY      0x95AC9329AC4BC9B5ULL
#define CRC64_INITIALIZER   0xFFFFFFFFFFFFFFFFULL
#define CRC64_TABLE_SIZE    256

unsigned long long crc64(char* string) {
    static int initFlag = 0;
    static unsigned long long table[CRC64_TABLE_SIZE];
    
    if (!initFlag) { initFlag++;
        for (int i = 0; i < CRC64_TABLE_SIZE; i++) {
            unsigned long long part = i;
            for (int j = 0; j < 8; j++) {
                if (part & 1)
                    part = (part >> 1) ^ CRC64_REV_POLY;
                else part >>= 1;
            }
            table[i] = part;
        }
    }
    
    unsigned long long crc = CRC64_INITIALIZER;
    while (*string)
        crc = table[(crc ^ *string++) & 0xff] ^ (crc >> 8);
    return crc;
}

