#include <stdio.h>
#include <limits.h>

// unsigned char in C wraps around on overflow and underflow (modulo 256 arithmetic).
// - Division by zero is undefined and can lead to program crashes.
// - Use this behavior for low-level operations, but handle edge cases carefully to avoid unexpected results.

void print_binary(char *label, void *arr, int size)
{
  char *p = (char*)arr;
  printf("%-10s: ", label);
  for (int i = 0; i < size; i++)
  {
    for (int j = sizeof(char) * 8 - 1; j >= 0; j--)
    {    // Iterate over bits in reverse order
      printf("%d", (p[i] >> j) & 1); // Extract and print each bit
    }
    printf(" ");
  }
  printf("\n");
}

void demonstrate_addition()
{
  unsigned char a = 200;
  unsigned char b = 60;
  unsigned char result = a + b;

  printf("Addition (Normal Case): 100 + 50 = %hhu\n", (unsigned char)(100 + 50));
  printf("Addition (Overflow): %hhu + %hhu = %hhu (Wraparound)\n", a, b, result);
  // (Wraparound, since 260 % 256 = 4)
  print_binary("a", &a, sizeof(char));
  print_binary("b", &b, sizeof(char));
  print_binary("result", &result, sizeof(char));
  printf("----------------------------------------------\n");  
}

void demonstrate_subtraction()
{
  unsigned char a = 50;
  unsigned char b = 100;
  unsigned char result = a - b;

  printf("Subtraction (Normal Case): 100 - 50 = %hhu\n", (unsigned char)(100 - 50));
  printf("Subtraction (Underflow): %hhu - %hhu = %hhu (Wraparound)\n", a, b, result);
  // (Wraparound, since -50 + 256 = 206)
  print_binary("a", &a, sizeof(char));
  print_binary("b", &b, sizeof(char));
  print_binary("result", &result, sizeof(char));
  printf("----------------------------------------------\n");    
}

void demonstrate_multiplication()
{
  unsigned char a = 20;
  unsigned char b = 13;
  unsigned char result = a * b;

  printf("Multiplication (Normal Case): 10 * 10 = %hhu\n", (unsigned char)(10 * 10));
  printf("Multiplication (Overflow): %hhu * %hhu = %hhu (Wraparound)\n", a, b, result);
  // (Wraparound, since 260 % 256 = 4)
  print_binary("a", &a, sizeof(char));
  print_binary("b", &b, sizeof(char));
  print_binary("result", &result, sizeof(char));
  printf("----------------------------------------------\n");    
}

void demonstrate_division()
{
  unsigned char a = 100;
  unsigned char b = 3;
  unsigned char result = a / b;

  printf("Division (Normal Case): 100 / 5 = %hhu\n", (unsigned char)(100 / 5));
  printf("Division (Truncation): %hhu / %hhu = %hhu (Rounded Down)\n", a, b, result);
  print_binary("a", &a, sizeof(char));
  print_binary("b", &b, sizeof(char));
  print_binary("result", &result, sizeof(char));
  printf("----------------------------------------------\n");    
}

void demonstrate_negation(){
  unsigned char a = 0;
  unsigned char b = 100;

  printf("Negation (Normal Case): -%hhu = %hhu\n", a, -a);
  print_binary("a", &a, sizeof(char));
  unsigned char result = -b;
  printf("Negation (Overflow): -%hhu = %hhu\n", b, result);
  
  print_binary("b", &b, sizeof(char));
  print_binary("result", &result, sizeof(char));
  printf("----------------------------------------------\n");    
}

void demonstrate_edge_cases()
{
  unsigned char max_val = UCHAR_MAX; // 255
  unsigned char min_val = 0;

  printf("Edge Case (Overflow Addition): 255 + 1 = %hhu\n", (unsigned char)(max_val + 1));
  printf("Edge Case (Underflow Subtraction): 0 - 1 = %hhu\n", (unsigned char)(min_val - 1));
  printf("Edge Case (Multiplication): 255 * 2 = %hhu\n", (unsigned char)(max_val * 2));
  printf("Edge Case (Division by Zero): 100 / 0 = (undefined, may cause runtime error)\n");
}

int main()
{
  demonstrate_addition();
  demonstrate_subtraction();
  demonstrate_multiplication();
  demonstrate_division();
  demonstrate_negation();
  demonstrate_edge_cases();
  return 0;
}
