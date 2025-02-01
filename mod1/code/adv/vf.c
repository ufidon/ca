#include <stdio.h>

// Function with a variable-size stack frame
long vframe(long n, long idx, long *q)
{
  long i;

  // Variable-length array (VLA) allocation on the stack
  long p[n]; // Size of p is determined at runtime based on the value of n

  // Initialize p[0] to point to i (simulating a pointer to a local variable)
  p[0] = (long)&i;

  // Loop to initialize the rest of the array p
  for (i = 1; i < n; i++)
  {
    p[i] = (long)q; // Set elements of p to the value of q (simulating pointer assignment)
  }

  // Return the value pointed to by p[idx] (dereferencing the value stored in p)
  return *(long *)p[idx];
}

int main()
{
  long n = 5;   // Size of the array
  long idx = 2; // Index to return
  long q = 100; // Pointer value (simulated)

  // Call the function with the given parameters
  long result = vframe(n, idx, &q);

  // Print the result
  printf("Value at p[%ld]: %ld\n", idx, result);

  return 0;
}
