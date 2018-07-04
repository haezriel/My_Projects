//Michael Allen-bond
//02/7/2014
//CSE 222
//Programming Assignment 5
//This program will accept numerical input into both a stack and a queue,
//with commands to switch between the two, and will print the stack/queue upon switching.
//It will also accept remove commands, and will print accordingly.
//To use this program, simply enter "make", and then ./P5.
//The instructions are displayed from there.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
       
//Main block, contains all of my variables, input block, switch statements.
//initialized queue and stack as simple 10 element arrays, using head, tail, and top as tracking variables
//for the two arrays. switcher is for toggling between stack and queue, key is for toggling various cases,
//numerr and nope are error catchers.  I'm pretty certain that this program catches all 
//string errors, no matter what.

main(){
	int queue[10];
	int stack[10];
	int numerr,switcher, head, tail, top, integer;
	char buffer[100];
	char letter[1], key, nope;

//This numerr being initialized to 3 is to keep the first call of Queue from printing an array of awfulness.
//The Queue was very error-prone and required a 3-way error-check, and the Stack took about 5 minutes to finish.

	numerr=3;
	head=tail=top=0;
	help();
	printf("Select State:\n");

//Input block, similar to P4, but with a few changes to make it more precise, and to allow for a persistent switch
//between Queue and Stack.

	 while (NULL != fgets(buffer, 100, stdin)){
                if (1==sscanf(buffer, "%d %s", &integer, &nope))
                        key='i';
                else if (1==sscanf(buffer, "%s %s", &letter[0], &nope)){
                        if(letter[0]=='s' && letter[1]=='\0'){
                                switcher=1;
                                key='w';
                                printf("Stack Mode. Current Stack:\n");
                                print(stack,top);
                        }
                        else if (letter[0]=='q'&& letter[1]=='\0'){
                                switcher=2;
                                key='w';
                                printf("Queue Mode. Current Queue:\n");
                                prints(queue,head,tail,numerr);
                        }
                        else if (letter[1]=='\0')
                                key=letter[0];
                        else key='b';
                        if (letter[0]=='i'||letter[0]=='w')
                                key='b';
                }

//Switch block. I created the modules incrementally and realized I could have probably just done if statements,
//but cases felt a little cleaner, even though there aren't really that many.
		
		switch(key){
//Quit case, self-explanatory		

		case 'Q':
			printf("Exiting program, resume frolicking.\n");
			exit(0);

//Pop/Remove case, checks for proper switch activation, and then proceeds to call pop or remove functions,
//Depending on which switch is on.

		case 'p':
			if(switcher!=1&&switcher!=2){
			angsty();
			help();
			break;
			}
			if(switcher==1 && top!=0){
				top=pop(stack,top,integer);
				break;
			}
			if(switcher==2 && numerr!=2 && numerr!=3){
				head=rem(queue,head,integer);
			if(head==tail) numerr=2;
			else numerr=0;
			break;
			}
			else printf("Array is empty.\n");
			break;

//Activated by integer entry, does the same switcher check,  and then calls my push/add functions.  The numerr
//was key to catching errors with the head and tail pointing to the same array slot, 
//and it's also present in the pop/remove case, above.

		case 'i':
			if(switcher!=1&&switcher!=2){ 
			angsty();
			help();
			break;
			}
			if(switcher==1 && top!=10){
				top=push(stack,top,integer);
				break;
			}
			if(switcher==2 && numerr!=1){
				tail=add(queue,tail,integer);
			if ((tail)==head) numerr=1;
			else numerr=0;
			break;
			}
			else printf("THE ARRAY IS FULL STOP NOOOOOOOOOOOOOOOO\n");
			break;

//w case, activated solely to allow a silent break from the case statement (no angsty or help functions)

		case 'w':
			break;		

//default, everything besides useful calls should fall here, and recieve my delightful messages.

		default:
			angsty();
			help();
			break;
		}

//These reset case variables for the next input to prevent re-entries.

	letter[0]='b';
	key='b';

	}

}

//Push function, super simple, sets array[top] to num, increments top, prints num, returns top.

int push(int stack[10],int top,int num){
	stack[top++]=num;
	printf("Number %d successfully entered.\n", num);
return top;
}

//Pop function, again, simple, prints array[top], decrements, returns.

int pop(int stack[10],int top,int num){
	printf("Popping %d.\n", stack[--top]);
return top;
}

//The queue functions were a little more complicated. Add function, sets tail to num, increments tail,
//if tail is 10,sets to 0, prints, returns tail.

int add(int queue[10],int tail, int num){
	queue[tail]=num;
	tail++;
	if (tail>9) tail=0;
	printf("Number %d successfully entered.\n",num);
return tail;
}

//Basically the add function in reverse, rem prints the head, increments it, if head is 10, sets to 0, returns.

int rem(int queue[10], int head, int num){
	printf("Removing %d.\n", queue[head]);
	head++;
	if (head>9) head=0;
return head;
}

//Prints Stack from the top down, again, easier function of the 2 prints.

print(int stack[10], int top){
	while(top>0)
		printf("%d ",stack[--top]);
return printf("\n");
}

//This function was incredibly irritating to make, due to the plethora of conditional errors that can occur,
//such as printing an array where the tail has looped all the way around and is now equal to the head,
//or when the queue is first made and contains no input numbers. I ended up handing in numerr here
//because it was vital for distinguishing various conditions.

prints(int queue[10], int head, int tail, int numerr){
	if(numerr==3||numerr==2) return printf("\n");
	while(1){	
		printf("%d ",queue[head]);
		head++;
		if (head>9) head=0;
		if (head==tail) break;
	}
return printf("\n");
}

//angsty, because it was easy to copy and edit, and amuses me.

angsty(){

printf("\n\n\n\n");
int r;
r=rand()%12;
if(r<2){
printf("This is an error message. You have erred. Sorry.\n");
return;
}
if(r>=2&&r<4){
printf("I think it might be time for a nap, what you just entered made no sense. Go to bed, man.\n");
return;
}
if(r>=4&&r<6){
printf("Let's admit that we all occasionally input strings of curse words when we're bored.\n");
return;
}
if(r>=6&&r<8){
printf("Ok, no, obviously no, that's not right.\n");
return;
}
if(r>=8&&r<10){
printf("Much error, such sad, wow.\n");
return;
}
if(r>=10){
printf("I'm allergic to mangoes, you're allergic to following directions.\n");
return;
}
}

//Help, because help.

help (){
printf("\n\n\n\n");
printf("Usage Instructions:\n");
printf("'Q' - Quits the program.\n");
printf("'(integer)' - Inserts the number into the queue or the stack.\n");
printf("'p' - Removes the number from the queue, or pops it from the tree, and prints it.\n");
printf("If you'd like you can see this message again by typing entirely the wrong thing.\n");
}

