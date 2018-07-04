//Michael Allen-Bond
//CS 330
//relative error calculator (up to n=15)

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>


int main(){
int n;
double z,i;
for(n=1;n<=15;n++){
	z=n+1;				//for each value n+1
        
	for(i=n;i>=1;i--)
                z=z*(i);        	//factorial loop for each n+1

	z=(2/(z))*pow(((log(2))/2),(n+1));  //rest of the error calc formula

	printf("n=%d, rel. error of n+1 = %0.19f\n",n,z);
	}
}

