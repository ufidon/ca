#include <stdio.h>

// Structure with potential padding due to alignment rules
struct S1
{
  int i;  // 4 bytes
  char c; // 1 byte
  int j;  // 4 bytes
};

// Structure with padding added by the compiler for proper alignment
struct S2
{
  int i;  // 4 bytes
  int j;  // 4 bytes
  char c; // 1 byte
          // 3 bytes of padding will be added to align the next element in an array
};

// Structure with manual alignment
struct S3
{
  char c; // 1 byte
  int i;  // 4 bytes
};

int main()
{
  // Declare instances of the structures
  struct S1 s1;
  struct S2 s2;
  struct S3 s3;

  // Print the sizes of the structures
  printf("Size of S1: %zu bytes\n", sizeof(s1)); // May include padding
  printf("Size of S2: %zu bytes\n", sizeof(s2)); // Includes padding to align fields
  printf("Size of S3: %zu bytes\n", sizeof(s3)); // Manually aligned with no extra padding

  // Show the memory layout of the structures
  printf("\nMemory layout of S1:\n");
  printf("Address of s1.i: %p\n", (void *)&s1.i);
  printf("Address of s1.c: %p\n", (void *)&s1.c);
  printf("Address of s1.j: %p\n", (void *)&s1.j);

  printf("Offset of s1.i: %lu\n", (unsigned long)&s1.i - (unsigned long)&s1);
  printf("Offset of s1.c: %lu\n", (unsigned long)&s1.c - (unsigned long)&s1);
  printf("Offset of s1.j: %lu\n", (unsigned long)&s1.j - (unsigned long)&s1);

  printf("\nMemory layout of S2:\n");
  printf("Address of s2.i: %p\n", (void *)&s2.i);
  printf("Address of s2.j: %p\n", (void *)&s2.j);
  printf("Address of s2.c: %p\n", (void *)&s2.c);

  printf("Offset of s2.i: %lu\n", (unsigned long)&s2.i - (unsigned long)&s2);
  printf("Offset of s2.j: %lu\n", (unsigned long)&s2.j - (unsigned long)&s2);
  printf("Offset of s2.c: %lu\n", (unsigned long)&s2.c - (unsigned long)&s2);

  printf("\nMemory layout of S3:\n");
  printf("Address of s3.c: %p\n", (void *)&s3.c);
  printf("Address of s3.i: %p\n", (void *)&s3.i);

  printf("Offset of s3.c: %lu\n", (unsigned long)&s3.c - (unsigned long)&s3);
  printf("Offset of s3.i: %lu\n", (unsigned long)&s3.i - (unsigned long)&s3);

  return 0;
}