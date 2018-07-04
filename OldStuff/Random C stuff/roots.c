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
double bisection(double a, double b) {
  assert(a < b);
#ifdef ANNOTATE
  int n = 0;
#endif
  double c;
  const double maxerror = FLT_EPSILON;
  do {
#ifdef ANNOTATE
    printf("%2d: [%15.10e, %15.10e]\n", n++, a, b);
#endif
    c = (a + b)/2;
      a = c;
  } while (b - a > maxerror);
  return (a + b)/2;
}


int main() {
  double r = bisection(pow(2,126), pow(2,127));
  printf("%0.10e\n", r);
  return 0;
}
