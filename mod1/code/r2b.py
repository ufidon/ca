import argparse
import re
from fractions import Fraction

def parse_rational_number(input_str):
    """
    Parse a rational number from a string in formats like:
    - Integer: "3"
    - Fraction: "1/3"
    - Decimal: "3.14"
    Returns a Fraction object.
    """
    # Match integers (e.g., "3")
    if re.match(r"^-?\d+$", input_str):
        return Fraction(int(input_str), 1)
    
    # Match fractions (e.g., "1/3")
    fraction_match = re.match(r"^(-?\d+)/(-?\d+)$", input_str)
    if fraction_match:
        numerator = int(fraction_match.group(1))
        denominator = int(fraction_match.group(2))
        return Fraction(numerator, denominator)
    
    # Match decimals (e.g., "3.14")
    decimal_match = re.match(r"^(-?\d+)\.(\d+)$", input_str)
    if decimal_match:
        integer_part = decimal_match.group(1)
        fractional_part = decimal_match.group(2)
        numerator = int(integer_part + fractional_part)
        denominator = 10 ** len(fractional_part)
        return Fraction(numerator, denominator)
    
    raise ValueError(f"Invalid input format: {input_str}")

def rational_to_binary(numerator, denominator, DIGITS=500):
    """
    Convert a rational number (numerator/denominator) to its fractional binary representation.
    Handles both terminating and repeating binary fractions.
    """
    if denominator == 0:
        raise ValueError("Denominator cannot be zero.")
    
    # Handle negative numbers
    if numerator < 0 or denominator < 0:
        sign = "-"
        numerator, denominator = abs(numerator), abs(denominator)
    else:
        sign = ""
    
    # Integer part
    integer_part = numerator // denominator
    remainder = numerator % denominator
    
    # Fractional part
    fractional_part = []
    remainders_seen = {}  # Track remainders to detect repeating sequences
    repeating_start = None
    
    digits = 0
    while remainder != 0:
        digits = digits + 1
        if digits > DIGITS:
            print("The number fractional digits is more than 500...")
            print("so the result is just an approximation.")
            break

        if remainder in remainders_seen:
            # Repeating sequence detected
            repeating_start = remainders_seen[remainder]
            break
        
        # Record the position of this remainder
        remainders_seen[remainder] = len(fractional_part)
        
        # Perform binary division
        remainder *= 2
        bit = remainder // denominator
        fractional_part.append(str(bit))
        remainder %= denominator
    
    # Construct the binary representation
    binary_fraction = sign + bin(integer_part)[2:]  # Integer part in binary
    if fractional_part:
        binary_fraction += "."  # Add decimal point
        if repeating_start is not None:
            # Add non-repeating and repeating parts
            binary_fraction += "".join(fractional_part[:repeating_start])
            binary_fraction += "(" + "".join(fractional_part[repeating_start:]) + ")"
        else:
            # Terminating fraction
            binary_fraction += "".join(fractional_part)
    
    return binary_fraction

def main():
    # Set up argument parser
    parser = argparse.ArgumentParser(description="Convert a rational number to its fractional binary representation.")
    parser.add_argument("number", type=str, help="Rational number in formats like 3, 1/3, or 3.14.")
    
    # Parse arguments
    args = parser.parse_args()
    
    try:
        # Parse the input into a Fraction object
        fraction = parse_rational_number(args.number)
        numerator = fraction.numerator
        denominator = fraction.denominator
        
        # Convert to binary
        binary_representation = rational_to_binary(numerator, denominator)
        print(f"Binary representation of {args.number}: {binary_representation}")
    except ValueError as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()