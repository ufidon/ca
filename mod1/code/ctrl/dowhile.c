#include <stdio.h>

// (a) C code with do-while loop
long fact_do(long n)
{
  long result = 1;
  do
  {
    result *= n;
    n = n - 1;
  } while (n > 1);
  return result;
}

// (b) Equivalent goto version
long fact_do_goto(long n)
{
  long result = 1;
loop:
  result *= n;
  n = n - 1;
  if (n > 1)
    goto loop;
  return result;
}

// Main function to test both implementations
int main()
{
  long n;

  // Test case 1
  n = 5;
  printf("fact_do(%ld) = %ld\n", n, fact_do(n));
  printf("fact_do_goto(%ld) = %ld\n", n, fact_do_goto(n));

  // Test case 2
  n = 7;
  printf("fact_do(%ld) = %ld\n", n, fact_do(n));
  printf("fact_do_goto(%ld) = %ld\n", n, fact_do_goto(n));

  // Test case 3
  n = 1;
  printf("fact_do(%ld) = %ld\n", n, fact_do(n));
  printf("fact_do_goto(%ld) = %ld\n", n, fact_do_goto(n));

  return 0;
}

// 📝 convert do while to goto
long dw_loop(long x) {
    long y = x * x;
    long *p = &x;
    long n = 2 * x;
    do {
        x += y;
        (*p)++;
        n--;
    } while (n > 0);
    return x;
}