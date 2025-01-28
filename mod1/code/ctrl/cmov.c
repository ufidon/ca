#include <stdio.h>

// gcc -o cmov cmov.c
// objdump -d cmov

// Original C code using if-else
long absdiff(long x, long y)
{
  long result;
  if (x < y)
    result = y - x;
  else
    result = x - y;
  return result;
}

// Implementation using conditional assignment
long cmovdiff(long x, long y)
{
  long rval = y - x;
  long eval = x - y;
  long ntest = x >= y;

  // Conditional move equivalent:
  if (ntest)
    rval = eval;

  return rval;
}

int main()
{
  long x = 10, y = 15;

  // Using the original if-else function
  long result_if_else = absdiff(x, y);
  printf("Absolute difference (if-else): %ld\n", result_if_else);

  // Using the conditional assignment function
  long result_cmov = cmovdiff(x, y);
  printf("Absolute difference (cmov-like): %ld\n", result_cmov);

  // Verify that both implementations produce the same result
  if (result_if_else == result_cmov)
  {
    printf("Both functions produce the same result.\n");
  }
  else
  {
    printf("Functions produce different results.\n");
  }

  return 0;
}
