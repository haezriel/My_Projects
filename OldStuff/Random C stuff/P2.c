////Michael Allen-bond
//01/10/2014
//Programming Assignment 2
//This program accepts input from a user in various forms to input numbers in a linked list,
//search the list, delete numbers from the list, and print the list, on command.
//It also has a lot of different error messages, even though I could have just made a single error function.
//This is because I was waiting for a PvP group in WoW, and had a lot of time.
//That's my only justification.  I'm sorry.
//To use this program, simply enter "make", and then ./P2.
//The instructions are displayed from there.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

struct node{
	int data;
	struct node *next;
};


//The search function has an int return,
//so that other functions can use the result to direct their logic.

int search(struct node *L, int num);

//Main function. Contains my switches, function calls, fgets, and some frivolous bafoonery.

main(){
	struct node *list;
	char buffer[100];
	int integer,error, i;
	char letter, switcher;	

//Header node, followed by belligerent monologuing.

	list=malloc(sizeof(struct node));	
	list->next=NULL;
	printf("\n");
	printf("__________________________________________________________\n");
	printf("Here-in lies the result of 4 liters of Coke Zero,\n");
	printf("2 hours spent looking at cats on the internet,\n");
	printf("and 12 minutes spent screaming at a search function.\n");
	help();
	printf("\nLet's Begin!\n");
	printf("\n>");
	
//First sscanf checks for an integer entry, and if one is found, it enters 'i' case.
//Else sscanf gives a value to the aptly named 'error', which comes in handy for catching tricky input.
//The if statement for 'i' is in case someone gets clever and puts in 'i' to mess with integer entry.
//I didn't want to put integer entry under my default case, this was my solution.
 	
	while (NULL != fgets(buffer, 100, stdin)){
		if (1==sscanf(buffer, "%d", &integer))
			switcher='i';
		else{
			error=sscanf(buffer,"%s %d", &letter, &integer);
			switcher=letter;
			if(switcher=='i'){
				printf("Dohoho, I see what you did there..\n");
				switcher='b';
			}
		}

//Switch statement block.	
		
		switch(switcher){
	
//'Q' is really simple, print something snarky, exit program
		
		case 'Q':
			printf("Entering infinite loop, launching 7000 copies of P2.\n");
			exit(0);

//'s' will trigger the error if not accompanied by a number (caught by the earlier sscanned error variable),
//otherwise if input correctly, triggers a search, which returns 1 if number already exists,
//or tells us the number doesn't exist if anything else (0) is returned.

		case 's':
			if (error==1){
                                printf("Ok, so you either didn't enter a number, or you didn't use a space.\n");
                                printf("You must REALLY love reading help menus.\n\n");
				help();
				break;
                                }
                        if(1==search(list->next,integer))
                                printf("Found it. Found your number, %d. It's right here. Where you put it.", integer);
                        else
                                printf("It's not in here, man.. I checked, like, all the numbers, and none of them were %d..", integer);
                        break;

//'d' has the same error check to make sure people put their input in correctly,
//again accompanied by snarky and extraneous output. Assuming things are entered correctly,
//we first use the search function to check for the node, and then delete it if it exists.
//It should be noted that delete function has a search built in, but we confirm the number/node's existance first
//with the search function to prevent trying to manipulate a NULL and seg faulting(from experience).

		case 'd':
			if (error==1){
				printf("Gotta give me a number to delete. Did you forget to use a space again?\n");
				printf("Wait here, I'll get you some help.\n\n");
				help();
				break;
			}
			if(1==search(list->next,integer)){
				delete(list,integer);
				printf("RIP number %d, gone forever, nary to return, unless you enter it again,\n",integer);
				printf("Which honestly seems like a heartless thing to do.");
				}
			else
				printf("Can't delete what doesn't exist.");
			break;
		
//'i' again utilizes the ever-useful search, and if it returns 0, will insert the integer. case 'i' is triggered by any integer input,
//and will NOT respond to inputting 'i'.  Although you're welcome to try whatever input you'd like. 
//I've written a plethora of error messages.

		case 'i':
			if (0==search(list->next, integer)){
				insert(list, integer);
				printf("Your number has been inserted. If you would like to see the list, enter 'p'.\n");
			}
			else{
				printf("That number is already in your list. If you would like to see the list,\n");
				printf("enter 'p'");
			}
			break;

//'p' prints the whole list, simple stuff, and '?' calls help()

		case 'p':
			traverse(list->next);
			break;
		case '?':
			help();
			break;

//Yes.  This is an entire case block devoted to monologuing and being annoying.  I'm sorry.

		default:
			printf("Error detected between keyboard and chair.\n");
			printf("Attempting to remove erroneous component.\n");
			printf("Did you leave the oven on? You should go check.\n");
			for (i=0;i<10;i++)
				printf("\n");
			printf("Erroneous component either successfully removed or slightly worried about their oven.\n");
			printf("Resuming program.\n");
			printf("\n");
			help();
			break;
		
		}

//This little set of commands is to make sure that people can't just press enter again and duplicate a command
//that they just entered.  'b' is just my go-to letter for getting a default case.  This just makes sure that people 
//have to input something to get a case other than default.

		letter='b';
		switcher='b';
		printf("\n>");
	}
}
//END OF MAIN FUNCTION

//Insert function. Takes in pointer to header node, makes a new node, takes new->next from header, makes header point to new node,
//all done.

insert(struct node *L, int num){
        
        struct node *new;
        new=malloc(sizeof(struct node));
        new->data=num;
        new->next=L->next;
        L->next=new;
        

}     

//Delete function. Takes in pointer to header node, checks next (checking first node), uses del node as a temp node to hold
//the node that needs to be deleted while L node is connected to the del->next node. Once everything's set, del is freed.

delete (struct node *L, int num){
	
	struct node *del;
	while(L!=NULL){	
		if (L->next->data==num){
			del=L->next;
			L->next=L->next->next;
			free(del);
			return;
		}
		L=L->next;			
	}
}	

//Search function. Takes in pointer to header->next (this is to avoid catching the data portion of header node),
//and searches for a match from there. If match is found, return 1, if not, return 0.

int search (struct node *L, int num){
		
	while (L!=NULL){
		
		if (num==L->data)
			return 1;
		L=L->next;
		}
	return 0;
}	

//Ok this is basically an exact copy of the print function that is in the sample code, not much to improve on or change.
//This function also takes in pointer to header->next to, again, avoid the data portion of the header.

traverse (struct node *L){

printf("Numbers currently in your list:\n");
while (L != NULL){
    printf("%d ",L->data);
    L=L->next;
  }
  printf("\n");
}

//Simple help function.

help (){
printf("Usage Instructions:\n");
printf("'Q' - Quits the program.\n");
printf("'(integer)' - Inserts the number into the list, enter a number (integers only please).\n");
printf("'s' '(integer)' - Searches for the number in the list.\n");
printf("'d' '(integer)' -  Deletes the number from this list.\n");
printf("'p' - Prints the whole list.\n");
printf("'?' - Displays this help message again\n");
printf("If you enter anything else, you will recieve an error message,\n");
printf("And one of your lightbulbs will burn out, and you'll start to believe in wizards.\n");
}
