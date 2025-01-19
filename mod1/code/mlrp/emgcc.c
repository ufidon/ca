#include <stdio.h>

int main()
{
  int a = 10, b = 4;
  int result;

  // Arithmetic Operations
  printf("=== Arithmetic Operations ===\n");
  printf("a = %d, b = %d\n", a, b);

  // Addition
  asm("addl %1, %0" : "=r"(result) : "r"(a), "0"(b));
  printf("a + b = %d\n", result);

  // Subtraction
  asm("subl %1, %0" : "=r"(result) : "r"(a), "0"(b));
  printf("a - b = %d\n", result);

  // Multiplication
  asm("imull %1, %0" : "=r"(result) : "r"(a), "0"(b));
  printf("a * b = %d\n", result);

  // Division
  asm("movl %1, %%eax;"
      "movl %2, %%ebx;"
      "cltd;"
      "idivl %%ebx;"
      "movl %%eax, %0;" : "=r"(result) : "r"(a), "r"(b) : "%eax", "%ebx", "%edx");
  printf("a / b = %d\n", result);

  // Modulus
  asm("movl %1, %%eax;"
      "movl %2, %%ebx;"
      "cltd;"
      "idivl %%ebx;"
      "movl %%edx, %0;" : "=r"(result) : "r"(a), "r"(b) : "%eax", "%ebx", "%edx");
  printf("a %% b = %d\n", result);

  // Increment
  asm("incl %0" : "=r"(a) : "0"(a));
  printf("++a = %d\n", a);

  // Decrement
  asm("decl %0" : "=r"(b) : "0"(b));
  printf("--b = %d\n", b);

  // Logical Operations
  printf("\n=== Logical Operations ===\n");
  printf("a = %d, b = %d\n", a, b);

  // Bitwise AND
  asm("andl %1, %0" : "=r"(result) : "r"(a), "0"(b));
  printf("a & b = %d\n", result);

  // Bitwise OR
  asm("orl %1, %0" : "=r"(result) : "r"(a), "0"(b));
  printf("a | b = %d\n", result);

  // Bitwise XOR
  asm("xorl %1, %0" : "=r"(result) : "r"(a), "0"(b));
  printf("a ^ b = %d\n", result);

  // Bitwise NOT
  asm("notl %0" : "=r"(result) : "0"(a));
  printf("~a = %d\n", result);

  // Bitwise Shift Left
  asm("shll $2, %0" : "=r"(result) : "0"(a));
  printf("a << 2 = %d\n", result);

  // Bitwise Shift Right
  asm("shrl $1, %0" : "=r"(result) : "0"(b));
  printf("b >> 1 = %d\n", result);

  // Bitwise Rotate Left
  asm("roll $1, %0" : "=r"(result) : "0"(a));
  printf("a <<< 1 = %d\n", result);

  // Bitwise Rotate Right
  asm("rorl $1, %0" : "=r"(result) : "0"(b));
  printf("b >>> 1 = %d\n", result);

  return 0;
}