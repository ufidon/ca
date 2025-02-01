#include <stdio.h>

// Function to demonstrate the use of function pointers
int add(int a, int b)
{
  return a + b;
}

int main()
{
  // 1. Pointer to a variable
  int num = 10;
  int *ptr = &num; // Pointer to int

  printf("Pointer value: %p\n", (void *)ptr); // Address of num
  printf("Dereferenced value: %d\n", *ptr);   // Value of num through pointer

  // 2. Array and pointer relationship
  int arr[] = {1, 2, 3, 4, 5};
  int *arr_ptr = arr; // Pointer to the first element of the array

  printf("\nArray values using pointer arithmetic:\n");
  for (int i = 0; i < 5; i++)
  {
    printf("arr[%d] = %d\n", i, *(arr_ptr + i)); // Pointer arithmetic to access array elements
  }

  // 3. Pointer casting example
  char *str = "Hello, World!";
  void *ptr_void = str; // Casting to a void pointer

  // Casting back to char* to print the string
  printf("\nPointer casting:\n");
  printf("String via void pointer: %s\n", (char *)ptr_void);

  // 4. Function pointer usage
  int (*func_ptr)(int, int) = add; // Pointer to function 'add'

  int result = func_ptr(5, 7);                       // Call function using the pointer
  printf("\nFunction pointer result: %d\n", result); // Output the result

  return 0;
}
