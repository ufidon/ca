#include <stdio.h>

long arith2(long x, long y, long z)
{
  long t1 = x | y;   // OR operation: t1 = x | y
  long t2 = t1 >> 3; // Arithmetic right shift by 3: t2 = t1 >> 3
  long t3 = ~t2;     // Bitwise NOT: t3 = ~t2
  long t4 = z - t3;  // Subtraction: t4 = z - t3
  return t4;         // Return t4
}

int main()
{
  long x = 0x12345678; // Example input
  long y = 0x87654321; // Example input
  long z = 0xABCDEF01; // Example input

  long result = arith2(x, y, z);
  printf("Result: 0x%lx\n", result); // Print the result

  return 0;
}