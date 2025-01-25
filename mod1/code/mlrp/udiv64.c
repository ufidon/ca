#include <stdio.h>

// Function to compute quotient and remainder for unsigned integers
void uremdiv(unsigned long x, unsigned long y, unsigned long *qp, unsigned long *rp)
{
  unsigned long q = x / y; // Compute quotient
  unsigned long r = x % y; // Compute remainder
  *qp = q;                 // Store quotient
  *rp = r;                 // Store remainder
}

int main()
{
  unsigned long x = 12345678901234567890UL; // Dividend
  unsigned long y = 9876543210987654321UL;  // Divisor
  unsigned long q, r;                     // Quotient and remainder

  // Call uremdiv to compute quotient and remainder
  uremdiv(x, y, &q, &r);

  // Print results
  printf("Dividend: %lu\n", x);
  printf("Divisor:  %lu\n", y);
  printf("Quotient: %lu\n", q);
  printf("Remainder: %lu\n", r);

  return 0;
}