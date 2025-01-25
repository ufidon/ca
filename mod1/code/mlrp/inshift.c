#include <stdio.h>

// Function to perform left shift by 4 and arithmetic right shift by n
long shift_left4_rightn(long x, long n)
{
  long result;

  // Inline assembly for shift operations
  __asm__ volatile(
      "movq %1, %%rax\n\t"   // Move x into %rax
      "salq $4, %%rax\n\t"   // Left shift %rax by 4 (x <<= 4)
      "movq %2, %%rcx\n\t"   // Move n into %rcx
      "sarq %%cl, %%rax\n\t" // Arithmetic right shift %rax by %cl (x >>= n)
      "movq %%rax, %0"       // Move result back to 'result'
      : "=r"(result)         // Output operand
      : "r"(x), "r"(n)       // Input operands
      : "%rax", "%rcx"       // Clobbered registers
  );

  return result;
}

// Function to perform arithmetic operations
long arith(long x, long y, long z)
{
  long result;

  // Inline assembly for arithmetic operations
  __asm__ volatile(
      "xorq %1, %0\n\t"             // t1 = x ^ y (x - y, assuming y is a negative of itself)
      "leaq (%2, %2, 2), %%rax\n\t" // t2 = 3 * z
      "salq $4, %%rax\n\t"          // t2 = 16 * (3 * z) = 48 * z
      "andq $0x0F0F0F0F, %0\n\t"    // t3 = t1 & 0x0F0F0F0F
      "subq %0, %%rax\n\t"          // t4 = t2 - t3
      "movq %%rax, %0"              // Return t4
      : "=r"(result)                // Output operand
      : "r"(x), "r"(y), "r"(z)      // Input operands
      : "%rax"                      // Clobbered registers
  );

  return result;
}

int main()
{
  // Test shift_left4_rightn
  long x = 0x12345678; // Example input
  long n = 8;          // Example shift amount
  long shift_result = shift_left4_rightn(x, n);
  printf("shift_left4_rightn Result: 0x%lx\n", shift_result);

  // Test arith
  long a = 0x12345678; // Example input
  long b = 0x87654321; // Example input
  long c = 0xABCDEF01; // Example input
  long arith_result = arith(a, b, c);
  printf("arith Result: 0x%lx\n", arith_result);

  return 0;
}