#include <stdio.h>
#include <math.h> // For NaN and INFINITY constants

typedef enum
{
  NEG,
  ZERO,
  POS,
  OTHER
} range_t;

range_t find_range(float x)
{
  range_t result;

  if (x < 0)
  {
    result = NEG;
  }
  else if (x == 0)
  {
    result = ZERO;
  }
  else if (x > 0)
  {
    result = POS;
  }
  else
  {
    result = OTHER; // This case is for NaN
  }

  return result;
}

// Generalized function to print the range result
void print_range_result(float x, range_t result)
{
  printf("For x = %.2f, result: ", x);
  switch (result)
  {
  case NEG:
    printf("NEG\n");
    break;
  case ZERO:
    printf("ZERO\n");
    break;
  case POS:
    printf("POS\n");
    break;
  case OTHER:
    printf("OTHER\n");
    break;
  }
}

int main()
{
  // Example values for each type:
  float x_neg = -3.5f; // NEG
  float x_zero = 0.0f; // ZERO
  float x_pos = 4.2f;  // POS
  float x_other = NAN; // OTHER (NaN example)

  // Check each value and print result using the generalized function
  print_range_result(x_neg, find_range(x_neg));
  print_range_result(x_zero, find_range(x_zero));
  print_range_result(x_pos, find_range(x_pos));
  print_range_result(x_other, find_range(x_other));

  return 0;
}
