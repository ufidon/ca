#include <stdio.h>

void switch_eg(long x, long n, long *dest)
{
  long val = x;
  switch (n)
  {
  case 100:
    val *= 13;
    break;
  case 102:
    val += 10;
    // Fall through to the next case
  case 103:
    val += 11;
    break;
  case 104:
  case 106:
    val *= val;
    break;
  default:
    val = 0;
    break;
  }
  *dest = val;
}

void switch_eg_impl(long x, long n, long *dest)
{
  // Table of code pointers
  static void *jt[7] = {
      &&loc_A, &&loc_def, &&loc_B, &&loc_C, &&loc_D, &&loc_def, &&loc_D};
  unsigned long index = n - 100;
  long val = x;

  if (index > 6)
  {
    goto loc_def; // Default case if index is out of bounds
  }

  // Jump to the appropriate location based on the value of n
  goto *jt[index];

loc_A: // Case 100
  val *= 13;
  goto done;

loc_B: // Case 102
  val += 10;
  goto loc_C; // Fall through to next case

loc_C: // Case 103
  val += 11;
  goto done;

loc_D: // Cases 104, 106
  val = x * x;
  goto done;

loc_def: // Default case
  val = 0;

done:
  *dest = val;
}

int main()
{
  long result;

  // Demonstrate switch statement
  switch_eg(5, 102, &result); // Example call
  printf("Result using switch statement: %ld\n", result);

  // Demonstrate extended C (jump table) version
  switch_eg_impl(5, 102, &result); // Example call
  printf("Result using jump table: %ld\n", result);

  return 0;
}
