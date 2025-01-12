#include <stdio.h>
#include <stdlib.h>

// To compile the code with GCC, use the -std=gnu2x or -std=c2x flag:
// gcc -std=gnu2x -o dfp_example dfp_example.c

int main() {
    // Declare decimal floating-point variables
    _Decimal128 d128 = 1234567890123456789012345678901234.0DL;
    _Decimal64 d64 = 1234567890123456.0DD;
    _Decimal32 d32 = 1234567.0DF;

    // Print decimal floating-point values
    printf("Decimal128: %Lf\n", (long double)d128); // Note: Printing requires casting
    printf("Decimal64: %lf\n", (double)d64);
    printf("Decimal32: %f\n", (float)d32);

    return 0;
}