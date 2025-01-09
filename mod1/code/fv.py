import sys
from tabulate import tabulate


def int_to_binary(n, w):
    """Convert an integer to a binary string of length w."""
    return format(n, f"0{w}b")


def int_to_hex(n, w):
    """Convert an integer to a hexadecimal string of length w//4."""
    return format(n, f"0{w//4}X")


def split_binary_pattern(binary, k, m):
    """Split the binary pattern into sign bit, exponent bits, and mantissa bits."""
    sign_bit = binary[0]
    exponent_bits = binary[1 : k + 1]
    mantissa_bits = binary[k + 1 : k + 1 + m]
    return sign_bit, exponent_bits, mantissa_bits


def print_floating_point_table(w, m):
    # Calculate k (exponent bits)
    k = w - m - 1  # w = k + m + 1 (sign bit)

    # Define constants
    bias = (1 << (k - 1)) - 1  # Exponent bias
    max_exp = (1 << k) - 1  # Maximum exponent value

    # Positive and negative zeros
    pos_zero_bits = 0
    neg_zero_bits = 1 << (w - 1)

    # Positive and negative infinities
    pos_inf_bits = max_exp << m
    neg_inf_bits = (1 << (w - 1)) | (max_exp << m)

    # Positive and negative NaNs
    pos_nan_bits = (max_exp << m) | 1  # Smallest NaN
    neg_nan_bits = (1 << (w - 1)) | (max_exp << m) | 1  # Smallest negative NaN

    # Minimum and maximum normalized values
    min_norm_bits = 1 << m  # Smallest normalized number
    max_norm_bits = ((max_exp - 1) << m) | ((1 << m) - 1)  # Largest normalized number

    # Minimum and maximum denormalized values
    min_denorm_bits = 1  # Smallest denormalized number
    max_denorm_bits = (1 << m) - 1  # Largest denormalized number

    # Prepare the table data
    table = [
        [
            "+NaN",
            *split_binary_pattern(int_to_binary(pos_nan_bits, w), k, m),
            int_to_hex(pos_nan_bits, w),
            "NaN",
            "NaN (any non-zero mantissa)",
        ],
        [
            "+Infinity",
            *split_binary_pattern(int_to_binary(pos_inf_bits, w), k, m),
            int_to_hex(pos_inf_bits, w),
            "+∞",
            "(−1)^0 × ∞",
        ],
        [
            "+Max Normalized",
            *split_binary_pattern(int_to_binary(max_norm_bits, w), k, m),
            int_to_hex(max_norm_bits, w),
            f"{(2 - 2**(-m)) * (2**bias)}",
            f"(2 − 2^(−{m})) × 2^{bias}",
        ],
        [
            "+Min Normalized",
            *split_binary_pattern(int_to_binary(min_norm_bits, w), k, m),
            int_to_hex(min_norm_bits, w),
            f"{2**(-bias + 1)}",
            f"2^(−{bias} + 1)",
        ],
        [
            "+Max Denormalized",
            *split_binary_pattern(int_to_binary(max_denorm_bits, w), k, m),
            int_to_hex(max_denorm_bits, w),
            f"{(1 - 2**(-m)) * 2**(1-bias)}",
            f"(1 − 2^(−{m})) × 2^(1−{bias})",
        ],
        [
            "+Min Denormalized",
            *split_binary_pattern(int_to_binary(min_denorm_bits, w), k, m),
            int_to_hex(min_denorm_bits, w),
            f"{2**(-bias - m + 1)}",
            f"2^(−{bias} − {m} + 1)",
        ],
        [
            "+0",
            *split_binary_pattern(int_to_binary(pos_zero_bits, w), k, m),
            int_to_hex(pos_zero_bits, w),
            "+0",
            "+0",
        ],
        [
            "-0",
            *split_binary_pattern(int_to_binary(neg_zero_bits, w), k, m),
            int_to_hex(neg_zero_bits, w),
            "−0",
            "−0",
        ],
        [
            "-Max Denormalized",
            *split_binary_pattern(
                int_to_binary(min_denorm_bits | (1 << (w - 1)), w), k, m
            ),
            int_to_hex(min_denorm_bits | (1 << (w - 1)), w),
            f"-{2**(-bias - m + 1)}",
            f"−2^(−{bias} − {m} + 1)",
        ],
        [
            "-Min Denormalized",
            *split_binary_pattern(
                int_to_binary(max_denorm_bits | (1 << (w - 1)), w), k, m
            ),
            int_to_hex(max_denorm_bits | (1 << (w - 1)), w),
            f"-{(1 - 2**(-m)) * 2**(1-bias)}",
            f"−(1 − 2^(−{m})) × 2^(1−{bias})",
        ],
        [
            "-Max Normalized",
            *split_binary_pattern(
                int_to_binary(min_norm_bits | (1 << (w - 1)), w), k, m
            ),
            int_to_hex(min_norm_bits | (1 << (w - 1)), w),
            f"-{2**(-bias + 1)}",
            f"−2^(−{bias} + 1)",
        ],
        [
            "-Min Normalized",
            *split_binary_pattern(
                int_to_binary(max_norm_bits | (1 << (w - 1)), w), k, m
            ),
            int_to_hex(max_norm_bits | (1 << (w - 1)), w),
            f"-{(2 - 2**(-m)) * (2**bias)}",
            f"−(2 − 2^(−{m})) × 2^{bias}",
        ],
        [
            "-Infinity",
            *split_binary_pattern(int_to_binary(neg_inf_bits, w), k, m),
            int_to_hex(neg_inf_bits, w),
            "−∞",
            "(−1)^1 × ∞",
        ],
        [
            "-NaN",
            *split_binary_pattern(int_to_binary(neg_nan_bits, w), k, m),
            int_to_hex(neg_nan_bits, w),
            "NaN",
            "NaN (any non-zero mantissa)",
        ],
    ]

    # Print the table using tabulate
    headers = [
        "Type",
        "Sign Bit",
        "Exponent Bits",
        "Mantissa Bits",
        "Hex Pattern",
        "Value",
        "Formula",
    ]
    print(tabulate(table, headers=headers, tablefmt="grid"))


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python script.py <w> <m>")
        sys.exit(1)

    w = int(sys.argv[1])
    m = int(sys.argv[2])

    if w <= m + 1:
        print("Error: w must be greater than m + 1 (w > m + 1).")
        sys.exit(1)

    print_floating_point_table(w, m)
