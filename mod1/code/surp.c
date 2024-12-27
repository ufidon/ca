#include <stdio.h>
#include <limits.h>

int main()
{
  // Constants
  int tmin = INT_MIN; // -2147483648
  int tmax = INT_MAX; //  2147483647
  unsigned int u_tmax = (unsigned int)INT_MAX;
  unsigned int u_tmin = (unsigned int)INT_MIN; // 2147483648U

  // Evaluations
  printf("Expression Evaluation (Signed and Unsigned Casting Surprises)\n\n");

  printf("0 == 0U : %d\n", 0 == 0U); // True
  printf("-1 < 0  : %d\n", -1 < 0);  // True
  printf("-1 < 0U : %d\n", -1 < 0U); // False (Implicit cast of -1 to unsigned -> large value)

  printf("tmax > tmin : %d\n", tmax > tmin);         // True
  printf("u_tmax > tmin : %d\n", u_tmax > tmin);     // False (tmin is implicitly casted to unsigned 2147483648U)
  printf("u_tmax > u_tmin : %d\n", u_tmax > u_tmin); // False (2147483647U < 2147483648U)

  printf("-1 > -2 : %d\n", -1 > -2);                     // True
  printf("(unsigned)-1 > -2 : %d\n", (unsigned)-1 > -2); // True (-1 cast to large unsigned)

  printf("tmax < u_tmin : %d\n", tmax < u_tmin);           // True (2147483647 < 2147483648U)
  printf("tmax < (int)u_tmin : %d\n", tmax < (int)u_tmin); // False ((int)2147483648U -> Overflow)

  // Debugging and Boundary Testing
  printf("\nBoundary Testing:\n");
  printf("tmin : %d\n", tmin);
  printf("tmax : %d\n", tmax);
  printf("u_tmin : %u\n", u_tmin);
  printf("u_tmax : %u\n", u_tmax);

  return 0;
}
