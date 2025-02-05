#include <stdio.h>

int main()
{
  union
  {
    unsigned char c[8];  // Access as bytes
    unsigned short s[4]; // Access as 2-byte shorts
    unsigned int i[2];   // Access as 4-byte ints
    unsigned long l[1];  // Access as 8-byte long
  } dw;

  // Initialize bytes from 0xf0 to 0xf7
  for (int j = 0; j < 8; j++)
    dw.c[j] = 0xf0 + j;

  // Print individual bytes
  printf("Bytes:    [0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x]\n",
         dw.c[0], dw.c[1], dw.c[2], dw.c[3],
         dw.c[4], dw.c[5], dw.c[6], dw.c[7]);

  // Print as 2-byte shorts
  printf("Shorts:   [0x%04x,0x%04x,0x%04x,0x%04x]\n",
         dw.s[0], dw.s[1], dw.s[2], dw.s[3]);

  // Print as 4-byte ints
  printf("Ints:     [0x%08x,0x%08x]\n",
         dw.i[0], dw.i[1]);

  // Print as 8-byte long
  printf("Long:     [0x%016lx]\n",
         dw.l[0]);

  return 0;
}