#include <stdio.h>

// gcc  -fno-if-conversion -Og -S  -o absdiff.s absdiff.c
// 

// Helper function to compute absolute value
long abs_value(long x)
{
  if (x < 0)
  {
    return -x;
  }
  return x;
}

// Function using if...else to calculate absolute difference
long abs_difference_if_else(long a, long b)
{
  a = abs_value(a);
  b = abs_value(b);
  if (a > b)
  {
    return a - b;
  }
  else
  {
    return b - a;
  }
}

// Function using goto to calculate absolute difference
long abs_difference_goto(long a, long b)
{
  long result;
  a = abs_value(a);
  b = abs_value(b);

// Using goto for control flow
check_a_bigger:
  if (a > b)
  {
    result = a - b;
    goto end;
  }

  result = b - a;

end:
  return result;
}

int main()
{
  long a = 3, b = -3;

  // Using the function with if...else
  printf("Absolute difference (if...else): %ld\n", abs_difference_if_else(a, b));

  // Using the function with goto
  printf("Absolute difference (goto): %ld\n", abs_difference_goto(a, b));

  return 0;
}
