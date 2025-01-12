#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
  // Test cases for each expression
  int x;
  float f;
  double d;

  // Expression 1: x == (int)(float) x
  // Casting `int` to `float` may cause rounding if `x` is large, 
  // and casting back to `int` may not restore the original value.
  x = INT_MAX; // Largest possible int value
  printf("1. x == (int)(float) x\n");
  printf("   x = %d, (int)(float) x = %d\n", x, (int)(float)x);
  printf("   Result: %s\n\n", x == (int)(float)x ? "True" : "False");

  // Expression 2: x == (int)(double) x
  // `double` has enough precision to represent all `int` values exactly, 
  // so casting back to `int` preserves the original value.
  x = INT_MAX; // Largest possible int value
  printf("2. x == (int)(double) x\n");
  printf("   x = %d, (int)(double) x = %d\n", x, (int)(double)x);
  printf("   Result: %s\n\n", x == (int)(double)x ? "True" : "False");

  // Expression 3: f == (float)(double) f
  // Casting `float` to `double` preserves the exact value, 
  // and casting back to `float` restores the original value.
  f = FLT_MAX; // Largest possible float value
  printf("3. f == (float)(double) f\n");
  printf("   f = %f, (float)(double) f = %f\n", f, (float)(double)f);
  printf("   Result: %s\n\n", f == (float)(double)f ? "True" : "False");

  // Expression 4: d == (double)(float) d
  // Casting `double` to `float` may lose precision or cause overflow, 
  // and casting back to `double` may not restore the original value.
  d = DBL_MAX; // Largest possible double value
  printf("4. d == (double)(float) d\n");
  printf("   d = %lf, (double)(float) d = %lf\n", d, (double)(float)d);
  printf("   Result: %s\n\n", d == (double)(float)d ? "True" : "False");

  // Expression 5: f == -(-f)
  // Negating a value twice returns the original value.
  f = 123.456f; // Arbitrary float value
  printf("5. f == -(-f)\n");
  printf("   f = %f, -(-f) = %f\n", f, -(-f));
  printf("   Result: %s\n\n", f == -(-f) ? "True" : "False");

  // Expression 6: 2/3 == 2/3.0
  // `2/3` is integer division (result: `0`), 
  // while `2/3.0` is floating-point division (result: `0.666...`).
  printf("6. 2/3 == 2/3.0\n");
  printf("   2/3 = %d, 2/3.0 = %f\n", 2 / 3, 2 / 3.0);
  printf("   Result: %s\n\n", 2 / 3 == 2 / 3.0 ? "True" : "False");

  // Expression 7: d < 0.0 ⇒ ((d*2) < 0.0)
  // Floating point is monotonic
  d = -1.0; // Negative double value
  printf("7. d < 0.0 ⇒ ((d*2) < 0.0)\n");
  printf("   d = %lf, d*2 = %lf\n", d, d * 2);
  printf("   Result: %s\n\n", (d < 0.0) == ((d * 2) < 0.0) ? "True" : "False");

  // Expression 8: d > f ⇒ -f > -d
  // Floating point is monotonic
  d = 100.0; // Arbitrary double value
  f = 50.0f; // Arbitrary float value
  printf("8. d > f ⇒ -f > -d\n");
  printf("   d = %lf, f = %f, -f = %f, -d = %lf\n", d, f, -f, -d);
  printf("   Result: %s\n\n", (d > f) == (-f > -d) ? "True" : "False");

  // Expression 9: d * d >= 0.0
  // Floating point is monotonic
  d = -123.456; // Arbitrary double value
  printf("9. d * d >= 0.0\n");
  printf("   d = %lf, d * d = %lf\n", d, d * d);
  printf("   Result: %s\n\n", d * d >= 0.0 ? "True" : "False");

  // Expression 10: (d + f) - d == f
  // If `d` is much larger than `f`, adding `f` to `d` may result in a loss of precision, 
  // making `(d + f) - d` not equal to `f`
  d = 1.0e20; // Large double value
  f = 1.0f;   // Small float value
  printf("10. (d + f) - d == f\n");
  printf("   d = %lf, f = %f, (d + f) - d = %lf\n", d, f, (d + f) - d);
  printf("   Result: %s\n\n", (d + f) - d == f ? "True" : "False");

  return 0;
}