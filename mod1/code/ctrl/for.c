#include <stdio.h>

// Function using a for loop
long fact_for(long n)
{
  long i;
  long result = 1;
  for (i = 2; i <= n; i++)
  {
    result *= i;
  }
  return result;
}

// Function using a while loop
long fact_for_while(long n)
{
  long i = 2;
  long result = 1;
  while (i <= n)
  {
    result *= i;
    i++;
  }
  return result;
}

// Function using a goto statement
long fact_for_jm_goto(long n)
{
  long i = 2;
  long result = 1;

// Use of goto statement
test:
  if (i <= n)
  {
    result *= i;
    i++;
    goto test;
  }
  return result;
}

int main()
{
  long num = 5; // Example input for factorial computation

  printf("Factorial using for loop: %ld\n", fact_for(num));
  printf("Factorial using while loop: %ld\n", fact_for_while(num));
  printf("Factorial using goto: %ld\n", fact_for_jm_goto(num));

  return 0;
}
