#include <stdio.h>
#include <string.h>

/* WARNING: This code demonstrates buffer overflow vulnerabilities.
   Never use gets() in production code - it's deprecated and dangerous. */

/* Compile with:
   gcc -fno-stack-protector -z execstack bfdemo.c -o bfdemo

   Run:
   ./bfdemo

   Expected behavior:
   - Input < 4 chars: Works normally
   - Input > 4 chars: Stack overflow, likely segmentation fault

   📝 Turn on the protection and try it again
*/

void echo()
{
  char buf[4]; /* Deliberately small buffer */
  printf("Type a string: ");
  gets(buf); /* gets() has no bounds checking */
  puts(buf); /* Will print beyond buffer bounds */
}

void call_echo()
{
  echo();
}

int main()
{
  call_echo();
  return 0;
}