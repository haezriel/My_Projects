#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

main(){
double x,y,z,m;
x=4;
m=.5;
y=.5;
z=y-1;
int n=10;
int k=0;
int j=n-1;
int a=1;

for (k=n-1;k<=0;k--){
	if(k%2==0)
		m=fma(x,m,a);
	else
		m=fma(x,m,-a);
}		
printf("%f\n",x*m);
//x=x*m;
//printf("%f\n",x);
}
