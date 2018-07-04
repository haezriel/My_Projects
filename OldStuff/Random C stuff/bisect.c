#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>

#define ANNOTATE

//
// bisection method for find the root of a given function f(x).
// input:
//   f : function of one variable,
//   [a,b] : valid bracket for root
//
double bisection(double (*f)(double), double a, double b) {
  assert(a < b);
  double fa = f(a);
  double fb = f(b);
  assert(fa*fb <= 0);
#ifdef ANNOTATE
  int n = 0;
#endif
  double c;
  const double maxerror = DBL_EPSILON*(fabs(a) + fabs(b));
  do {
#ifdef ANNOTATE
    printf("%2d: [%15.10e, %15.10e]\n", n++, a, b);
#endif
    c = (a + b)/2;
    double fc = f(c);
    if (fa*fc < 0) {
      b = c;
      fb = fc;
    } else {
      a = c;
      fa = fc;
    }
  } while (b - a > maxerror);
  return (a + b)/2;
}

double f(double x) {
  const double s = exp(-x)-cos(x);
  return s;
}

int main() {
  double r = bisection(f, 0, 3.14/2);
  printf("%0.10e\n", r);
  return 0;
}
