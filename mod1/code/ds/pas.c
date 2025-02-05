#include <stdio.h>
#include <stdlib.h>

// https://stackoverflow.com/questions/15111526/complex-c-declaration
// https://c-faq.com/decl/spiral.anderson.html

void demonstrate_basic_pointers()
{
  // Basic array vs pointer declaration
  int A1[3] = {1, 2, 3}; // Array of 3 integers
  int *A2;               // Pointer to integer (uninitialized)

  printf("sizeof(A1) = %lu\n", sizeof(A1)); // Returns 12 (3 * sizeof(int))
  printf("sizeof(A2) = %lu\n", sizeof(A2)); // Returns 8 (size of pointer)

  // Properly allocate A2
  A2 = (int *)malloc(3 * sizeof(int));
  A2[0] = 1;
  A2[1] = 2;
  A2[2] = 3;
}

void demonstrate_array_pointers()
{
  // Array of pointers vs pointer to array
  int *A2[3];  // Array of 3 pointers to int
  int(*A3)[3]; // Pointer to array of 3 ints
  int(*A4[3]); // Array of 3 pointers to int (same as A2)

  // Initialize A2 (array of pointers)
  for (int i = 0; i < 3; i++)
  {
    A2[i] = (int *)malloc(sizeof(int));
    *A2[i] = i;
  }

  // Initialize A3 (pointer to array)
  A3 = (int(*)[3])malloc(sizeof(int[3]));
  (*A3)[0] = 0;
  (*A3)[1] = 1;
  (*A3)[2] = 2;
}

void demonstrate_2d_arrays()
{
  // 2D array and various pointer combinations
  int A1[3][5];    // 2D array of integers
  int *A2[3][5];   // 2D array of pointers to int
  int(*A3)[3][5];  // Pointer to 2D array
  int *(A4[3][5]); // Same as A2
  int(*A5[3])[5];  // Array of pointers to arrays

  // Initialize A1 (regular 2D array)
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 5; j++)
      A1[i][j] = i * 5 + j;

  // Initialize A3 (pointer to 2D array)
  A3 = (int(*)[3][5])malloc(sizeof(int[3][5]));

  // Initialize A5 (array of pointers to arrays)
  for (int i = 0; i < 3; i++)
  {
    A5[i] = (int(*)[5])malloc(sizeof(int[5]));  // or malloc(5 * sizeof(int))
    for (int j = 0; j < 5; j++)
      (*A5[i])[j] = i * 5 + j;
  }

  printf("sizeof(A1) = %lu\n", sizeof(A1));     // 60 (3 * 5 * sizeof(int))
  printf("sizeof(*A1) = %lu\n", sizeof(*A1));   // 20 (5 * sizeof(int))
  printf("sizeof(**A1) = %lu\n", sizeof(**A1)); // 4 (sizeof(int))
}

int main()
{
  demonstrate_basic_pointers();
  demonstrate_array_pointers();
  demonstrate_2d_arrays();
  return 0;
}