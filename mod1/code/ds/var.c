#include <stdio.h>

#define N 3 // Matrix size (3x3 for this example)

typedef int fix_matrix[N][N];

// (a) Original C code: Compute matrix element (i, k) of the variable matrix product
// The parameter n must precede A[n][n] 
// to allow the array dimensions to be computed at the time of declaration.
int var_prod_ele(long n, int A[n][n], int B[n][n], long i, long k)
{
  long j;
  int result = 0;

  // Compute the dot product of row i of A and column k of B
  for (j = 0; j < n; j++)
  {
    result += A[i][j] * B[j][k];
  }

  return result;
}

// (b) Optimized C code: Compute matrix element (i, k) of the variable matrix product using pointers
int var_prod_ele_opt(long n, int A[n][n], int B[n][n], long i, long k)
{
  int *Arow = A[i];     // Pointer to row i of matrix A
  int *Bptr = &B[0][k]; // Pointer to element B[0][k] in matrix B
  int result = 0;
  long j;

  // Compute the dot product using pointer arithmetic
  for (j = 0; j < n; j++)
  {
    result += Arow[j] * *Bptr;
    Bptr += n; // Move pointer to the next element in column k of B
  }

  return result;
}

int main()
{
  // Example 3x3 matrices for A and B
  fix_matrix A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  fix_matrix B = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

  long i = 1, k = 2; // Example: Compute the (1, 2) element of the matrix product

  // Call the original function and print the result
  int result_original = var_prod_ele(N, A, B, i, k);
  printf("Original matrix product element at (%ld, %ld): %d\n", i, k, result_original);

  // Call the optimized function and print the result
  int result_optimized = var_prod_ele_opt(N, A, B, i, k);
  printf("Optimized matrix product element at (%ld, %ld): %d\n", i, k, result_optimized);

  return 0;
}
