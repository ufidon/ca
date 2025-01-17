#include <stdio.h>

int main()
{
  // Variables for demonstration
  int a = 10, b = 4;
  unsigned int c = 0b1010; // Binary 1010 (10 in decimal)
  unsigned int d = 0b1100; // Binary 1100 (12 in decimal)

  // Arithmetic Operations
  printf("=== Arithmetic Operations ===\n");
  printf("a = %d, b = %d\n", a, b);
  printf("a + b = %d\n", a + b);  // Addition
  printf("a - b = %d\n", a - b);  // Subtraction
  printf("a * b = %d\n", a * b);  // Multiplication
  printf("a / b = %d\n", a / b);  // Division
  printf("a %% b = %d\n", a % b); // Modulus
  printf("++a = %d\n", ++a);      // Pre-increment
  printf("--b = %d\n", --b);      // Pre-decrement

  // Logical Operations
  printf("\n=== Logical Operations ===\n");
  printf("a = %d, b = %d\n", a, b);
  printf("a && b = %d\n", a && b); // Logical AND
  printf("a || b = %d\n", a || b); // Logical OR
  printf("!a = %d\n", !a);         // Logical NOT

  // Bitwise Operations
  printf("\n=== Bitwise Operations ===\n");
  printf("c = 0b1010 (10), d = 0b1100 (12)\n");
  printf("c & d = 0b%04b\n", c & d);         // Bitwise AND
  printf("c | d = 0b%04b\n", c | d);         // Bitwise OR
  printf("c ^ d = 0b%04b\n", c ^ d);         // Bitwise XOR
  printf("~c = 0b%04b\n", (unsigned int)~c); // Bitwise NOT
  printf("c << 1 = 0b%04b\n", c << 1);       // Left shift
  printf("d >> 1 = 0b%04b\n", d >> 1);       // Right shift

  // Bit Manipulation
  printf("\n=== Bit Manipulation ===\n");
  printf("Set bit 2 of c: 0b%04b\n", c | (1 << 2));    // Set bit 2
  printf("Clear bit 3 of d: 0b%04b\n", d & ~(1 << 3)); // Clear bit 3
  printf("Toggle bit 1 of c: 0b%04b\n", c ^ (1 << 1)); // Toggle bit 1

  return 0;
}