#include <stdio.h>
#include <limits.h>

// In the overflow cases, the results may seem unexpected due to 
// wrapping around the 8-bit signed char range (-128 to 127).

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

int main() {
    signed char a, b, result;
    
    // 1. Addition (Normal Case)
    a = 50;
    b = 20;
    result = a + b;
    printf("Addition (Normal): %d + %d = %d\n", a, b, result);
    print_binary("a", &a, sizeof(char));
    print_binary("b", &b, sizeof(char));
    print_binary("result", &result, sizeof(char));
    printf("----------------------------------------------\n");
    
    // 2. Addition (Overflow Case)
    a = 100;
    b = 50;
    result = a + b;
    printf("Addition (Overflow): %d + %d = %d\n", a, b, result);
    print_binary("a", &a, sizeof(char));
    print_binary("b", &b, sizeof(char));
    print_binary("result", &result, sizeof(char));
    printf("----------------------------------------------\n");

    // 3. Subtraction (Normal Case)
    a = 50;
    b = 20;
    result = a - b;
    printf("Subtraction (Normal): %d - %d = %d\n", a, b, result);
    print_binary("a", &a, sizeof(char));
    print_binary("b", &b, sizeof(char));
    print_binary("result", &result, sizeof(char));
    printf("----------------------------------------------\n");

    // 4. Subtraction (Overflow Case)
    a = -100;
    b = 50;
    result = a - b;
    printf("Subtraction (Overflow): %d - %d = %d\n", a, b, result);
    print_binary("a", &a, sizeof(char));
    print_binary("b", &b, sizeof(char));
    print_binary("result", &result, sizeof(char));
    printf("----------------------------------------------\n");

    // 5. Multiplication (Normal Case)
    a = 5;
    b = 4;
    result = a * b;
    printf("Multiplication (Normal): %d * %d = %d\n", a, b, result);
    print_binary("a", &a, sizeof(char));
    print_binary("b", &b, sizeof(char));
    print_binary("result", &result, sizeof(char));
    printf("----------------------------------------------\n");

    // 6. Multiplication (Overflow Case)
    a = 16;
    b = 16;
    result = a * b;
    printf("Multiplication (Overflow): %d * %d = %d\n", a, b, result);
    print_binary("a", &a, sizeof(char));
    print_binary("b", &b, sizeof(char));
    print_binary("result", &result, sizeof(char));
    printf("----------------------------------------------\n");

    // 7. Division (Normal Case)
    a = 100;
    b = 5;
    result = a / b;
    printf("Division (Normal): %d / %d = %d\n", a, b, result);
    print_binary("a", &a, sizeof(char));
    print_binary("b", &b, sizeof(char));
    print_binary("result", &result, sizeof(char));
    printf("----------------------------------------------\n");

    // 8. Division (Overflow Case)
    a = -128;
    b = -1;
    result = a / b;
    printf("Division (Overflow): %d / %d = %d\n", a, b, result);
    print_binary("a", &a, sizeof(char));
    print_binary("b", &b, sizeof(char));
    print_binary("result", &result, sizeof(char));
    printf("----------------------------------------------\n");

    // 9. Modulus (Normal Case)
    a = 101;
    b = 10;
    result = a % b;
    printf("Modulus (Normal): %d %% %d = %d\n", a, b, result);
    print_binary("a", &a, sizeof(char));
    print_binary("b", &b, sizeof(char));
    print_binary("result", &result, sizeof(char));
    printf("----------------------------------------------\n");

    // 10. Negation
    a = -128;
    result = -a;
    printf("Negation (Normal): -%d = %d\n", a, result);
    print_binary("a", &a, sizeof(char));
    print_binary("result", &result, sizeof(char));
    printf("----------------------------------------------\n");    

    return 0;
}
