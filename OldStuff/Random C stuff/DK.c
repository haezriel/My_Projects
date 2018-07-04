#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <float.h>
#define M_PI 3.14159265358979323846
#define MAXN 25 // max degree

complex double f(complex double z,complex double c[MAXN+1],int n);

int main(void) {
  int j,i;
  int n = 0;  // polynomial degree 
  complex double c[MAXN+1];
  double a, b;
  while (scanf("%lf %lf", &a, &b) == 2)
    c[n++] = a + b*I;
  c[n] = 1;  // leading coeff implied

  complex double Q;
  complex double z[MAXN+1];
  double max=0;
  complex double dz[MAXN+1];
  double dzmax;
  for (j=0;j<=n;j++)
	if (cabs(c[j])>cabs(max)){
		max=cabs(c[j]);
	}
  double R=1+max;
  printf("Initial Guesses:\n");
  for (j=0;j<=n-1;j++){
	z[j]=((cos(j*(2*M_PI)/n)+I*sin(j*(2*M_PI)/n)))*R;
	printf("%0.10f+%0.10fi\n", creal(z[j]),cimag(z[j]));
  }
  for (int k=1;k<=50;k++){
	dzmax=0;

  	for(j=0;j<=n-1;j++){
		Q=1;
		for(i=0;i<=n-1;i++){
			if(i!=j)
			Q*=(z[j]-z[i]);
		}
		dz[j]=(-f(z[j],c,n))/Q;
  		if(cabs(dz[j])>cabs(dzmax))
			dzmax=cabs(dz[j]);
  	}
	printf("Iteration[%d]\n",k);
  	for(j=0;j<=n-1;j++){
		z[j]=z[j]+dz[j];
  		printf("z[%d] = %0.10f+%0.10f i\n",j,creal(z[j]),cimag(z[j]));
	}
	if (cabs(dzmax)<=FLT_EPSILON) 
		break;
	
  }
  printf("Final:\n");
  for (int i = 0; i < n; i++) {
    printf("%0.10f + %0.10f i\n", creal(z[i]), cimag(z[i]));

  }

  
  return 0;
}

complex double f(complex double z,complex double c[MAXN+1],int n){
complex double fz=1;
for(int i=n-1;i>=0;i--)
	//fz=fma(z,fz,c[i]);
         fz = z*fz + c[i];

return fz;
}
