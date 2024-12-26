#include <stdio.h>
#include <math.h>  // For floor()
#include <limits.h>

// Multiply by constant using bitwise shift-and-add
int multiply_by_constant(int x, int K) {
    int result = 0;
    int shift = 0;

    while (K > 0) {
        if (K & 1) {  // Check if the least significant bit is 1
            result += (x << shift);  // Add shifted x
        }
        K = K >> 1;  // Shift K to the right (binary division by 2)
        shift += 1;
    }

    return result;
}

// Divide by constant using precomputed multiplier
int divide_by_K(int x, int K) {
    const int n = 32;
    unsigned int M = (unsigned int) floor((double)(1ULL << n) / K);
    const int bias = 1 << (n - 1);  // 2^(n-1) for rounding correction

    // Apply bias for negative values to handle floor division correctly
    if (x < 0) {
        // For negative numbers, subtract bias after multiplication to round towards zero
        return (x * (long long)M - bias) >> n;
    } else {
        // For positive numbers, add bias before shifting
        return (x * (long long)M + bias) >> n;
    }
}


// Testing the functions
int main() {
    int x = 25;
    int K_mul = 13;
    int K_div = 13;

    int mul_result = multiply_by_constant(x, K_mul);
    int div_result = divide_by_K(x, K_div);

    printf("%d * %d = %d\n", x, K_mul, mul_result);
    printf("%d / %d = %d\n", x, K_div, div_result);

    // Test with negative numbers
    x = -25;
    mul_result = multiply_by_constant(x, K_mul);
    div_result = divide_by_K(x, K_div);

    printf("%d * %d = %d\n", x, K_mul, mul_result);
    printf("%d / %d = %d\n", x, K_div, div_result);

    return 0;
}
