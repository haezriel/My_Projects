//Michael Allen-bond
//02/16/2014
//CSE 222
//Programming Assignment 6
//This program will accept up to MAX (defined) words into a hash table, and can search,
//print, and delete them with the appropriate commands.
//To use, type "make", and then ./P6.  The instructions are displayed from there.
//Bruce Willis approves.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define MAX 20

//My struct uses *word to point to my word entries, and tag to indicate whether the slot is empty, holding a word,
//or containing a deleted statement.

struct bucket{
	char *word;
	int tag;
};

//Struct hash is obvious, int error is to contain the return value from my search function, i is just a counter variable.
//buffer takes input from fgets, up to the max of [1024], and word takes the formatted string, again up to 1024.
//char letter holds my letter input, key holds my switch commands, and nope is nope. 

main(){
	struct bucket *hash;
	int error,i;
	char buffer[1024], word[1024];
	char letter[2], key, nope;

//Allocating memory to the hash, initializing all the tags to 0(NULL), and setting nope and word to '\0', so that
//if someone tries to delete or search for nothing with their first input, it doesn't get screwy.

	hash=malloc(MAX*sizeof(struct bucket));
	initialize(hash);
	nope=letter[0]=key=word[0]='\0';
	error=i=0;	

//Input loop, first one checks for 2 set commands, like "#d potato", second one checks for single commands,
//like "#p", third one checks for normal string inserts.

	help();
	while (NULL != fgets(buffer, 1024, stdin)){
	       	if (2==sscanf(buffer, "#%s %s %s", &letter[0], &word[0], &nope)){
			if(letter[1]=='\0'&&letter[0]!='i')
				key=letter[0];
               	}
		else if(1==sscanf(buffer, "#%s %s", &letter[0], &nope)){
			if(letter[1]=='\0'&&letter[0]!='i')
				key=letter[0];
		}
		else if (1==sscanf(buffer, "%s %c", &word[0], &nope)){
			if('#'==word[0]||nope!='\0') key='b';
			else
				key='i';
		}
	
//Switch Statements.

		switch(key){

//Quit case:  calls dump function, which frees all of the string pointers in the hash table.
//then it frees the hash pointer, which should only be pointing to empty structures at this point.
//Then it exits.

		case 'Q':
			if (word[0]!='\0'){
				angsty();
				help();
				break;
			}	
			dump(hash);
			free(hash);
			printf("Exiting Now.\n");
			exit(0);

//Print case:  calls print function, breaks (print function described below).

		case 'p':
			if(word[0]!='\0'){
				angsty();
				help();
				break;
			}	
			print(hash,word);
			break;

//Delete case:  checks if word is '\0', and if not, calls delete function for word.

		case 'd':
			if (strcmp(word,"\0")==0){
				angsty();
				help();
			}
			else
				delete(hash,word);
			break;

//Search case:  Again, checks if word is '\0', if not, calls search, returns with 1 or 0.

		case 's':
			if (strcmp(word,"\0")==0){
				angsty();
				help();
				break;
			}
			error=search(hash,word);			
			if(error==1)
				printf("Found '%s'.\n", word);
			else
				printf("'%s' does not exist in array.\n", word);
			break;

//Insert case:  calls search, if returns 0, calls insert, or prints message if returns 1.
		
		case 'i':
			error=search(hash,word);
			if(error==0){
				insert(hash,word);
			}
			else
				printf("'%s' already exists in array.\n", word);
			break;

//Help case: Help.

		case 'h':
			if (strcmp(word,"\0")!=0)
				angsty();
			help();
			break;

//Default case:  The Ender's Game movie sucked.

		default:
			angsty();
			help();
			break;
		}

//resets word and nope to '\0', letter and key to 'b', this prevents accidentally reusing string information.
	
	nope='\0';
	strcpy(word,"\0");
	letter[0]='b';
	letter[1]='\0';
	key='b';

	}
}

//dump function: creates a counter, loops to MAX, frees hash.word pointers as it goes, returns.
//Called ONLY when exiting the program.

dump(struct bucket *hash){
int i;
for(i=0;i<MAX;i++)
	if(hash[i].tag==1)
		free(hash[i].word);
return;
}

//initialize function: PROBABLY not necessary, as the int tags in the hash struct are most likely already 0,
//but I had some weird issues with another function when I didn't specifically set an int to 0, so this is mostly
//a precaution.  In short, it sets all the tags to 0(NULL).

initialize(struct bucket *hash){
int i;
for (i=0;i<MAX;i++)
	hash[i].tag=0;
}

//delete function: hashes key (If we do more hash tables, I'll be separating the hash function, since it's used so much),
//goes through loop, will only strcmp if there's actually a word in the table, if it matches, will set the string to "\0",
//free the pointer, set the tag to 2(Deleted), and prints confirmation.  Otherwise, keeps searching.

delete(struct bucket *hash, char *key){

int i,x;
x=0;

for(i=0;i<strlen(key);i++)
	x=x+key[i];
x=x%MAX;

for(i=0;i<MAX;i++){
	if(hash[x].tag==1)
		if(strcmp(hash[x].word,key)==0){
			strcpy(hash[x].word,"\0");
			free(hash[x].word);
			hash[x].tag=2;
			printf("'%s' has been deleted.\n", key);
			return;
		}
	else if (hash[x].tag==0||hash[x].tag==2) return printf("'%s' does not exist in the array.\n",key);
	else
		x=(x+7)%MAX;
}
return printf("'%s' does not exist in the array.\n",key);
}

//print function: starts loop, goes through hash table, checks tags, prints message accordingly.

print(struct bucket *hash, char *key){

int i;

for(i=0;i<MAX;i++){
	if(hash[i].tag==0)
		printf("%d               <NULL>\n", i);
	if(hash[i].tag==1)
		printf("%d               %s\n",i, hash[i].word);
	if(hash[i].tag==2)
		printf("%d               <Deleted>\n",i);
}
return;
}

//insert function: hashes key, starts insert loop, if first spot is tagged as available (0 or 2), 
//sets tag to 1, allocates memory for word, copies word into table, prints confirmation message.
//Else, adds 7, mods, and if array is full(MAX loops), prints message.

insert(struct bucket *hash, char *key){

int i,x;
x=0;

for(i=0;i<strlen(key);i++)
	x=x+key[i];
x=x%MAX;

for(i=0;i<MAX;i++){
	if(hash[x].tag==0||hash[x].tag==2){
		hash[x].word=malloc(strlen(key)+1);
		hash[x].tag=1;
		strcpy(hash[x].word,key);
		printf("'%s' has been inserted into slot %d.\n", hash[x].word, x);
		return;
	}
	else
		x=(x+7)%MAX;
}
return printf("Array is full.\n");
}

//search function:  hashes key (this is why I was considering putting it into it's own function),
//checks for content tag (1), compares string, if found, returns 1, if not, continues through loop until MAX.
//returns 0 if no matches found.

int search(struct bucket *hash, char *key){

int i,x;
x=0;

for(i=0;i<strlen(key);i++)
	x=x+key[i];
x=x%MAX;

for(i=0;i<MAX;i++){
	if(hash[x].tag==1)
		if(strcmp(hash[x].word,key)==0) return 1;
	else if (hash[x].tag==0||hash[x].tag==2) return 0;
	else
		x=(x+7)%MAX;
}
return 0;
}

//Angsty function, still going strong.

angsty(){

printf("\n\n\n\n");
int r;
r=rand()%12;
if(r<2){
printf("Cat on keyboard.\n");
return;
}
if(r>=2&&r<4){
printf("Something is input wrong.\n");
return;
}
if(r>=4&&r<6){
printf("Error message #1423: Potato.\n");
return;
}
if(r>=6&&r<8){
printf("Activation code accepted: Engaging transformer mode; Please stand by for giant robots.\n");
return;
}
if(r>=8&&r<10){
printf("Babies aren't dishwasher safe.\n");
return;
}
if(r>=10){
printf("Wrong input, ran out of clever things to say.\n");
return;
}
}

//Help, because help.

help (){
printf("\n\n\n\n");
printf("Usage Instructions:\n");
printf("'#Q' - Quits the program.\n");
printf("'<entry>' - Inserts the entry into the hash table, can be any combination of letters/numbers/symbols\n");
printf("'#p' - prints out the hash table.\n");
printf("'#d <entry>' - deletes the entry, if it exists.\n");
printf("'#s <entry>' - searches for the entry.\n");
printf("'#h' - prints help message.\n");
}

