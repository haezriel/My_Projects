#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "LUdecomp.h"


void LUdestroy(LUdecomp *decomp){
int i;
for(i=0;i<decomp->N;i++)
		free(decomp->LU[i]);
free(decomp->LU);
free(decomp->mutate);

free(decomp);
return;
}

void LUsolve(LUdecomp *decomp, const double *b, double *x){
int i,j;
double *y=malloc(decomp->N*sizeof(double*));
for(i=0;i<decomp->N;i++)
	y[i]=b[decomp->mutate[i]];
for(i=1;i<decomp->N;i++)		//22
	for(j=0;j<i;j++)				
		y[i]=y[i]-(decomp->LU[i][j]*y[j]);

j=(decomp->N)-1;
x[j]=(y[j])/(decomp->LU[j][j]);
i=j-1;
for(;i>=0;i--){					//23
	for(j=i+1;j<decomp->N;j++)
		y[i]=y[i]-(decomp->LU[i][j]*x[j]);
	x[i]=(1/(decomp->LU[i][i]))*y[i];
}
return;
}
										//Numbers represent the steps through the written algorithm
LUdecomp *LUdecompose(int N, const double **A){

LUdecomp *decomp=malloc(sizeof(LUdecomp));
decomp->N=N;
decomp->LU=malloc(N*sizeof(double**));
double *swap;
short x;
int n,r,j,i,k;
double p;

swap=malloc(N*sizeof(double*));

for(r=0;r<N;r++)					//Initialize decomp	
	decomp->LU[r]=malloc(N*sizeof(double*));

decomp->mutate=malloc(N*sizeof(short*));

for(r=0;r<N;r++)					//Initialize mutate
	decomp->mutate[r]=r;

decomp->d=1;

for(j=0;j<N;j++){					//copy A into LU
	for(i=0;i<N;i++){
		decomp->LU[j][i]=A[j][i];
	}
}
for (j=0;j<N;j++){				//2
	for(i=0;i<=j;i++){			//3
		for(k=0;k<i;k++)
			decomp->LU[i][j]=decomp->LU[i][j]-(decomp->LU[i][k]*decomp->LU[k][j]);
	}
	p=fabs(decomp->LU[j][j]);	//5
	n=j;								//6
	for(i=j+1;i<N;i++){			//7
		for(k=0;k<j;k++)			
			decomp->LU[i][j]=decomp->LU[i][j]-(decomp->LU[i][k]*decomp->LU[k][j]);
		if(fabs(decomp->LU[i][j])>p){		//9
			p=fabs(decomp->LU[i][j]);
			n=i;
		}
	}
	if(p==0){						//12
		printf("SINGULAR MATRIX.\n");
		exit(0);
	}
	if(n!=j){						//13
		swap=decomp->LU[n];
		decomp->LU[n]=decomp->LU[j];
		decomp->LU[j]=swap;
		x=decomp->mutate[n];
		decomp->mutate[n]=decomp->mutate[j];
		decomp->mutate[j]=x;
		decomp->d=-1*(decomp->d);
	}
	for(i=j+1;i<N;i++)			//17
		decomp->LU[i][j]=decomp->LU[i][j]/decomp->LU[j][j];	

}


return decomp;
}

