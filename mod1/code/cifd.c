#include <stdio.h>
#include <limits.h> // For INT_MIN

int main()
{
  // 1. From int to float: No overflow, but rounding may occur
  int intVal = 123456789;         // A large integer
  float floatVal = (float)intVal; // Cast int to float
  printf("1. int to float:\n");
  printf("   int: %d\n", intVal);
  printf("   float: %f (may be rounded)\n\n", floatVal);

  // 2. From int or float to double: Exact value preserved
  double doubleVal1 = (double)intVal;   // Cast int to double
  double doubleVal2 = (double)floatVal; // Cast float to double
  printf("2. int or float to double:\n");
  printf("   int to double: %lf (exact)\n", doubleVal1);
  printf("   float to double: %lf (exact)\n\n", doubleVal2);

  // 3. From double to float: Possible overflow or rounding
  double largeDouble = 1.0e38;                // A large double value
  float floatFromDouble = (float)largeDouble; // Cast double to float
  printf("3. double to float:\n");
  printf("   double: %lf\n", largeDouble);
  printf("   float:  %f (may overflow or round)\n\n", floatFromDouble);

  // 4. From float or double to int: Rounded toward zero, possible overflow
  float floatVal2 = 1.999f;            // A float value
  double doubleVal3 = -1.999;          // A double value
  int intFromFloat = (int)floatVal2;   // Cast float to int
  int intFromDouble = (int)doubleVal3; // Cast double to int
  printf("4. float or double to int:\n");
  printf("   float:  %f -> int: %d (rounded toward zero)\n", floatVal2, intFromFloat);
  printf("   double: %lf -> int: %d (rounded toward zero)\n", doubleVal3, intFromDouble);

  // Demonstrate overflow when casting from double to int
  double veryLargeDouble = 1.0e20;               // A very large double value
  int intFromLargeDouble = (int)veryLargeDouble; // Cast double to int (overflow)
  printf("   double: %lf -> int: %d (overflow, result is INT_MIN)\n", veryLargeDouble, intFromLargeDouble);

  return 0;
}