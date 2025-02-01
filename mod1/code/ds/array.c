#include <stdio.h>

int main()
{
  // Declare arrays with specified sizes and types
  char A[12];   // Array of 12 char elements
  char *B[8];   // Array of 8 pointers to char
  int C[6];     // Array of 6 integers
  double *D[5]; // Array of 5 pointers to double

  // Initialize the arrays with example values (optional)
  for (int i = 0; i < 12; i++)
  {
    A[i] = 'A' + i; // Fill A with characters 'A' to 'L'
  }

  for (int i = 0; i < 8; i++)
  {
    B[i] = &A[i]; // Fill B with pointers to A's elements
  }

  for (int i = 0; i < 6; i++)
  {
    C[i] = i + 1; // Fill C with integers 1 to 6
  }

  for (int i = 0; i < 5; i++)
  {
    D[i] = (double *)&C[i]; // Fill D with pointers to C's elements (cast to double*)
  }

  // Print the details for each array
  printf("Array A (char[12]):\n");
  printf("Element size: 1 byte, Total size: %lu bytes\n", sizeof(A));
  printf("Start address: %p\n", (void *)A);
  for (int i = 0; i < 12; i++)
  {
    printf("Element %d: %c at address %p\n", i, A[i], (void *)&A[i]);
  }

  printf("\nArray B (char*[8]):\n");
  printf("Element size: 8 bytes (pointer), Total size: %lu bytes\n", sizeof(B));
  printf("Start address: %p\n", (void *)B);
  for (int i = 0; i < 8; i++)
  {
    printf("Element %d: %p (points to A[%d])\n", i, (void *)B[i], i);
  }

  printf("\nArray C (int[6]):\n");
  printf("Element size: 4 bytes, Total size: %lu bytes\n", sizeof(C));
  printf("Start address: %p\n", (void *)C);
  for (int i = 0; i < 6; i++)
  {
    printf("Element %d: %d at address %p\n", i, C[i], (void *)&C[i]);
  }

  printf("\nArray D (double*[5]):\n");
  printf("Element size: 8 bytes (pointer), Total size: %lu bytes\n", sizeof(D));
  printf("Start address: %p\n", (void *)D);
  for (int i = 0; i < 5; i++)
  {
    printf("Element %d: %p (points to C[%d])\n", i, (void *)D[i], i);
  }

  return 0;
}
