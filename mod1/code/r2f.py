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
    Convert a floating-point value to its w-bit binary representation.
    Returns the bit pattern as an integer.
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
        mantissa = int(round((value - 1.0) * (1 << m)))
    else:  # Denormalized
        exponent = 0
        mantissa = int(round(value * (1 << (m + bias - 1))))
    
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
    parser = argparse.ArgumentParser(description="Convert a real number or special value to its floating-point bit pattern.")
    parser.add_argument("w", type=int, help="Total bit width of the floating-point number.")
    parser.add_argument("m", type=int, help="Bit width of the mantissa.")
    parser.add_argument("number", type=str, help="Real number or special value (e.g., 314, 3.14, 3/14, -3e14, inf, -inf, nan, -nan).")

    # Added -- before the arguments to ensure that -inf, -nan are treated as a positional argument and not as a flag.
    # e.g., python r2f.py -- -inf 32 23
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
            ["Exponent", f"{exponent:0{args.w - 1 - args.m}b}", f"{exponent:0{(args.w - 1 - args.m + 3) // 4}x}"],
            ["Full Bit Pattern", f"{bits:0{args.w}b}", f"{bits:0{(args.w + 3) // 4}x}"],
        ]
        
        # Print the table
        print(f"Floating-point bit pattern for {args.number} (w={args.w}, m={args.m}):")
        print(tabulate(table, headers=["Field", "Binary", "Hexadecimal"], tablefmt="pretty"))
    except ValueError as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()