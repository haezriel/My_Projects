#include "LUdecomp.h"
#include <stdio.h>
#include <math.h>

int main (){
int N,j,t,c;
char buffer[1000];
double key[100];
double x[9];


//x0,y0
int i=0;
fgets(buffer, 1000, stdin);
sscanf(buffer, "%d", &N);
while (NULL!=fgets(buffer, 1000, stdin)){
	sscanf(buffer,"%lf %lf", &key[i], &key[i+1]);
	i=i+2;
}
N=N*2;
j=i;
c=N;
double A8_[N][N]={
	for (t=0;t<N;t+=2,c+=2){
		{key[t],key[t+1],1,0,0,0,(-key[t]*key[c]),(-key[t+1]*key[c])},
		{0,0,0,key[t],key[t+1],1,(-key[t]*key[c+1]),(-key[t+1]*key[c+1])},
	}
};

const double *A[8]={
	A8_[0],A8_[1],A8_[2],A8_[3],A8_[4],A8_[5],A8_[6],A8_[7]
};

const double b[8]={
	key[8],key[9],key[10],key[11],key[12],key[13],key[14],key[15]
};

N=8;
LUdecomp *LU = LUdecompose(N, A);
LUsolve(LU,b,x);
x[8]=1;
for(i=0;i<8;i+=3)
	printf("%lf %lf %lf\n", x[i],x[i+1],x[i+2]);

LUdestroy(LU);

}
