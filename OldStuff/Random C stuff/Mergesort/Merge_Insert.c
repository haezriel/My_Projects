//Michael Allen-Bond
//02/24/2014
//CSE 223
//Programming Assignment 7
//This program demonstrates either a merge sort or an insertion sort, depending on the user's input.
//simply type "make" and "./P7" to start program.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "extra.h"
#define MAX 32

//Main block.  array initialized here, as well as input buffer for switch.  Other than that, not much to see here.

main(){
int array[MAX];
int num,i;
char buffer[120],nope;

printf("Please Enter either 'm' to do a merge sort, or 'i' to do an insert sort, or 'q' to quit.\n");

//Input block.  Just allows user to enter either merge sort or insert sort, and then carries out the respective sort.
//Displays help message if input is incorrect.

while(NULL!=fgets(buffer,120,stdin)){
	if(1==sscanf(buffer,"%c %s", &buffer[0],&nope)){
		if(buffer[0]=='i'||buffer[0]=='I'){
			myRnd(array,MAX);
			clear_display();
			printf("Insert Sort\n");
			display(0,array,MAX);
			delay(500);
			insert(array,MAX-1);
			printf("Insert Sort Completed.\n");
		}
		else if(buffer[0]=='m'||buffer[0]=='M'){
			myRnd(array,MAX);
			clear_display();
			printf("Merge Sort\n");
			display(0,array,MAX);
			delay(500);
			mergesort(array,0,MAX-1);
			printf("Merge Sort Completed.\n");
		}
		else if(buffer[0]=='q'||buffer[0]=='Q'){
			printf("Bye!\n");
			exit(0);
		}
		else
			printf("Please Enter either 'm' to do a merge sort, or 'i' to do an insert sort, or 'q' to quit.\n");
	}
}
}

//Insert function.  Goes through the array i->MAX-1, continually checks array[j] against the entry before it, and if it's smaller, swaps them.
//repeats for each index [i] until sorted.

insert(int *array,int num){
int i,j,k;
for (i=1;i<=num;i++){
	clear_display();
	j=i;
	while(j>0 && array[j]<array[j-1]){
		k=array[j];
		array[j]=array[j-1];
		array[j-1]=k;
		j--;
	}
	printf("Insert Sort\n");
	display(i,array,MAX);

	delay(500);
}
return;
}

//Recursive merge sort function.  Pretty simple, takes max+min/2 to get the middle number, uses that at the divider for the array,
//repeats until we just have arrays of 1-2 elements, and then merges them up from there (merge was the hard one).
//the if(min<max) ensures that our array is more than 1 element long before trying to split it, the merge uses the min and mid
//as starting indexes for comparing the 2 parts of the array in the merge. And then display, etc.

mergesort(int *array,int min,int max){
if(min<max){
	int mid=(max+min)/2;
	mergesort(array,min,mid);
	mergesort(array,(mid+1),max);
	
	merge(array,min,mid,max);
	clear_display();
	printf("Merge Sort\n");
	display(min,array,MAX);
	printf("Press enter to continue sorting.\n");
	delay(500);
	return;
}
return;
}

//Merge function. Commented throughout,  this does all the secretarial work of the function, and took me about 300
//printf statements to pick out all the discrepancies.

merge(int *array, int min, int mid, int max){

//Initialized temp array to hold my organized entries before copying them back. i is base counter, m is mid-max array counter,
//l is min-mid array counter, k is extra counter for copying arrays.

int i,m,k,l,temp[MAX];
l=min;
i=min;
m=mid+1;

	//If min-mid array entry is less or equal to mid-max array entry, it will insert that entry into
	//the next temp array slot, and then increment the min array. else, it increments the mid array
	//and puts that entry into temp.  afterwards, increments temp up to next slot.  	

while((l<=mid)&&(m<=max)){
	if(array[l]<=array[m]){
		temp[i]=array[l];
		l++;
	}
	else{
		temp[i]=array[m];
		m++;
	}
	i++;
}

	//This checks if the min array "empties" before mid array, and then dumps the rest of mid array into temp(up to max).
	//or if mid array "empties" first, it dumps the rest of min array into temp (up to mid).

if(l>mid){
	for(k=m;k<=max;k++){
		temp[i]=array[k];
		i++;
	}
}
else{
	for(k=l;k<=mid;k++){
		temp[i]=array[k];
		i++;
	}
}

	//Copies entire temp array into main array.

for(k=min;k<=max;k++)
	array[k]=temp[k];

}

