#include <stdio.h>

// Function to compute quotient and remainder
void remdiv(long x, long y, long *qp, long *rp)
{
  long q = x / y; // Compute quotient
  long r = x % y; // Compute remainder
  *qp = q;        // Store quotient
  *rp = r;        // Store remainder
}

int main()
{
  long x = 1234567890123456789; // Dividend
  long y = 987654321098765432;  // Divisor
  long q, r;                    // Quotient and remainder

  // Call remdiv to compute quotient and remainder
  remdiv(x, y, &q, &r);

  // Print results
  printf("Dividend: %ld\n", x);
  printf("Divisor:  %ld\n", y);
  printf("Quotient: %ld\n", q);
  printf("Remainder: %ld\n", r);

  return 0;
}