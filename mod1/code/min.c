#include <stdio.h>
#include <float.h> // For FLT_MIN and FLT_TRUE_MIN
#include <math.h>
// gcc min.c -o min -lm
int main()
{
  // Smallest normalized number for float
  float smallest_normalized = FLT_MIN;
  printf("Smallest normalized number (float): %e\n", smallest_normalized);
  printf("Smallest normalized number (float): 2^(%g)\n", log2(smallest_normalized));

  // Smallest denormalized number for float
  float smallest_denormalized = FLT_TRUE_MIN;
  printf("Smallest denormalized number (float): %e\n", smallest_denormalized);
  printf("Smallest denormalized number (float): 2^(%g)\n", log2(smallest_denormalized));

  // 📝 find the smallest normalized number and denormalized number for
  // double, long double
  // DBL_MIN; DBL_TRUE_MIN; LDBL_MIN; LDBL_TRUE_MIN
  

  return 0;
}