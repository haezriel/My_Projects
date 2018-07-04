// Assignemtn 2 problem 6.cpp : Defines the entry point for the console application.
// This program runs in visual studios C++ Should also run on C without the stdafx and the using namepsace

#include <math.h>  
#include <stdio.h>


//==================================
double factorial ( double x) {
return (x==1 || x==0) ? 1 : factorial (x -1) * x;
}// double factorial()
//====================

int main() {

double x = 3.0;// change these variables as needed
double c = 2.0;// change these variables as needed
double q = x-c;
double fun2 = pow(q,2);
double fun3 = pow(q,3);
double fun4 = pow(q,4);
double fun5 = pow(q,5);
double fun6 = pow(q,6);

double zero, first, second, third, fourth, fifth, sixth, seventh, something;//sixthdegree;

zero = exp(-c*c);
first = -2*c*exp(-c*c);
second = (4*(c*c) - 2)*(1/exp(c*c));
third = (-8*(c*c*c)+12*c)*(1/exp(c*c));
fourth = (16*pow(c,4) - 48*pow(c,2) + 12)*(1/exp(c*c));
fifth = (-32*pow(c,5) +160*pow(c,3) - 120*c)*(1/exp(c*c));
sixth = (64*pow(c, 6) - 480*pow(c, 4) + 720*pow(c,2) - 120)*exp(-c*c);
printf ("%.10f , \n", zero); 
printf ("%.10f , \n", first);
printf ("%.10f , \n", second);
printf ("%.10f , \n", third);
printf ("%.10f , \n", fourth);
printf ("%.10f , \n", fifth);
printf ("%.10f , \n", sixth);

something = zero + first*q + (second/factorial(2))*fun2 + (third/factorial(3))*fun3 + (fourth/factorial(4))*fun4 + 
(fifth/factorial(5))*fun5 + (sixth/factorial(6))*fun6;


double a = (exp(-x*x));
double abserror = fabs(a) -fabs(something);
printf ("%0.10le , \n", abserror);
return 0;
}
