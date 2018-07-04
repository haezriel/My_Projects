#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

long double trap(long double (*f) (long double), long double a, long double b, int n);
long double simpsons(long double (*f) (long double), long double a, long double b, int n);
long double simpsons38(long double (*f) (long double), long double a, long double b, int n);
long double booles(long double (*f) (long double), long double a, long double b, int n);
long double f(long double x);

int main(void) {
  const unsigned maxn = 800000;
	for (unsigned n = 12; n <= maxn; n *= 2) {
    const long double I_trap = trap(f, 0, 1, n);
    const long double error_trap = fabsl(M_PI - I_trap);
    const long double I_simp = simpsons(f, 0, 1, n);
    const long double error_simp = fabsl(M_PI - I_simp);
    const long double I_simp38 = simpsons38(f, 0, 1, n);
    const long double error_simp38 = fabsl(M_PI - I_simp38);
    const long double I_booles = booles(f, 0, 1, n);
    const long double error_booles = fabsl(M_PI - I_booles);
    printf("%5d %0.10Le %0.10Le %0.10Le %0.10Le\n", n, 
       error_trap, error_simp, error_simp38, error_booles);
  }
  return 0;
}

long double trap(long double (*f) (long double), long double a, long double b, int n) {
  assert(a < b);
  const long double h = (b - a)/n;
  long double sum = 0.0;
  long double x = a + h;
  for (int i = 1; i < n; i++, x += h)
    sum += f(x);
  return h*((f(a) + f(b))/2 + sum);
}

long double simpsons(long double (*f) (long double), long double a, long double b, int n) {
  assert(n % 2 == 0);
  assert(a < b);
  const long double h = (b - a)/n;
  long double sum1 = 0.0;
  for (int i = 1; i < n; i += 2)
    sum1 += f(a + i*h);
  long double sum2 = 0.0;
  for (int i = 2; i < n; i += 2)
    sum2 += f(a + i*h);
  return h/3*((f(a) + f(b)) + 4*sum1 + 2*sum2);
}

long double simpsons38(long double (*f) (long double), long double a, long double b, int n){
	assert(a < b);
	assert(n % 2==0);
	const long double h = (b-a)/n;
	long double sum1=0.0;
	for (int i=1;i<n;i+=3)
		sum1+= f(a+i*h);
	long double sum2=0.0;
	for (int i=2;i<n;i+=3)
		sum2+= f(a+i*h);
	long double sum3=0.0;
	for (int i=3;i<n;i+=3)
		sum3+= f(a+i*h);
	return ((h*3)/8)*((f(a)+f(b)) +3*sum1 + 3*sum2 + 2*sum3);

}

long double booles(long double (*f) (long double), long double a, long double b, int n){
	assert(a < b);
	assert(n%2==0);
	const long double h = (b-a)/n;
	long double sum1, sum2, sum3, sum4;
	sum1=sum2=sum3=sum4=0.0;
	for (int i=1;i<n;i+=4)
		sum1+=f(a+i*h);
   for (int i=2;i<n;i+=4)
   	sum2+=f(a+i*h);
   for (int i=3;i<n;i+=4)
      sum3+=f(a+i*h);
   for (int i=4;i<n;i+=4)
      sum4+=f(a+i*h);
	
	return ((h*2)/45)*(7*(f(a)+f(b)) + 32*sum1+12*sum2+32*sum3+14*sum4);
}

long double f(long double x){
	return 4.0L/(1.0L+x*x);
}
