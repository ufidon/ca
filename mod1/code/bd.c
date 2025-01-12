#include <stdio.h>
#include <stdlib.h>

// Function to perform division by power-of-2 using right shift
int divide_power2_shift(int x, int k) {
    return x >> k; // Simple right shift (problematic for negative x)
}

// Function to perform division by power-of-2 with biasing
int divide_power2_bias(int x, int k) {
    // Add bias: (1 << k) - 1 if x is negative
    int bias = (x >> 31) & ((1 << k) - 1); // Bias is 0 for positive x
    return (x + bias) >> k; // Corrected division
}

// Function to print results in the desired format
void print_division_results(int x, int k) {
    int result_shift = divide_power2_shift(x, k);
    int result_bias = divide_power2_bias(x, k);
    double real_quotient = (double)x / (1 << k); // Real quotient as double

    // Print the table row for shift operation
    printf("| %-6d >> %-2d | %-13.4f | %-9d | %-8X | ", x, k, real_quotient, result_shift, result_shift);
    for (int i = 31; i >= 0; i--) {
        printf("%d", (result_shift >> i) & 1);
        if (i % 8 == 0) printf(" ");
    }
    printf("|\n");

    // Print the table row for corrected operation
    printf("| "/*%d >> %d*/ "%-12s | %-13.4f | %-9d | %-8X | ", /*x, k,*/ "biased", real_quotient, result_bias, result_bias);
    for (int i = 31; i >= 0; i--) {
        printf("%d", (result_bias >> i) & 1);
        if (i % 8 == 0) printf(" ");
    }
    printf("|\n");
}

int main(int argc, char *argv[]) {
    int x, k;

    // Check if dividend and divisor are passed from command line
    if (argc == 3) {
        x = atoi(argv[1]); // Convert first argument to dividend
        k = atoi(argv[2]); // Convert second argument to divisor (power-of-2)
    } else {
        // Fallback to old examples if no arguments are passed
        printf("No arguments provided. Using default examples.\n\n");
        x = -15213; // Default dividend
        k = 1;      // Default divisor (2^k)
    }

    // Print table header
    printf("| Division     | Real Quotient | Computed  | Hex      | Binary                              |\n");
    printf("|--------------|---------------|-----------|----------|-------------------------------------|\n");

    // Print results for the provided or default values
    print_division_results(x, k);

    // Additional test cases if no arguments are passed
    if (argc != 3) {
        print_division_results(x, 4);
        print_division_results(x, 8);
    }

    return 0;
}