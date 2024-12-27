#include <stdio.h>
#include <limits.h>

/** 1. printf format string
 * ------------------------
Integer Types:
char: %c (character), %d (signed decimal), %i (signed decimal or octal/hexadecimal)
short: %hd (signed decimal), %hi (signed decimal or octal/hexadecimal)
int: %d (signed decimal), %i (signed decimal or octal/hexadecimal)
long: %ld (signed decimal), %li (signed decimal or octal/hexadecimal)
long long: %lld (signed decimal), %lli (signed decimal or octal/hexadecimal)

Unsigned Integer Types:
unsigned char: %hhu (unsigned decimal)
unsigned short: %hu (unsigned decimal)
unsigned int: %u (unsigned decimal)
unsigned long: %lu (unsigned decimal)
unsigned long long: %llu (unsigned decimal)

Floating-Point Types:
float: %f (decimal notation), %e (scientific notation), %g (shortest representation)
double: %lf (decimal notation), %le (scientific notation), %lg (shortest representation)
long double: %Lf (decimal notation), %Le (scientific notation), %Lg (shortest representation)

Other Types:
void*: %p (pointer address)
size_t: %zu (unsigned integer type for sizes)

** 2. Literals
 *-----------------------------------------
Integer Literals:
u or U: Unsigned integer (e.g., 10U, 0xFFU)
l or L: Long integer (e.g., 10L, 0x10L)
ul, uL, LU, UL: Unsigned long integer (e.g., 10UL, 0xFFUL)
ll or LL: Long long integer (e.g., 10LL, 0x10LL)
ull, uLL, Ull, ULL, llu, llU, Llu, LLU: Unsigned long long integer (e.g., 10ULL, 0xFFULL)
z or Z: Signed version of std::size_t (C++23) (e.g., 10Z, 0xFFZ)
uz, uZ, Uz, UZ, zu, zU, Zu, ZU: std::size_t (C++23) (e.g., 10UZ, 0xFFUZ)

Floating-Point Literals:
f or F: Float (e.g., 3.14f)
l or L: Long double (e.g., 3.14L)

No suffix:
char literals are treated as integer values. 
  You can explicitly cast to unsigned char if needed. 
By default, integer literals are treated as int as well.
  You can explicitly cast to unsigned short.

*/

int main()
{
  // Expanding examples
  short int s_val = -12345;      // Negative short value
  short int ps_val = 12345;

  unsigned short us_val = 50000; // Large unsigned short value

  int s2i = s_val;   // Sign extension
  unsigned int s2ui = s_val;
  int ps2i = ps_val;
  unsigned int ps2ui = ps_val;

  unsigned int us2ui = us_val;
  int ex_us_val = us_val; // Zero extension

  // What will happen if different format strings are used?
  printf("Expanding:\n");
  printf("short: %hd → int: %d\n", s_val, s2i);
  printf("short: %hd → int: %d\n", ps_val, ps2i);
  printf("short: %hd → uint: %u\n", s_val, s2ui);
  printf("short: %hd → uint: %u\n", ps_val, ps2ui);
  printf("ushort: %hu → uint: %u\n", us_val, us2ui);
  printf("ushort: %hu → int: %d\n", us_val, ex_us_val);
  
  // Truncating examples
  int i_val = 70000;               // Larger than max unsigned short
  int ni_val = -70000;
  unsigned int u_i_val = UINT_MAX; // Max unsigned int

  unsigned short i2us = (unsigned short)i_val;
  short i2s = (short)i_val;
  unsigned short ni2us = (unsigned short)ni_val;
  short ni2s = (short)ni_val;  
  unsigned short ui2us = (unsigned short)u_i_val;
  short ui2s = (short)u_i_val;

  printf("\nTruncating:\n");
  printf("int: %d → ushort: %hu\n", i_val, i2us);
  printf("int: %d → ushort: %hu\n", ni_val, ni2us);
  printf("int: %d → short: %hd\n", i_val, i2s);
  printf("int: %d → short: %hd\n", ni_val, ni2s);  
  printf("uint: %u → ushort: %hu\n", u_i_val, ui2us);
  printf("uint: %u → short: %hd\n", u_i_val, ui2s);

  // Truncating signed values
  int neg_val = -32769; // Just below the range of short
  short nits = (short)neg_val;

  printf("int: %d → short: %hd\n", neg_val, nits);

  // Demonstrating modulo behavior
  int mod_val = 66000; // Greater than 65535
  unsigned short mod_result = mod_val % 65536;
  unsigned short tr_result = (unsigned short) mod_val;

  printf("\nModulo operation:\n");
  printf("%d mod 65536 = %u (similar to truncation)\n", mod_val, mod_result);
  printf("int: %d → ushort: %hu\n", mod_val, tr_result);

  return 0;
}
