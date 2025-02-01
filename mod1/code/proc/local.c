#include <stdio.h>

// Function to swap values and add them
long swap_add(long *xp, long *yp)
{
  long x = *xp;
  long y = *yp;

  *xp = y; // Swap values
  *yp = x;

  return x + y; // Return the sum
}

// Function demonstrating the swap_add call and difference computation
long caller()
{
  long arg1 = 534;
  long arg2 = 1057;

  // Call swap_add to swap and add values
  long sum = swap_add(&arg1, &arg2);

  // Calculate the difference between the updated values
  long diff = arg1 - arg2;

  return sum * diff; // Return the product of sum and difference
}

// Function demonstrating the proc call with various argument types
void proc(long a1, long *a1p, int a2, int *a2p, short a3, short *a3p, char a4, char *a4p)
{
  *a1p += a1;
  *a2p += a2;
  *a3p += a3;
  *a4p += a4;
}

// Function to call proc with some arguments
long call_proc()
{
  long x1 = 1;
  int x2 = 2;
  short x3 = 3;
  char x4 = 4;

  // Call proc to modify values
  proc(x1, &x1, x2, &x2, x3, &x3, x4, &x4);

  // Return the result of the calculation
  return (x1 + x2) * (x3 - x4);
}

int main()
{
  // Calling the functions and displaying results
  printf("Caller result: %ld\n", caller());
  printf("Call Proc result: %ld\n", call_proc());

  return 0;
}
