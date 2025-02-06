#include <stdio.h>

int main()
{
  int arr[] = {10, 20, 30, 40, 50};
  int *ptr1 = arr;
  int *ptr2 = &arr[2];

  /*
  1. Increment and Decrement (`++` and `--`)
    - `ptr++` or `++ptr`: Moves the pointer to the next element of the type it points to.
    - `ptr--` or `--ptr`: Moves the pointer to the previous element.  
  */
  printf("Original ptr1: %p, Value: %d\n", (void *)ptr1, *ptr1);
  ptr1++;
  printf("After ptr1++: %p, Value: %d\n", (void *)ptr1, *ptr1);
  ptr1--;
  printf("After ptr1--: %p, Value: %d\n\n", (void *)ptr1, *ptr1);

  /*
  2. Addition and Subtraction (`+` and `-`)
    - `ptr + n`: Moves the pointer forward by `n` elements.
    - `ptr - n`: Moves the pointer backward by `n` elements.
  */
  printf("Original ptr2: %p, Value: %d\n", (void *)ptr2, *ptr2);
  ptr2 = ptr2 + 2; // Move forward by 2 elements
  printf("After ptr2 + 2: %p, Value: %d\n", (void *)ptr2, *ptr2);
  ptr2 = ptr2 - 1; // Move backward by 1 element
  printf("After ptr2 - 1: %p, Value: %d\n\n", (void *)ptr2, *ptr2);


  /*
  3. Subtraction Between Pointers (`ptr1 - ptr2`)
    - When two pointers point to elements of the same array, their difference 
      gives the number of elements between them.
  */
  int diff = &arr[4] - &arr[1];
  printf("Difference between arr[4] and arr[1]: %d elements\n\n", diff);


  /*
  4. Comparison (`==, !=, >, <, >=, <=`)
    - Pointers can be compared to check if they point to the same or different memory locations.
    - They must belong to the same array or be `nullptr`.
  */
  if (ptr1 < ptr2)
  {
    printf("ptr1 points to an earlier element than ptr2\n");
  }
  else
  {
    printf("ptr1 does not point to an earlier element than ptr2\n");
  }

  /*
  5. Assignment (`=`)
    - A pointer can be assigned another pointer of the same type.
    - A pointer can be assigned `nullptr`.
  */
  int a = 100, b = 200;
  int *pA = &a;
  int *pB = &b;
  printf("Before assignment: pA points to %d, pB points to %d\n", *pA, *pB);
  pA = pB;
  printf("After assignment: pA now points to %d\n\n", *pA);

/*
Invalid Operations on Pointers
1. Multiplication (`*`), Division (`/`), and Modulus (`%`) are NOT allowed on pointers.
2. Adding two pointers (`ptr1 + ptr2`) is not allowed.
3. Dereferencing an uninitialized or out-of-bounds pointer results in undefined behavior.
*/
  // ptr1 = ptr1 * 2;  // ❌ Invalid
  // ptr1 = ptr1 / 2;  // ❌ Invalid
  // int *ptr3 = ptr1 + ptr2; // ❌ Invalid
  // int *p;
  // std::cout << *p; 

  return 0;
}
