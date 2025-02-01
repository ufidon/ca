#include <stdio.h>

#define N 3 // Matrix dimension

typedef int fix_matrix[N][N];

// (a) Original C code: Compute matrix element (i, k) of the fixed matrix product
int fix_prod_ele(fix_matrix A, fix_matrix B, long i, long k)
{
  long j;
  int result = 0;

  // Compute the dot product of row i of A and column k of B
  for (j = 0; j < N; j++)
  {
    result += A[i][j] * B[j][k];
  }

  return result;
}

// (b) Optimized C code: Compute matrix element (i, k) of the fixed matrix product using pointers
int fix_prod_ele_opt(fix_matrix A, fix_matrix B, long i, long k)
{
  int *Aptr = &A[i][0];     // Points to the first element in row i of A
  int *Bptr = &B[0][k];     // Points to the first element in column k of B
  int *Bend = &B[N - 1][k]; // Points to the last element in column k of B
  int result = 0;

  // Compute the dot product using pointers for optimization
  do
  {
    result += *Aptr * *Bptr; // Add product to result
    Aptr++;                  // Move Aptr to the next column in A
    Bptr += N;               // Move Bptr to the next row in B
  } while (Bptr != Bend); // Stop when we reach the end of column k in B

  return result;
}

int main()
{
  // Define two 3x3 matrices A and B
  fix_matrix A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  fix_matrix B = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

  long i = 1, k = 2; // Example for element at position (1, 2)

  // Call the original function and print the result
  int result_original = fix_prod_ele(A, B, i, k);
  printf("Original matrix product element at (%ld, %ld): %d\n", i, k, result_original);

  // Call the optimized function and print the result
  int result_optimized = fix_prod_ele_opt(A, B, i, k);
  printf("Optimized matrix product element at (%ld, %ld): %d\n", i, k, result_optimized);

  return 0;
}
