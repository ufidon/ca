#include <stdio.h>
#include "vector.h"

int main()
{
  int x[] = {1, 2, 3, 4};
  int y[] = {5, 6, 7, 8};
  int z[4];

  addvec(x, y, z, 4);
  printf("Sum: [%d %d %d %d] (Called %d times)\n", z[0], z[1], z[2], z[3], addcnt);

  multvec(x, y, z, 4);
  printf("Product: [%d %d %d %d] (Called %d times)\n", z[0], z[1], z[2], z[3], multcnt);

  return 0;
}
