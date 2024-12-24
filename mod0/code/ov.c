#include <stdio.h>
#include <limits.h>
#include <float.h>

// 📝: try various value limits

int main(){
  // 1. Is x² ≥ 0?
  int x = INT_MAX;
  printf("x=%d, x²=%d\n", x, x*x);

  float y = FLT_MAX;
  printf("y=%f, y²=%f\n", y, y*y);

  // 2. Is (x + y) + z = x + (y + z)?
  int x1 = INT_MAX, y1 = INT_MAX, z1 = INT_MIN;
  printf("(x1 + y1) + z1=%d, x1 + (y1 + z1)=%d\n", (x1 + y1) + z1, x1 + (y1 + z1));

  float x2 = 1e20, y2 = -1e20, z2 = 3.14159;
  printf("(x2 + y2) + z2=%f, x2 + (y2 + z2)=%f\n", (x2 + y2) + z2, x2 + (y2 + z2));

  return 0;
}