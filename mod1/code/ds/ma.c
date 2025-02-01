#include <stdio.h>

void print_arr(int arr[][3], int rows)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
}

void addr_demo(int arr[][3], int rows)
{
  printf("\nArray Address Mechanics:\n");
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      printf("&arr[%d][%d] = %p\n", i, j, (void *)&arr[i][j]);
    }
  }
}

void mem_layout_demo()
{
  int arr[5][3] = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
      {10, 11, 12},
      {13, 14, 15}};

  printf("Array Contents:\n");
  print_arr(arr, 5);
  addr_demo(arr, 5);
}

int main()
{
  mem_layout_demo();
  return 0;
}