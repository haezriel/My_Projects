//Michael Allen-Bond
//CSE 222
//02/28/14
//Programming Assignment 8 (or knap)
//This program accepts an integer argument as a maximum capacity,
//then reads an inventory out of knapsack.data, and calculates the highest value to be acquired from
//a combination of items in the inventory, up to the capacity threshold.
//To use this program, type "make", and then ./knap <integer>.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "key.h"

//Object struct.  This will hold each item I read out of knapsack.data(up to 1024).
//int val for value, int wt for weight, and name to hold the name of the object(up to 32 chars).

struct object{
	int val,wt;
	char name[32];
};

//Max struct.  This holds the max values for each iteration, as well as the item inventory count,
//held in int array ct.
//global int count will track iterations of maxcalc function.

struct max{
	int max,ct[129];
};

int count;

//Main Block initialization: struct object, struct max are self-evident,
//int maximum holds the max value returned from the maxcalc function call,
//i is a counter, cap is the total amount of space in the bag, retrieved from argv,
//counter is the total number of objects available in knapsack.data,
//buffer just holds string input from knapsack.data
//and FILE bag is our pointer to knapsack.data.

main(int argc, char **argv){
struct object *object;
struct max *max;
int maximum,j,i,cap,counter;
char buffer[1000];
FILE *bag;

//I'm allocating 1024 locations for max, which makes room for holding up to 1024 max values(and respective inventories),
//as well as allocating 128 object locations for our knapsack.data entries.
//Then max is initialized to -1.

max=malloc(1025*sizeof(struct max));
object=malloc(129*sizeof(struct object));
for(i=0;i<1025;i++){
	max[i].max=-1;
}
i=0;

//if argc!=2, we quit. 

if(argc!=2){
	printf("Please type ./knap <integer>.\n");
	exit(0);
}

//if the second string is not a number, we quit.

if(1!=sscanf(argv[1],"%d",&cap)){
	printf("Must be integer entry less than 1025.\n");
	exit(0);		
}

//if the number is over 1024, we quit.

if(cap>1024){
	printf("Must be integer entry less than 1025.\n");
	exit(0);
}

//opens knapsack.data to bag pointer, if knapsack.data is NULL, quits.
//Otherwise, we begin to read knapsack, and filter valid input into our object array, up to 128.

bag=fopen("knapsack.data", "r");

if(bag<=0){
	printf("There's nothing in your knapsack...\n");
	exit(0);
}

printf("\nReading knapsack.\n");
while(NULL!=fgets(buffer,1000,bag)){
	if(2==sscanf(buffer,"%d %d %s\n", &object[i].wt, &object[i].val, &object[i].name[0])&&object[i].wt!=0){
		strcpy(object[i].name,"Unnamed item");
		i++;
	}
	else if(3==sscanf(buffer,"%d %d %s\n", &object[i].wt, &object[i].val, &object[i].name[0])&&object[i].wt!=0){
		i++;
	}
	else{
		printf("Bad data in knapsack.\n");
		exit(0);
	}
	if(i>128){
		printf("knapsack has too many items.\n");
		exit(0);
	}
}
if(i==0){
printf("Knapsack contained no items.\n");
exit(0);
}

//Here we set all of our counters to 0, and counter tallies up objects in knapsack.data.

count=counter=0;
for(i=0;i<129;i++){
	if(object[i].wt>0)
		counter++;
	else break;
}

printf("\nNumber of items in knapsack = %d\n", counter);
printf("\nMax capacity = %d\n", cap);

//maxcalc is called here, and result as well as iterations is printed.

maximum=maxcalc(cap,object,counter,max)+1;

printf("\n%d is the maximum value, # of iterations: %d\n", maximum, count);

//This loops through max[cap].ct array, which holds the inventory of ideal items for max value,
//and then prints them accordingly.

printf("\nIdeal item list:\n");
for(i=0;i<=counter;i++){
	if(max[cap].ct[i]>0)
	printf("%d %s\n",max[cap].ct[i], object[i].name);
	}

free(max);
free(object);

}

//maxcalc function: imports cap, object struc, counter, and max struct.  f and i are counters,
//c holds (cap-object.weight), m holds intermediate values, and max[cap].max holds the max value that gets returned.
//max[cap].ct holds the inventory from previous calls, and then also increments for it's most recent item entry.

int maxcalc(int cap,struct object *object, int counter, struct max *max){
int f,c,i,m;
count++;
c=0;
if (max[cap].max>=0){ 
return max[cap].max;
}
else{
for(i=0;i<counter;i++){
	if(object[i].wt<=cap){
	c=cap-object[i].wt;
	m=object[i].val+(maxcalc(c, object, counter, max));
	if(m>max[cap].max){
		for(f=0;f<=counter;f++)
			max[cap].ct[f]=max[c].ct[f];
		max[cap].ct[i]++;
		max[cap].max=m;
	}
	}
}
return max[cap].max;
}
}
