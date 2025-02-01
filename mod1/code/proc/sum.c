//   - `cl /Zi /Od sum.c /Fe:sum.exe`
//   - `gcc -g -o sum sum.c`

#include <stdio.h>

long sum(long a, long b, long c)
{
    return a + b + c;
}

int main()
{
    long a = 5, b=6, c=7;
    long result = sum(a,b,c);
    printf("%ld+%ld+%ld = %ld\n", a,b,c, result);
    return 0;
}