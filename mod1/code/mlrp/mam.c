#include <stdio.h>
#include <stdlib.h>

// Function to store the sum of two numbers in a destination
long sum_store(long a, long b, long *dest)
{
  long sum = a + b;
  *dest = sum;
  return sum;
}

// Function to swap two numbers
void swap(long *a, long *b)
{
  long ta = *a;
  long tb = *b;
  *a = tb;
  *b = ta;
}

// Main function demonstrating usage
int main(int argc, char *argv[])
{

  long x = 0x55;
  long y = 0xaa;

  // Demonstrate sum_store
  long sum;
  sum_store(x, y, &sum);
  printf("%ld + %ld --> %ld (via sum_store)\n", x, y, sum);

  // Demonstrate swap
  printf("Before swap: x = %ld, y = %ld\n", x, y);
  swap(&x, &y);
  printf("After swap: x = %ld, y = %ld\n", x, y);

  // Array manipulation
  char arr1[] = "Donald Trump";
  for (int i = 0; i < 13; i++)
  {
    printf("%c", arr1[i]);
  }
  printf("\n");

  arr1[6] = '|';
  printf("%s\n", arr1);
  
  short arr2[] = {0x11,0x22,0x33,0x44,0x55};
  for (int i = 0; i < 5; i++)
  {
    printf("%hX ", arr2[i]);
  }
  printf("\n");  

  int arr3[] = {0x1111,0x2222,0x3333,0x4444,0x5555};
  for (int i = 0; i < 5; i++)
  {
    printf("%X ", arr3[i]);
  }
  printf("\n"); 

  long arr4[] = {0xaa,0xbb,0xcc,0xdd,0xee,0xff};
  for (int i = 0; i < 6; i++)
  {
    printf("%lX ", arr4[i]);
  }
  printf("\n"); 

  return 0;
}