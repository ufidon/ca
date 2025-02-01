
#include <stdio.h>

int sum(int a, int b)
{
  return a + b;
}

void print_greeting()
{
  printf("Hello for funs!\n");
}

int buf[2] = {1, 2};
int *bufp0 = &buf[0];
int *bufp1 = &buf[1];

void swap(void)
{
  int temp;

  temp = *bufp0;
  *bufp0 = *bufp1;
  *bufp1 = temp;
}
