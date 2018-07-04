//Michael Allen-bond
//01/31/2014
//CSE 222
//Programming Assignment 4
//This program accepts input from a user in various forms to input numbers in a binary tree,
//search the tree, delete from the tree, and print the tree, on command.
//It also prints the depth of the tree, as well as whether the tree is balanced.
//To use this program, simply enter "make", and then ./P4.
//The instructions are displayed from there.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

struct node{
	int data;
	struct node *left;
	struct node *right;
};

//declaring my two functions with returns.  The insert function will only return a new root node when root is NULL,
//Otherwise it will return new right/left nodes within the function, but won't alter the root.

struct node *insert(struct node *root, int num);
struct node *delete(struct node *root, int num);


//Main function.  declaring tree, setting it to null, declaring ints and chars to hold various error triggers
//and values (error holds error switch, letter holds char variables, nope catches trailing strings,
//integer holds int value, switcher takes in case value, i is for loops or small function counters.
main(){
	struct node *tree;
	char buffer[100];
	int integer, error, i;
	char letter, switcher, nope;
	srand(time(NULL));
	tree=NULL;
	printf("\n");
	help();
	printf("\nLet's Begin!\n");
	printf("\n>");
	
//This part is identical to P2, not much needed to be changed as far as how input is handled.
 	
	while (NULL != fgets(buffer, 100, stdin)){
		if (1==sscanf(buffer, "%d %s", &integer, &letter))
			switcher='i';
		else{
			error=sscanf(buffer,"%c %d %s", &letter, &integer, &nope);
			switcher=letter;
			if(switcher=='i'){
				printf("Dohoho, I see what you did there..\n");
				switcher='b';
			}
		}

		
		switch(switcher){
	
		
//Switch cases: d <int>, Q, s <int>, <int>, p, ?

		case 'Q':
			printf("You are now exiting the program. If you have any feedback, please don't give any feedback.\n");
			exit(0);

//checks error, calls search, if found, calls delete.		

		case 'd':
			if (error!=2){
				angsty();
				for(i=0;i<10;i++)
					printf("\n");
				help();
				break;
			}
			if(1==search(tree, integer)){
				tree=delete(tree, integer);
				printf("Deleted %d", integer);
			}
			else
				printf("%d cannot be deleted, because it is a figment of your imagination.", integer);
			break;


//Search case, activates error if input isn't correct, otherwise calls search function.

		case 's':
			if (error!=2){
				angsty();
				for (i=0;i<10;i++)
					printf("\n");
				help();
				break;
                        }
                        if (1==search(tree, integer))
				printf("Found your number, %d.\n",integer);
			else
                                printf("%d is gone on business, would you like to leave a message?", integer);
                        break;

//Calls search, if not found, calls insert.

		case 'i':
			if (0==search(tree, integer)){
				tree=insert(tree, integer);
				printf("Number %d has been inserted. If you would like to see the list, enter 'p'.\n", integer);
				break;
			}
			else
				printf("%d has already acquainted himself with the tree, and is no longer welcome at the buffet table.\n",integer);
			break;

//Calls traverse function, prints depth (i), calls balanced function, prints appropriate message.
	
		case 'p':
			if (error!=1){
				angsty();
				for(i=0;i<10;i++)
					printf("\n");
				help();
				break;
			}
			i=traverse(tree);
			printf("\nMax Depth= %d.",i);	
			i=balanced(tree);
			if(i==1)
				printf("\nYour tree is balanced.");
			else
				printf("\nYour tree is not balanced.");
			break;

//Calls Help

		case '?':
			help();
			break;

//Default, also contains error loop.

		default:
			angsty();
			for (i=0;i<10;i++)
				printf("\n");
			help();
			break;
		
		}	

//Resets switcher and letter input, for input error-checking.

		letter='b';
		switcher='b';
		printf("\n>");
	}
}

//Insert function. Takes in root and num, if null makes a node, if not, calls function again with a return to left,
//if num is smaller than current data, or right, if num is larger than current data (equal won't happen), as search
//is called before insert, and insert won't call if search returns 1.

struct node *insert(struct node *root, int num){
        
        if (root==NULL){
		root=malloc(sizeof(struct node));
		root->data=num;
		root->left=root->right=NULL;
		return (root);	
		}
	if (root->data>num){
		root->left=insert(root->left,num);
		return (root);
	}
	else{
		root->right=insert(root->right,num);
		return (root);
	}
}

//Delete function. Takes in root, traverses until num matches root->data, checks for various node cases (none, 1, or 2),
//and operates accordingly:  If one node, sets del to root->left-OR-right, frees root, returns del. if 2 nodes,
//replaces root with leftmost node in right subtree, and then deletes that node. if no nodes, just frees the root,
//and returns NULL.

struct node *delete(struct node *root, int num){
	struct node *del;
	if(root==NULL)	
		return(NULL);
	else if(num<root->data)
		root->left=delete(root->left,num);
	else if(num>root->data)
		root->right=delete(root->right,num);
	else{
		if(root->left==NULL && root->right==NULL){
			free(root);
			return(NULL);
		}
		else if(root->left!=NULL && root->right==NULL){
			del=root->left;
			free(root);
			return(del);
		}
		else if(root->left==NULL && root->right!=NULL){
			del=root->right;
			free(root);
			return(del);
		}
		else{
			del=root;
			del=del->right;
			while(del->left!=NULL)
				del=del->left;
			root->data=del->data;
			root->right=delete(del,del->data);
		}
	}
return(root);
}


//Search function.  Takes in root and num, checks for NULL and for match on every call, and searches all the nodes,
//returning 1 if a match is found anywhere.

int search (struct node *root, int num){
	if(root==NULL) return 0;
	
	if(root->data==num) return 1;
	
	if(search(root->left,num)==1 || search(root->right,num)==1)
		return 1;
	
	return 0;
}	


//Traverse function.  Takes in root node, creates 2 ints, initializes them to 1.  Every time the function is called,
//a new instance of num and num2 are made, and set to 1. Every time the function returns, it adds the return int,
//depending on which is higher (which is determined by which gets successfully called/returned more).
//Eventually the highest is returned from the first call to the main program, where it's printed out as "max depth".

int traverse (struct node *root){

	if (root==NULL) return (0);

	int left=(traverse(root->left));
	printf("%d ",root->data);
	int right=(traverse(root->right));

	if(left>right)

		return (left+1);
	else
		return (right+1);
}

//balanced function.  increments left and right recursively to determine depth. If (abs) right is more than 1 deeper than left, 
//returns 0. Else, calls balanced for both sides, and returns 1 if both sides are balanced (not returning 0, which only occurs
//if they're out of balance.

int balanced(struct node *root){ 

	if(root == NULL) return 1; 

	int left = left+balanced(root->left); 
	int right = right+balanced(root->right); 

	if(abs(right-left)>1) return 0;
 
	return balanced(root->left) && balanced(root->right);

}

//This function doesn't deserve an explanation.

angsty(){

printf("\n\n\n\n");
int r;
r=rand()%12;
if(r<2){
printf("No.\n");
return;
}
if(r>=2&&r<4){
printf("Please Stop.\n");
return;
}
if(r>=4&&r<6){
printf("I prefer chunky peanut butter.\n");
return;
}
if(r>=6&&r<8){
printf("Nope.\n");
return;
}
if(r>=8&&r<10){
printf("Much error, such sad, wow.\n");
return;
}
if(r>=10){
printf("User rolled D12 for initiative, failed, user has fumbled.\n");
return;
}
}

//Help function.

help (){
printf("Usage Instructions:\n");
printf("'Q' - Quits the program.\n");
printf("'(integer)' - Inserts the number into the tree, enter a number (integers only please).\n");
printf("'d' 'integer' - Deletes the number from the tree, if it exists.\n");
printf("'s' '(integer)' - Searches for the number in the tree.\n");
printf("'p' - Prints the whole tree, as well as its maximum depth, and whether it is balanced.\n");
printf("'?' - Displays this help message again\n");
printf("This program also responds to interpretive dance.\n");
}
