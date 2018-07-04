//Michael Allen-bond
//01/10/2014
//Programming Assignment 1
//This code will ask the user for the number of vectors they would like to input,
//Then it will ask for vector inputs in X Y Z format,
//Then it will display all of the vectors and their calculated lengths.
//To use, simply type "make", and then "./P1", and the program will initiate.
//I don't know if this is enough commenting.
//Potato.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct vector{
	double x;
	double y;
	double z;
};
double length (struct vector *vect);

//Start

main(){
double l;			//l will recieve the return value from the length function.
int vectorcount,p,i;		//vectorcount is # of vectors, p is just a trigger variable for sscanf,
char buffer[100];		//and i is our loop counter.
char error;			//error is my little demon monkey that catches extra input in fgets and triggers errors.

//This section is asking for the vectorcount, if I did this program modularly,
//I would have this in a separate module.

printf("Please enter how many vectors you would like to input(>=1):");
fgets(buffer,100,stdin);
p=sscanf(buffer,"%d %s",&vectorcount, &error);

//error checking loop here, p won't be 1 unless it's a numeric integer input.

while (p!=1){

	printf("\nInteger entry only please, try again: ");
	fgets(buffer,100,stdin);
	p=sscanf(buffer,"%d %s",&vectorcount, &error);
}

printf("\n");

//This would be my second module, it sets up the struct, allocates a multiple
//of sizeof(struct) based on vectorcount's value, and then inputs vectors
//in the ascending array of structs.

struct vector *vectorArray;
vectorArray=malloc(vectorcount*sizeof(struct vector));
for (i=0;i<vectorcount;i++){	
	printf("\nEnter Vector %d's X Y Z values, separated by a spaces: ",i+1);
	if (NULL == fgets(buffer,100,stdin)){
	printf("\nStop pressing control D. Exiting program, killing a puppy for your sins.\n");
	exit(0);
	}
	else
	p=sscanf(buffer,"%lf %lf %lf %s",&vectorArray[i].x,&vectorArray[i].y,&vectorArray[i].z, &error);
	
//Error checking loop.

	while (p!=3){
		printf("\nLet's Try Again. Enter X Y Z values, separated by spaces: ");
		if (NULL == fgets(buffer,100,stdin)){
		printf("\nYou really pressed ctrl D again?  Oh my god, you must hate puppies. Exiting program.\n");
		exit(0);
		}
		else
		p=sscanf(buffer,"%lf %lf %lf %s",&vectorArray[i].x,&vectorArray[i].y,&vectorArray[i].z, &error);
		
	}
}

printf("\n");

//Third module (I would just put the double function into here),
//loops through the (now full) struct array, calculates length(l) for each set of vectors,
//and then prints the vectors and the length.

for (i=0;i<vectorcount;i++){
	l=length(&vectorArray[i]);	//points to the start of vectorArray[i]
       	printf("Vector %d:",i+1);
	printf("\nx=%lf, y=%lf, z=%lf,length=%lf\n",vectorArray[i].x, vectorArray[i].y, vectorArray[i].z,l);
	printf("\n");
}

printf("All Done! :D\n");

}

//Length function, returns double l, utilizes a pointer to a struct, makes me look stupid for taking so long
//to figure it out.

double length (struct vector *v)
{
	double l;
	l=sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
	return l;
}
