#include <stdio.h>
#include <stdlib.h>

#define ZLEN 5
#define PCOUNT 4
#define UCOUNT 3
#define N 16

typedef int zip_dig[ZLEN];

// Array allocation example
zip_dig cmu = {1, 5, 2, 1, 3};
zip_dig mit = {0, 2, 1, 3, 9};
zip_dig ucb = {9, 4, 7, 2, 0};

// Multi-dimensional array
zip_dig pgh[PCOUNT] = {
    {1, 5, 2, 0, 6},
    {1, 5, 2, 1, 3},
    {1, 5, 2, 1, 7},
    {1, 5, 2, 2, 1}};

// Multi-level array
int *univ[UCOUNT] = {mit, cmu, ucb};

// Access single array element
int get_digit(zip_dig z, int digit)
{
  return z[digit];
}

// Increment array elements in a loop
void zincr(zip_dig z)
{
  for (size_t i = 0; i < ZLEN; i++)
    z[i]++;
}

// Accessing row in a nested array
int *get_pgh_zip(int index)
{
  return pgh[index];
}

// Accessing element in a nested array
int get_pgh_digit(int index, int dig)
{
  return pgh[index][dig];
}

// Accessing element in a multi-level array
int get_univ_digit(size_t index, size_t digit)
{
  return univ[index][digit];
}

// Fixed-size matrix access
typedef int fix_matrix[N][N];
int fix_ele(fix_matrix a, size_t i, size_t j)
{
  return a[i][j];
}

// Variable-size matrix access with explicit indexing
#define IDX(n, i, j) ((i) * (n) + (j))
int vec_ele(size_t n, int *a, size_t i, size_t j)
{
  return a[IDX(n, i, j)];
}

// Variable-size matrix access with implicit indexing
int var_ele(size_t n, int a[n][n], size_t i, size_t j)
{
  return a[i][j];
}

int main()
{
  printf("Array Allocation and Access Demonstration\n");
  printf("cmu[2] = %d\n", get_digit(cmu, 2));

  zincr(cmu);
  printf("After increment: cmu[2] = %d\n", cmu[2]);

  printf("pgh[1][3] = %d\n", get_pgh_digit(1, 3));
  printf("univ[2][4] = %d\n", get_univ_digit(2, 4));

  fix_matrix matrix = {0};
  matrix[3][5] = 42;
  printf("fix_matrix[3][5] = %d\n", fix_ele(matrix, 3, 5));

  int *vector_matrix = malloc(N * N * sizeof(int));
  vector_matrix[IDX(N, 3, 5)] = 99;
  printf("vector_matrix[3][5] = %d\n", vec_ele(N, vector_matrix, 3, 5));
  free(vector_matrix);

  return 0;
}
