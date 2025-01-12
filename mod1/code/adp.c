#include <stdio.h>
#include <math.h>

int main()
{
  printf("Demonstrating Properties of Floating-Point Addition:\n\n");
  // Variables for testing
  double a = 3.14, b = 1e10, c = -1e10, zero = 0.0;

  // 1. Closed Under Addition (with Infinity and NaN)
  double inf = 1e308 + 1e308; // Overflow to Infinity
  double nan = inf - inf;     // NaN from undefined operation
  printf("1. Closed Under Addition:\n");
  printf("   1e308 + 1e308 = %f (Infinity)\n", inf);
  printf("   Infinity - Infinity = %f (NaN)\n\n", nan);

  // 2. Commutative Property
  double comm1 = a + b;
  double comm2 = b + a;
  printf("2. Commutative Property:\n");
  printf("   a + b = %f, b + a = %f\n\n", comm1, comm2);

  // 3. Non-Associativity
  double assoc1 = (a + b) + c; // (3.14 + 1e10) - 1e10
  double assoc2 = a + (b + c); // 3.14 + (1e10 - 1e10)
  printf("3. Non-Associativity:\n");
  printf("   (a + b) + c = %f\n", assoc1);
  printf("   a + (b + c) = %f\n\n", assoc2);

  // 4. Additive Identity (0)
  double identity = a + zero;
  printf("4. Additive Identity:\n");
  printf("   a + 0 = %f\n\n", identity);

  // 5. Additive Inverses
  double inverse = a + (-a);
  double inf_inverse = inf + (-inf); // Infinity - Infinity
  printf("5. Additive Inverses:\n");
  printf("   a + (-a) = %f\n", inverse);
  printf("   Infinity - Infinity = %f (NaN)\n\n", inf_inverse);

  // 6. Monotonicity
  double x = 5.0, y = 3.0, z = 2.0; // x > y
  double mono1 = x + z;
  double mono2 = y + z;
  printf("6. Monotonicity:\n");
  printf("   If x >= y, then x + z >= y + z:\n");
  printf("   %g >= %g, then %g + %g = %g  >= %g  + %g = %g :\n", x, y, x, z, mono1, y, z, mono2);
  return 0;
}
