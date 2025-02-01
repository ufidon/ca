#include <stdio.h>

// Function performing floating-point arithmetic
double funct(double a, float x, double b, int i)
{
  return a * x - b / i;
}

// Function with more arguments performing division and subtraction
double funct1(double p, double q, double r, double s)
{
  return p / (q + r) - s;
}

int main()
{
  double a = 5.5, b = 2.0, p = 20.0, q = 4.0, r = 6.0, s = 3.0;
  float x = 3.5f;
  int i = 2;

  double result1 = funct(a, x, b, i);
  double result2 = funct1(p, q, r, s);

  printf("funct(a, x, b, i) = %f\n", result1);
  printf("funct1(p, q, r, s) = %f\n", result2);

  return 0;
}
