#include <stdio.h>
// gcc  -fno-if-conversion -Og -S  -o dist.s dist.c
// Function to calculate the distance between two points using if...else
long dist_if_else(long p1, long p2)
{
  if (p1 > p2)
  {
    return p1 - p2;
  }
  else
  {
    return p2 - p1;
  }
}

// Function to calculate the distance between two points using goto
long dist_goto(long p1, long p2)
{
  long distance;

// Using goto for control flow to calculate the distance
check_p1_greater:
  if (p1 > p2)
  {
    distance = p1 - p2;
    goto end;
  }

  distance = p2 - p1;

end:
  return distance;
}

int main()
{
  long p1 = 10, p2 = 5;

  // Using the function with if...else to calculate the distance
  printf("Distance (if...else): %ld\n", dist_if_else(p1, p2));

  // Using the function with goto to calculate the distance
  printf("Distance (goto): %ld\n", dist_goto(p1, p2));

  return 0;
}

/*
 📝 Rewrite `if⋯else` with `goto`
*/

void valid(long a, long *p){
  if(p && a > *p)
    *p = a;
}
