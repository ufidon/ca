#include <stdio.h>

// Function to compare two long values and return 1 if a < b, otherwise 0
int comp(long a, long b)
{
/* SetX	Instructions set single byte based on combination of condition codes
- one of addressable byte registers such as `al`
  - High-order bytes must be cleared to generate 32-bit or 64-bit result
  - typically use `movzbl` to finish job
- 32-bit instructions also set upper 32 bits to 0
*/  
  return a < b;
}

int main()
{
  long a = 10;
  long b = 20;

  // Call the comparison function
  int result = comp(a, b);

  // Print the result
  printf("Result of a < b: %d\n", result);

  return 0;
}

/*
📝 Try all C integer types and relational operators
- 1. explore the generated code
- 2. redo with t2 = 0
*/
#define COMP <= // ==, !=, <, >, >=
typedef long T1;
typedef char T2;

int xcomp(T1 t1, T2 t2){
  return t1 COMP t2;
}