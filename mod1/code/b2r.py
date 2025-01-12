import sys


def binary_to_decimal(binary_str):
    # Split the binary string into integer and fractional parts
    if "." in binary_str:
        integer_part, fractional_part = binary_str.split(".")
    else:
        integer_part, fractional_part = binary_str, ""

    # Convert the integer part to decimal
    decimal_integer = 0
    for i, bit in enumerate(integer_part[::-1]):
        decimal_integer += int(bit) * (2**i)

    # Convert the fractional part to decimal
    decimal_fraction = 0
    for i, bit in enumerate(fractional_part):
        decimal_fraction += int(bit) * (2 ** -(i + 1))

    # Combine integer and fractional parts
    return decimal_integer + decimal_fraction


if __name__ == "__main__":
    # Check if a binary number is provided as a command-line argument
    if len(sys.argv) != 2:
        print("Usage: python binary_to_decimal.py <binary_number>")
        sys.exit(1)

    binary_number = sys.argv[1]
    try:
        decimal_number = binary_to_decimal(binary_number)
        print(f"Binary: {binary_number} -> Decimal: {decimal_number}")
    except ValueError:
        print(
            "Invalid binary number. Please provide a valid binary string (e.g., 10.10)."
        )
