#include "vector.h"

int multcnt = 0;

void multvec(int *x, int *y, int *z, int n)
{
  multcnt++;
  for (int i = 0; i < n; i++)
  {
    z[i] = x[i] * y[i];
  }
}
