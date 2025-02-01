#include <stdio.h>

// Function to demonstrate moving floating-point values
float float_mov(float v1, float *src, float *dst)
{
  float v2 = *src; // Read value from source pointer
  *dst = v1;       // Store v1 into destination pointer
  return v2;       // Return the value read from source
}

// Function to convert between different floating-point and integer types
double fcvt(int i, float *fp, double *dp, long *lp)
{
  float f = *fp;  // Read float from pointer
  double d = *dp; // Read double from pointer
  long l = *lp;   // Read long from pointer

  *lp = (long)d;   // Convert double to long and store
  *fp = (float)i;  // Convert int to float and store
  *dp = (double)l; // Convert long to double and store

  return (double)f; // Return converted float as double
}

// Function to convert using pointer references
double fcvt2(int *ip, float *fp, double *dp, long l)
{
  int i = *ip;    // Dereference integer pointer
  float f = *fp;  // Dereference float pointer
  double d = *dp; // Dereference double pointer

  *ip = (int)l;    // Convert long to int
  *fp = (float)d;  // Convert double to float
  *dp = (double)i; // Convert int to double

  return (double)f; // Return float as double
}

// Main function to test the implementations
int main()
{
  float src = 3.5f, dst = 0.0f;
  float result = float_mov(2.5f, &src, &dst);
  printf("float_mov result: %.2f, dst: %.2f\n", result, dst);

  int i = 10;
  float f = 4.2f;
  double d = 8.9;
  long l = 20;

  double res1 = fcvt(i, &f, &d, &l);
  printf("fcvt result: %.2f, f: %.2f, d: %.2f, l: %ld\n", res1, f, d, l);

  double res2 = fcvt2(&i, &f, &d, l);
  printf("fcvt2 result: %.2f, i: %d, f: %.2f, d: %.2f\n", res2, i, f, d);

  return 0;
}
