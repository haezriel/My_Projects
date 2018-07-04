////Michael Allen-bond
//01/10/2014
//Programming Assignment 3
//This program accepts input from a user in various forms to input numbers in a binary tree,
//search the tree, and print the tree, on command.
//It also has a set of different error messages.

//To use this program, simply enter "make", and then ./P3.
//The instructions are displayed from there.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


struct node{
	int data;
	struct node *left;
	struct node *right;
};

//declaring my two functions with returns.  The insert function will only return a new root node when root is NULL,
//Otherwise it will return new right/left nodes within the function, but won't alter the root.
//Search just returns 1 or 0, depending on whether it finds the appropriate number.

struct node *insert(struct node *root, int num);
int search(struct node *root, int num);

//Main function.  declaring tree, setting it to null, declaring ints and chars to hold various error triggers
//and values (error holds error switch, letter holds char variables, nope catches trailing strings,
//integer holds int value, switcher takes in case value, i is for loops or small function counters.


main(){
	struct node *tree;
	char buffer[100],buffer2[100];
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
			buffer2=buffer;
			error=sscanf(buffer,"%c %d %s", &letter, &integer, &nope);
			switcher=letter;
			if(switcher=='i'){
				printf("Dohoho, I see what you did there..\n");
				switcher='b';
			}
		}

		
		switch(switcher){
	
		
//Switch cases, same as last program.

		case 'Q':
			printf("We're sorry, you have entered a subscriber only feature.  \nIf you would like to subscribe ");
			printf("and download this feature, please enter your name and credit card information below:\n");
			exit(0);

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
                                printf("%d cannot be found in this tree.  Have you tried checking some other trees?..", integer);
                        break;

//Calls search, if not found, calls insert.

		case 'i':
			if (0==search(tree, integer)){
				tree=insert(tree, integer);
				printf("Number %d has been inserted. If you would like to see the list, enter 'p'.\n", integer);
				break;
			}
			else
				printf("%d is already in your tree. Just hanging out up there. I think I saw him eating some of the other numbers.\n",integer);
			break;

//Calls traverse function, prints depth (i)
	
		case 'p':
			if (error!=1){
				angsty();
				for(i=0;i<10;i++)
					printf("\n");
				help();
				break;
			}
			i=traverse(tree);
			printf("\nMax Depth of your tree = %d.",i);
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

//Search function.  Takes in root and num, checks for NULL and for match on every call, and searches all the nodes,
//returning 1 if a match is found anywhere.

int search (struct node *root, int num){
	if(root==NULL) return 0;
	if(root->data==num) return 1;
	
	if(search(root->left,num)==1 || search(root->right,num)==1)
		return 1;
}	


//Traverse function.  Takes in root node, creates 2 ints, initializes them to 1.  Every time the function is called,
//a new instance of num and num2 are made, and set to 1. Every time the function returns, it adds the return int,
//depending on which is higher (which is determined by which gets successfully called/returned more).
//Eventually the highest is returned from the first call to the main program, where it's printed out as "max depth".
//This was the hardest function for me to figure out.

int traverse (struct node *root){
int num,num2;
num2=1;
num=1;
if (root==NULL) return (0);

num=num+(traverse(root->left));
printf("%d ",root->data);
num2=num2+(traverse(root->right));

if(num>=num2)
	return (num);
else
	return (num2);
}

//This function doesn't deserve an explanation.

angsty(){

printf("\n\n\n\n");
int r;
r=rand()%12;
if(r<2){
printf("Yeah there's something wrong with your input. Do you have fingers?\n");
printf("It's fine if you don't, just use your nose. That's how I did this whole program.\n");
return;
}
if(r>=2&&r<4){
printf("Yeah, no, wrong input. Have you tried the newest feature of this program, voice recognition?\n");
printf("Just hold shift+ctrl, and shout 'VOICE RECOGNITION ACTIVATE'. You might have to do it a couple of times.\n");
return;
}
if(r>=4&&r<6){
printf("Ok, so, I'm imagining this scenario where a genie appears and is like 'Hey man, you get 3 wishes.',\n");
printf("And then he explains the rules very carefully before asking 'What's your first wish',\n");
printf("To which you immediately reply 'pqweprlwqer4352' or '[^D]', and then you have 2 wishes left,\n");
printf("And the genie doesn't want to admit that he's mad, but he's pretty upset.\n");
return;
}
if(r>=6&&r<8){
printf("Nope.\n");
return;
}
if(r>=8&&r<10){
printf("But I, being poor, have only my dreams;\n");
printf("I have spread my dreams under your feet;\n");
printf("Tread softly because you tread on my dreams.\n");
return;
}
if(r>=10){
printf("Hang on, something happened with your input, let me transfer you to Tech Support.\n\n\n\n\n");
printf("Hi this Bob with Tech Support, have you tried turning it off then on again?\n");
return;
}
}

//Help function.

help (){
printf("Usage Instructions:\n");
printf("'Q' - Quits the program.\n");
printf("'(integer)' - Inserts the number into the tree, enter a number (integers only please).\n");
printf("'s' '(integer)' - Searches for the number in the tree.\n");
printf("'p' - Prints the whole tree, as well as its maximum depth.\n");
printf("'?' - Displays this help message again\n");
printf("This program also responds to interpretive dance.\n");
}
