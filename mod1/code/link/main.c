#include <stdio.h>

int sum(int a, int b);
void print_greeting();
extern int buf[];
void swap(void);

int main()
{
  print_greeting();
  
  int result = sum(5, 3);
  printf("Sum: %d\n", result);

  swap();
  printf("buf[0] = %d, buf[1] = %d\n", buf[0], buf[1]);

  return 0;
}
