#include <stdio.h>
/*
- x86-64 passes up to six arguments via registers, based on data size.
  - Smaller arguments use parts of 64-bit registers (e.g., `%edi` for 32-bit).
- Arguments beyond six are passed on the stack, allocated in the caller's stack frame.
  - Stack arguments are rounded to multiples of eight, and called functions access them via registers or stack.

| **size(bits)\argument#** | **1**| **2** | **3**| **4**| **5** | **6**|
|---------|------|-------|------|------|------|------|
| **64**  | %rdi | %rsi  | %rdx | %rcx | %r8  | %r9  |
| **32**  | %edi | %esi  | %edx | %ecx | %r8d | %r9d |
| **16**  | %di  | %si   | %dx  | %ex  | %r8w | %r9w |
| **8**   | %dil | %sil  | %dl  | %cl  | %r8b | %r9b |
*/
// Function definition
void proc(long a1, long *a1p, int a2, int *a2p, short a3, short *a3p, char a4, char *a4p)
{
  // Perform the specified operations
  *a1p += a1;
  *a2p += a2;
  *a3p += a3;
  *a4p += a4;
}

int main()
{
  // Declare variables
  long a1 = 10, a1p = 5;
  int a2 = 20, a2p = 15;
  short a3 = 30, a3p = 25;
  char a4 = 40, a4p = 35;

  // Print values before calling proc
  printf("Before proc:\n");
  printf("a1p: %ld, a2p: %d, a3p: %d, a4p: %d\n", a1p, a2p, a3p, a4p);

  // Call the proc function
  proc(a1, &a1p, a2, &a2p, a3, &a3p, a4, &a4p);

  // Print values after calling proc
  printf("\nAfter proc:\n");
  printf("a1p: %ld, a2p: %d, a3p: %d, a4p: %d\n", a1p, a2p, a3p, a4p);

  return 0;
}
