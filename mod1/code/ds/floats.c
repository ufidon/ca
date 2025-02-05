#include <stdio.h>

// Floating Point Addition
float fadd(float x, float y)
{
  return x + y;
}

double dadd(double x, double y)
{
  return x + y;
}

// Floating Point Memory Referencing
double dincr(double *p, double v)
{
  double x = *p;
  *p = x + v;
  return x;
}

int main()
{
  float a = 1.5f, b = 2.5f;
  double c = 3.5, d = 4.5;
  double val = 10.0;

  printf("fadd(%f, %f) = %f\n", a, b, fadd(a, b));
  printf("dadd(%lf, %lf) = %lf\n", c, d, dadd(c, d));

  printf("Original val: %lf\n", val);
  double old_val = dincr(&val, 5.0);
  printf("dincr(&val, 5.0): old = %lf, new = %lf\n", old_val, val);

  return 0;
}
