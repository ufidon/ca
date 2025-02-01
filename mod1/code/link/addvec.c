#include "vector.h"

int addcnt = 0;

void addvec(int *x, int *y, int *z, int n)
{
  addcnt++;
  for (int i = 0; i < n; i++)
  {
    z[i] = x[i] + y[i];
  }
}
