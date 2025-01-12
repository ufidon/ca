#include <stdio.h>
#include <stdbool.h> // For bool in C

/**

## Table of C/C++ Literal Types and `printf` Format Specifiers

| **Literal Type**            | **Example Literal**       | **`printf` Format Specifier** | **Description**                                                                 |
|------------------------------|---------------------------|-------------------------------|---------------------------------------------------------------------------------|
| **Integer (int)**            | `42`                      | `%d`                          | Signed decimal integer.                                                         |
| **Unsigned Integer**         | `42U`                     | `%u`                          | Unsigned decimal integer.                                                       |
| **Long Integer**             | `42L`                     | `%ld`                         | Signed long decimal integer.                                                    |
| **Unsigned Long**            | `42UL`                    | `%lu`                         | Unsigned long decimal integer.                                                  |
| **Long Long Integer**        | `42LL`                    | `%lld`                        | Signed long long decimal integer.                                               |
| **Unsigned Long Long**       | `42ULL`                   | `%llu`                        | Unsigned long long decimal integer.                                             |
| **Octal Integer**            | `052`                     | `%o`                          | Unsigned octal integer (leading `0` indicates octal).                           |
| **Hexadecimal Integer**      | `0x2A`                    | `%x` or `%X`                  | Unsigned hexadecimal integer (lowercase `x` for `a-f`, uppercase `X` for `A-F`).|
| **Floating-Point**           | `3.14f`                   | `%f`                          | Decimal floating-point (float).                                                 |
| **Double**                   | `3.14`                    | `%lf`                         | Decimal floating-point (double).                                                |
| **Long Double**              | `3.14L`                   | `%Lf`                         | Decimal floating-point (long double).                                           |
| **Character (char)**         | `'A'`                     | `%c`                          | Single character.                                                               |
| **Signed Character (signed char)** | `'A'`              | `%hhd`                        | Signed 8-bit integer (treated as a small integer).                              |
| **Unsigned Character (unsigned char)** | `'A'`         | `%hhu`                        | Unsigned 8-bit integer (treated as a small integer).                            |
| **Short Integer (short)**    | `42`                      | `%hd`                         | Signed short decimal integer.                                                   |
| **Unsigned Short Integer (unsigned short)** | `42`       | `%hu`                         | Unsigned short decimal integer.                                                 |
| **String**                   | `"Hello"`                 | `%s`                          | Null-terminated string.                                                         |
| **Pointer**                  | `&x`                      | `%p`                          | Pointer address (in hexadecimal).                                               |
| **Boolean (C++)**            | `true` or `false`         | `%d`                          | Boolean value (prints `1` for `true`, `0` for `false`).                         |

## Key Notes
1. **Signed/Unsigned Char**:
   - `signed char` is treated as an 8-bit integer and uses `%hhd`.
   - `unsigned char` is treated as an 8-bit unsigned integer and uses `%hhu`.
2. **Short**:
   - `short` uses `%hd` for signed short integers.
   - `unsigned short` uses `%hu` for unsigned short integers.
3. **Pointer Format**:
   - Always cast pointers to `void*` when using `%p` to avoid compiler warnings.
4. **Boolean in C**:
   - In C, use `int` with `0` for `false` and `1` for `true`. In C++, `bool` can be used directly.
*/

int main()
{
  int i = 42;
  unsigned int u = 42U;
  long l = 42L;
  unsigned long ul = 42UL;
  long long ll = 42LL;
  unsigned long long ull = 42ULL;
  float f = 3.14f;
  double d = 3.14;
  long double ld = 3.14L;
  char c = 'A';
  signed char sc = -128;
  unsigned char uc = 255;
  short s = 32767;
  unsigned short us = 65535;
  char str[] = "Hello";
  int *ptr = &i;
  bool b = true;

  printf("Integer: %d\n", i);
  printf("Unsigned Integer: %u\n", u);
  printf("Long Integer: %ld\n", l);
  printf("Unsigned Long: %lu\n", ul);
  printf("Long Long Integer: %lld\n", ll);
  printf("Unsigned Long Long: %llu\n", ull);
  printf("Octal: %o\n", i);
  printf("Hexadecimal: %x\n", i);
  printf("Float: %f\n", f);
  printf("Double: %lf\n", d);
  printf("Long Double: %Lf\n", ld);
  printf("Character: %c\n", c);
  printf("Signed Char: %hhd\n", sc);
  printf("Unsigned Char: %hhu\n", uc);
  printf("Short: %hd\n", s);
  printf("Unsigned Short: %hu\n", us);
  printf("String: %s\n", str);
  printf("Pointer: %p\n", (void *)ptr);
  printf("Boolean: %d\n", b);

  return 0;
}