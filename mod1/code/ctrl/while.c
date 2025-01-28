#include <stdio.h>

// (a) C code for factorial using while loop
long fact_while(long n)
{
  long result = 1;
  while (n > 1)
  {
    result *= n;
    n = n - 1;
  }
  return result;
}

// (b) Equivalent goto version of the while loop factorial
long fact_while_jm_goto(long n)
{
  long result = 1;
  goto test;

loop:
  result *= n;
  n = n - 1;

test:
  if (n > 1)
    goto loop;
  return result;
}

// (c) C code for factorial using do-while loop
long fact_do_while(long n)
{
  long result = 1;
  if (n <= 1)
  {
    return result; // Handle edge case where n is 0 or 1
  }
  do
  {
    result *= n;
    n = n - 1;
  } while (n > 1);
  return result;
}

// (d) Equivalent goto version of the while loop factorial (corrected version)
long fact_while_gd_goto(long n)
{
  long result = 1;
  if (n <= 1)
    goto done;

loop:
  result *= n;
  n = n - 1;
  if (n != 1)
    goto loop;

done:
  return result;
}

int main()
{
  long n = 5;

  printf("Factorial using while loop: %ld\n", fact_while(n));
  printf("Factorial using goto (jm_goto): %ld\n", fact_while_jm_goto(n));
  printf("Factorial using do-while loop: %ld\n", fact_do_while(n));
  printf("Factorial using goto (gd_goto): %ld\n", fact_while_gd_goto(n));

  return 0;
}