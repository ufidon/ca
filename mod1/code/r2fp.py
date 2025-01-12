import argparse
from fractions import Fraction
from tabulate import tabulate


def parse_real_number(input_str):
    """
    Parse a real number or special value from a string.
    Supports formats like:
    - Integer: "314"
    - Decimal: "3.14"
    - Fraction: "3/14"
    - Scientific notation: "-3e14"
    - Special values: "inf", "-inf", "nan", "-nan"
    Returns a float.
    """
    try:
        # Handle special values
        if input_str.lower() == "inf":
            return float("inf")
        elif input_str.lower() == "-inf":
            return float("-inf")
        elif input_str.lower() == "nan":
            return float("nan")
        elif input_str.lower() == "-nan":
            return float("-nan")
        # Handle fractions
        elif "/" in input_str:
            numerator, denominator = input_str.split("/")
            return float(Fraction(int(numerator), int(denominator)))
        # Handle scientific notation
        elif "e" in input_str or "E" in input_str:
            return float(input_str)
        # Handle integers and decimals
        else:
            return float(input_str)
    except ValueError:
        raise ValueError(f"Invalid input format: {input_str}")


def float_to_bits(value, w, m):
    """
    Convert a floating-point value to its w-bit binary representation,
    with post-normalization rounding using guard, round, and sticky bits.
    """
    if w <= 1 or m <= 0 or m >= w:
        raise ValueError("Invalid values for w or m. Ensure w > 1, m > 0, and m < w.")

    # Calculate exponent bits and bias
    e = w - 1 - m  # Exponent bits
    bias = (1 << (e - 1)) - 1  # Bias for exponent

    # Handle special cases
    if value == 0.0:
        return 0  # Positive zero
    elif value == -0.0:
        return 1 << (w - 1)  # Negative zero
    elif value == float("inf"):
        return ((1 << e) - 1) << m  # Positive infinity
    elif value == float("-inf"):
        return (1 << (w - 1)) | (((1 << e) - 1) << m)  # Negative infinity
    elif value != value:  # NaN
        return (1 << (w - 1)) | (((1 << e) - 1) << m) | 1  # NaN with non-zero mantissa

    # Handle sign bit
    sign_bit = 0 if value >= 0 else 1
    value = abs(value)

    # Normalize the value
    if value >= 2 ** (1 - bias):  # Normalized
        exponent = 0
        while value >= 2.0:
            value /= 2.0
            exponent += 1
        while value < 1.0:
            value *= 2.0
            exponent -= 1
        exponent += bias
        raw_mantissa = (value - 1.0) * (1 << (m + 3))  # Include GRS bits
    else:  # Denormalized
        exponent = 0
        raw_mantissa = value * (1 << (m + bias + 2))  # Include GRS bits

    # Extract mantissa and GRS bits
    raw_mantissa = int(round(raw_mantissa))
    mantissa = (raw_mantissa >> 3) & ((1 << m) - 1)  # Keep m bits
    guard = (raw_mantissa >> 2) & 1
    round_bit = (raw_mantissa >> 1) & 1
    sticky = raw_mantissa & 1 or (raw_mantissa >> 3) != 0  # Sticky OR all bits below

    # Apply rounding
    if guard == 1:
        if round_bit == 1 or sticky == 1 or (mantissa & 1) == 1:
            mantissa += 1
            if mantissa >= (1 << m):  # Handle overflow in mantissa
                mantissa = 0
                exponent += 1

    # Handle overflow in exponent
    if exponent >= (1 << e):
        exponent = (1 << e) - 1  # Set to max (Infinity)
        mantissa = 0  # Clear mantissa for infinity

    # Combine sign bit, exponent, and mantissa
    bits = (sign_bit << (w - 1)) | (exponent << m) | mantissa
    return bits


def extract_fields(bits, w, m):
    """
    Extract the sign bit, mantissa, and exponent from the bit pattern.
    """
    sign_bit = (bits >> (w - 1)) & 0x1
    exponent_mask = (1 << (w - 1 - m)) - 1
    exponent = (bits >> m) & exponent_mask
    mantissa = bits & ((1 << m) - 1)
    return sign_bit, mantissa, exponent


def main():
    # Set up argument parser
    parser = argparse.ArgumentParser(
        description="Convert a real number or special value to its floating-point bit pattern."
    )
    parser.add_argument(
        "w", type=int, help="Total bit width of the floating-point number."
    )
    parser.add_argument("m", type=int, help="Bit width of the mantissa.")
    parser.add_argument(
        "number",
        type=str,
        help="Real number or special value (e.g., 314, 3.14, 3/14, -3e14, inf, -inf, nan, -nan).",
    )

    # Parse arguments
    args = parser.parse_args()

    try:
        # Parse the input number or special value
        value = parse_real_number(args.number)

        # Convert the floating-point value to its bit pattern
        bits = float_to_bits(value, args.w, args.m)

        # Extract the sign bit, mantissa, and exponent
        sign_bit, mantissa, exponent = extract_fields(bits, args.w, args.m)

        # Create the table
        table = [
            ["Sign Bit", f"{sign_bit:01b}", f"{sign_bit:01x}"],
            ["Mantissa", f"{mantissa:0{args.m}b}", f"{mantissa:0{(args.m + 3) // 4}x}"],
            [
                "Exponent",
                f"{exponent:0{args.w - 1 - args.m}b}",
                f"{exponent:0{(args.w - 1 - args.m + 3) // 4}x}",
            ],
            ["Full Bit Pattern", f"{bits:0{args.w}b}", f"{bits:0{(args.w + 3) // 4}x}"],
        ]

        # Print the table
        print(f"Floating-point bit pattern for {args.number} (w={args.w}, m={args.m}):")
        print(
            tabulate(
                table, headers=["Field", "Binary", "Hexadecimal"], tablefmt="pretty"
            )
        )
    except ValueError as e:
        print(f"Error: {e}")


if __name__ == "__main__":
    main()
