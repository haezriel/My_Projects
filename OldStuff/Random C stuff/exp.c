//Michael Allen-Bond
//02/24/2014
//CS 330
//Programming Project #1
//Main program + e^x function.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#define ERROR 0.0000000103245990548
#define Const7 0.0001984127011382952
#define Const6 0.0013888889225199819
#define Const5 0.0083333337679505348
#define Const4 0.0416666679084300995
#define Const3 0.1666666716337203979
#define Const2 0.5
#define M_LN2 0.6931471805599452862
#define M_LOG2E 1.4426950408889633870

float myexp(float x);

//Main function, just creates variabls and calls myexp function.
int main(){

long double f,d,e;
float x,b;

for(x=-20.0;x<=20.0;){			//just did interval -20 -> 20 in jumps of 1.3333
	b=myexp(x);
	d=expl(x);
	f=x;				//setting x to long double f for printf
	e=(fabsf(b-exp(x)))/(exp(x));
	printf("x=%+0.9Le, myexp(x)=%0.9e, expl(x)=%0.9Le, relative error=%0.15Le\n",f,b,d,e);
	x=x+1.33333333;
}
}

float myexp(float x){
int m;			
float z,w,v,u,l;
l=1.0;
z=x*(M_LOG2E);			//Basically following the range reduction from the assignment sheet verbatim
m=roundf(z);			
w=(z-m);
u=w*M_LN2;
if(m>=0)
l=(1<<m);			//using bitwise operators for the integer portion of x
else{
m=fabsf(m);			//if m is negative, taking reciprocal (after manipulating bits)
//printf("%d\n",m);
m=(1<<m);
l=m;
l=1.0/l;
//printf("%e\n",l);
}
//v=fma(u,Const7,Const6);	
//v=fma(u,v,Const5);		//This is just the step-by-step Horner's method
//v=fma(u,v,Const4);		//I only did this for testing values along each step
//v=fma(u,v,Const3);
//v=fma(u,v,Const2);		
//v=fma(u,v,1.0);
//v=fma(u,v,1.0)+ERROR;

v=fma(u,(fma(u,(fma(u,(fma(u,(fma(u,(fma(u,(fma(u,Const7,Const6)),Const5)),Const4)),Const3)),Const2)),1)),1)+ERROR;
v=l*v;				//v holds 2^m*e^u
return v;
}
		
