#include <stdio.h>

void demonstrate_pointer_basics() {
    // Pointer Arithmetic and Operators Demonstration
    int x = 42;
    int *p = &x;  // '&' generates pointer to x
    
    printf("Pointer Basics:\n");
    printf("Value of x: %d\n", x);
    printf("Address of x: %p\n", (void*)&x);
    printf("Pointer p value (address): %p\n", (void*)p);
    printf("Dereferenced pointer *p: %d\n", *p);
    
    // Pointer Arithmetic
    int arr[] = {10, 20, 30, 40, 50};
    int *arr_ptr = arr;  // arr decays to pointer
    
    printf("\nPointer Arithmetic:\n");
    printf("First element: %d\n", *arr_ptr);
    printf("Third element via pointer arithmetic: %d\n", *(arr_ptr + 2));
    printf("Equivalent array indexing: %d\n", arr[2]);
}

void demonstrate_pointer_operations() {
    int numbers[] = {1, 2, 3, 4, 5};
    int *start = numbers;
    int *end = numbers + 5;  // Pointer to end of array
    
    printf("\nPointer Operations:\n");
    // Pointer subtraction to get array length
    printf("Array length: %ld\n", end - start);
    
    // Demonstrating pointer scaling
    printf("Scaled pointer arithmetic:\n");
    for (int *ptr = start; ptr < end; ptr++) {
        printf("%d ", *ptr);
    }
    printf("\n");
}

void demonstrate_pointer_equivalence() {
    int data[] = {100, 200, 300, 400, 500};
    
    printf("\nArray and Pointer Equivalence:\n");
    // Demonstrating array subscripting vs pointer arithmetic
    printf("data[3] = %d\n", data[3]);
    printf("*(data + 3) = %d\n", *(data + 3));
    
    // Showing they are truly equivalent
    int *ptr = data;
    printf("ptr[3] = %d\n", ptr[3]);
    printf("*(ptr + 3) = %d\n", *(ptr + 3));
}

void demonstrate_pointer_difference() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    
    int *p1 = arr1;
    int *p2 = arr2;
    
    printf("\nPointer Difference:\n");
    // Demonstrating pointer differences
    printf("Pointer to first array: %p\n", (void*)p1);
    printf("Pointer to second array: %p\n", (void*)p2);
    
    // Pointer difference shows memory offset
    printf("Pointer difference: %ld\n", p2 - p1);
    
    // Pointer comparison
    printf("p1 < p2: %s\n", p1 < p2 ? "true" : "false");
    
    // Difference in bytes
    printf("Difference in bytes: %ld\n", 
           (char*)p2 - (char*)p1);
}

int main() {
    demonstrate_pointer_basics();
    demonstrate_pointer_operations();
    demonstrate_pointer_equivalence();
    demonstrate_pointer_difference();
    
    return 0;
}