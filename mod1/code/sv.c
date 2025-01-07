#include <stdio.h>
#include <math.h>
// gcc sv.c -lm
int main()
{

  // 1. Generate infinity
  // 1.1 Dividing a non-zero number by zero results in infinity.
  float pos_inf = 1.0 / 0.0;
  float neg_inf = -1.0 / 0.0;
  printf("Positive Infinity: %f\n", pos_inf);
  printf("Negative Infinity: %f\n", neg_inf);

  // 1.2 Overflow
  float pos_inf2 = 1e38 * 1e38, neg_inf2= -1e38 * 1e38;
  printf("Positive Infinity: %f\n", pos_inf2);
  printf("Negative Infinity: %f\n", neg_inf2);

  // 1.3 Explicit Assignment
  float pos_inf3 = INFINITY;  // Positive infinity
  float neg_inf3 = -INFINITY; // Negative infinity
  printf("Positive Infinity: %f\n", pos_inf3);
  printf("Negative Infinity: %f\n", neg_inf3);

  // 2. Generate NaN
  // 2.1 Division of zero by zero.
  float nan = 0.0 / 0.0;
  printf("NaN: %f\n", nan);

  // 2.2 Square root of a negative number.
  float nan2 = sqrt(-3.14);
  printf("NaN: %f\n", nan2);

  // 2.3 Operations involving infinity (e.g., ∞−∞).
  float nan3 = INFINITY - INFINITY; // NaN
  printf("NaN: %f\n", nan3);

  // 2.4 Explicit Assignment:
  float nan4 = NAN; // NaN
  printf("NaN: %f\n", nan4);


  // Checking for infinity and NaN
  if (isinf(pos_inf))
  {
    printf("pos_inf is infinity\n");
  }
  if (isnan(nan))
  {
    printf("nan is NaN\n");
  }

  /* verify
  ∞+∞ = ∞
  ∞×∞ = ∞
  ∞−∞ = NaN
  ∞/∞ = NaN
  -∞ < any finite number < +∞
  Any operation involving NaN results in NaN.
    NaN + 1.2 → NaN
  NaN is not equal to anything, including itself.
    NaN == NaN → false  
  */ 

  return 0;
}
