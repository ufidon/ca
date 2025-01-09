#include <stdio.h>
#include <float.h>

int main()
{
  printf("Size of float: %zu bytes\n", sizeof(float));
  printf("Size of double: %zu bytes\n", sizeof(double));

  // extended precision, 80 bits on x86; 64 or 128 on other architectures
  // resulting in 16 bytes is due the alignment of memory layout and ABI requirements
  printf("Size of long double: %zu bytes\n", sizeof(long double));
  // if LDBL_DIG is around 18, the long double is 80-bit extended precision internally.
  // If it’s 33-34, it represents 128-bit (quadruple precision).
  // If it’s 15, it's 64-bit (same as double).
  printf("Long double precision: %d digits\n", LDBL_DIG);

  float x = 6.75, nx = -6.75;
  printf("float encoding of %f: %x\n", x, *(unsigned int*)&x);
  printf("float encoding of %f: %x\n", nx, *(unsigned int*)&nx);

  float y = 8.75;
  printf("float encoding of %f: %x\n", y, *(unsigned int*)&y);

  return 0;
}
