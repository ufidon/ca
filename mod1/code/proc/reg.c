#include <stdio.h>

// Callee function (Q)
void Q(int *x, int *y)
{
  *x += 10; // Modify the first argument (callee-saved)
  *y *= 2;  // Modify the second argument (caller-saved)
}

// Caller function (P)
void P()
{
  int x = 5; // Local variable
  int y = 3; // Local variable

  // Save callee-saved registers (simulate by saving x and y)
  int saved_x = x;
  int saved_y = y;

  // Call function Q (callee)
  Q(&x, &y);

  // After the call, x is callee-saved, so it's safe
  // However, y is caller-saved, so we need to restore it
  y = saved_y;

  // Print the results
  printf("After Q, x = %d, y = %d\n", x, y);
}

int main()
{
  P(); // Call the function P
  return 0;
}
