/*Michael Allen-Bond
Programming Assignment 1
CS 360
Dr. Lang
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <getWord.h>
#include "hash.h"

void error(int N);
void help();

int main(int argc, char **argv){
char *word2;			//This stores the second word in the pair
char *wordpair;			//This stores the first word in the pair
char *space;			//This just holds a space character that is placed between the two words.
int testchar;			//This holds values from fgetc in the file testing loop.
int i=1;			//This int holds start points for reading argvalues loop.
char *num;			//This holds the string from argv[1], which represents the limit for output.
int limit;			//limit argument for output function.
FILE *test;			//this is a file pointer used to test whether the file is binary or text
space=" ";

/*This statement checks for a limit argument, and if there is one,
assigns it to the int 'limit', and then checks if there is a file argument.*/
if (argv[1]!=NULL&&argv[1][0]=='-'){
	if(argv[2]==NULL) error(1);
	num=argv[1]+1;
	limit=atoi(num);
	i=2;
}
else {
	if(argv[1]==NULL) error(1);	
	limit=0;
}
//end of statement

Table *Hashtable=hash(50);	//initializes hashtable

//This loop contains all of the file I/O
for(;i<argc;i++){
	FILE *text;

	//This statement makes sure the file exists and is readable
	if((access(argv[i],F_OK)||access(argv[i],R_OK))!=0){
		free(Hashtable);
		error(0);
	}
	//end of statement
	
	/*This loop makes sure that the file is not binary,
	by ensuring that every character is in the ASCII dictionary.*/
	test=fopen(argv[i], "r");
	while((testchar=fgetc(test))!=EOF)
		if(testchar<0||testchar>127){
			free(Hashtable);
			fclose(test);
			error(2);
		}
	fclose(test);	
	//End of loop
	
	//This loop reopens the file for actual parsing and hashing.	
	text=fopen(argv[i], "r");
	wordpair=getNextWord(text);
	word2=getNextWord(text);
	while(word2!=NULL){
		strcat(wordpair,space);
		strcat(wordpair,word2);
		
		Hashtable=hashadd(wordpair, Hashtable);
		wordpair=word2;
		word2=getNextWord(text);
	}
	fclose (text);
	//End of hashing loop.
}	

output(Hashtable,limit);

freehash(Hashtable);

}



//function for various error messages
void error(int N){
	switch(N){
		case 0:
			fputs("One of your file arguments is either not a file, or not readable.\n\n",stderr);
			help();
			exit(1);
		case 1:
			fputs("You must input at least one argument for the program, which must be a readable file.\n\n",stderr);
			help();
			exit(2);
		case 2:
			fputs("The input files must be text files, not binary files.\n\n",stderr);
			help();
			exit(3);
}
}

//help function
void help(){
printf("Proper input for this program:\n");
printf("wordpairs <-count> fileName1 <fileName2> <fileName3> …\n");
printf("OR\n");
printf("wordpairs fileName1 <fileName2> <fileName3> …\n");
printf("Where: count is the integer number of word pairs to print out\n");
printf("and fileNameN are pathnames from which to read words.\n");
printf("If no count argument is specified, ALL words are\n");
printf("printed to stdout. (tokens enclosed in angular brackets\n");
printf("are optional).\n\n");
}

