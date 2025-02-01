#include <stdio.h>

// Caution:
// Using packed structures can reduce memory usage 
// but might lead to performance penalties on some architectures 
// due to misaligned memory accesses.

// Disable padding for structures using pragma pack
// specific to some compilers like GCC and MSVC
#pragma pack(push, 1) // Set alignment to 1 byte

// A structure without padding
struct packed_struct
{
  char c;   // 1 byte
  int i;    // 4 bytes
  double d; // 8 bytes
};

// A union without padding
union packed_union
{
  char c;   // 1 byte
  int i;    // 4 bytes
  double d; // 8 bytes
};

// Restore default alignment
#pragma pack(pop)

int main()
{
  struct packed_struct ps;
  union packed_union pu;

  // Print the size of the packed structure and union
  printf("Size of packed_struct: %zu bytes\n", sizeof(ps));
  printf("Size of packed_union: %zu bytes\n", sizeof(pu));

  // Print the memory addresses of the members to show no gaps
  printf("Offset of ps.c: %p\n", (void *)&ps.c);
  printf("Offset of ps.i: %p\n", (void *)&ps.i);
  printf("Offset of ps.d: %p\n", (void *)&ps.d);

  printf("Offset of pu.c: %p\n", (void *)&pu.c);
  printf("Offset of pu.i: %p\n", (void *)&pu.i);
  printf("Offset of pu.d: %p\n", (void *)&pu.d);

  return 0;
}
