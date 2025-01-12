import sys


def parse_bit_pattern(bit_pattern, w):
    """
    Parse a bit pattern into an integer representation, handling binary and hexadecimal inputs.

    Parameters:
        bit_pattern (str): Bit pattern in binary (e.g., '0b1010') or hexadecimal (e.g., '0xA').
        w (int): Total bit width of the floating-point format.

    Returns:
        int: The integer representation of the bit pattern.
    """
    if bit_pattern.startswith("0b"):
        value = int(bit_pattern, 2)
    elif bit_pattern.startswith("0x"):
        value = int(bit_pattern, 16)
    else:
        raise ValueError(
            "Bit pattern must be in binary ('0b...') or hexadecimal ('0x...')."
        )

    if value >= (1 << w):
        raise ValueError(f"Bit pattern exceeds {w} bits.")

    return value


def convert_to_real_value(w, m, bit_pattern):
    """
    Convert a floating-point bit pattern to a real value.

    Parameters:
        w (int): Total bit width.
        m (int): Number of mantissa bits.
        bit_pattern (str): Bit pattern as binary or hexadecimal string.

    Returns:
        float: The real value represented by the floating-point bit pattern.
    """
    # Parse the bit pattern
    value = parse_bit_pattern(bit_pattern, w)

    # Calculate the number of exponent bits
    e = w - 1 - m  # Exponent bits

    # Extract sign, exponent, and mantissa
    sign = (value >> (w - 1)) & 0b1
    exponent = (value >> m) & ((1 << e) - 1)
    mantissa = value & ((1 << m) - 1)

    # Bias for the exponent
    bias = (1 << (e - 1)) - 1

    # Determine the real value
    if exponent == 0:
        if mantissa == 0:
            # Zero
            real_value = 0.0
        else:
            # Denormalized number
            real_value = (-1) ** sign * (mantissa / (1 << m)) * 2 ** (-bias + 1)
    elif exponent == (1 << e) - 1:
        if mantissa == 0:
            # Infinity
            real_value = float("inf") if sign == 0 else float("-inf")
        else:
            # NaN
            real_value = float("nan")
    else:
        # Normalized number
        real_value = (-1) ** sign * (1 + mantissa / (1 << m)) * 2 ** (exponent - bias)

    return real_value


def main():
    """
    Main function to process command-line arguments and convert bit pattern.
    """
    if len(sys.argv) != 4:
        print("Usage: python script.py <w> <m> <bit_pattern>")
        print("Example: python script.py 8 3 0b11001010")
        sys.exit(1)

    # Parse command-line arguments
    try:
        w = int(sys.argv[1])
        m = int(sys.argv[2])
        bit_pattern = sys.argv[3]

        if w <= m + 1:
            raise ValueError("w must be greater than m + 1 (w > m + 1).")

        # Convert bit pattern to real value
        real_value = convert_to_real_value(w, m, bit_pattern)
        print(f"Real value for bit pattern '{bit_pattern}': {real_value}")
    except ValueError as e:
        print(f"Error: {e}")
        sys.exit(1)


if __name__ == "__main__":
    main()
