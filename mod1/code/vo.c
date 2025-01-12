#include <stdio.h>
#include <limits.h>

int main()
{
  // Test case 1: Unsigned integer overflow
  unsigned int u1 = UINT_MAX; // Largest unsigned int value
  unsigned int v1 = 1;

  printf("Unsigned Integer Test:\n");
  printf("u1 = %u, v1 = %u\n", u1, v1);
  printf("u1 > 0 is true, but u1 + v1 > v1? %s\n", (u1 + v1 > v1) ? "true" : "false"); // Should fail due to overflow

  // Test case 2: Signed integer overflow
  int u2 = INT_MAX; // Largest signed int value
  int v2 = 1;

  // ⚠️Ubuntu clang version 14.0.0 gives expected result
  // but gcc version 11.4.0 does NOT
  printf("\nSigned Integer Test:\n");
  printf("u2 = %d, v2 = %d\n", u2, v2);
  printf("%d+%d = %d\n", u2, v2, u2+v2);
  printf("u2 > 0 is true, but u2 + v2 > v2? %s\n", ((int)(u2 + v2) > v2) ? "true" : "false"); // Should fail due to overflow

  // Test case 3: Unsigned integer multiplication
  unsigned int u3 = 2;
  unsigned int v3 = UINT_MAX / 2 + 1; // A value that causes overflow when multiplied by 2

  printf("\nUnsigned Integer Multiplication Test:\n");
  printf("u3 = %u, v3 = %u\n", u3, v3);
  printf("u3 > 0 and v3 > 0, but u3 * v3 > 0? %s\n", (u3 * v3 > 0) ? "true" : "false"); // Should fail due to overflow

  // Test case 4: Signed integer multiplication
  int u4 = INT_MIN; // Smallest signed int value
  int v4 = -1;

  printf("\nSigned Integer Multiplication Test:\n");
  printf("u4 = %d, v4 = %d\n", u4, v4);
  printf("u4 < 0 and v4 < 0, but u4 * v4 > 0? %s\n", (u4 * v4 > 0) ? "true" : "false"); // Should fail due to overflow

  return 0;
}