#include <stdio.h>

// Function to compute t = x + 4*y + 12*z using inline assembly
long scale(long x, long y, long z)
{
  long t;

  // Inline assembly to compute t = x + 4*y + 12*z using leaq
  __asm__ volatile(
      "leaq (%1, %2, 4), %%rax\n\t" // rax = x + 4*y
      "leaq (%3, %3, 2), %%rdx\n\t" // rdx = z + 2*z = 3*z
      "leaq (%%rax, %%rdx, 4), %0"  // t = rax + 4*rdx = x + 4*y + 12*z
      : "=r"(t)                     // Output operand: t
      : "r"(x), "r"(y), "r"(z)      // Input operands: x, y, z
      : "%rax", "%rdx"              // Clobbered registers
  );

  return t;
}

int main()
{
  long x = 2, y = 3, z = 4;
  long result = scale(x, y, z);

  printf("Result: %ld\n", result); // Expected output: 2 + 4*3 + 12*4 = 2 + 12 + 48 = 62

  /* 📝 Find the C code for
  scale2:
      ; x in %rdi , y in %rsi , z in %rdx
      leaq  (%rdi,%rdi,4), %rax    ; rax = x + 4*x = 5*x
      leaq  (%rax,%rsi,2), %rax    ; rax = rax + 2*y = 5*x + 2*y
      leaq  (%rax,%rdx,8), %rax    ; rax = rax + 8*z = 5*x + 2*y + 8*z
      ret

  long scale2(long x, long y, long z) {
      // x in %rdi , y in %rsi , z in %rdx
      // Missing expression
      return t;
  }
  */

  return 0;
}