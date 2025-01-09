import argparse
from tabulate import tabulate

def unsigned_to_signed(unsigned_value, w):
    """
    Convert an unsigned integer to a signed integer (two's complement) of bit width w.
    """
    if unsigned_value >= (1 << w):
        raise ValueError(f"Unsigned value {unsigned_value} exceeds the range for {w}-bit integers.")
    
    # If the value is within the signed range, return it directly
    if unsigned_value < (1 << (w - 1)):
        return unsigned_value
    # Otherwise, convert to signed (two's complement)
    return unsigned_value - (1 << w)

def signed_to_unsigned(signed_value, w):
    """
    Convert a signed integer (two's complement) to an unsigned integer of bit width w.
    """
    if signed_value < -(1 << (w - 1)) or signed_value >= (1 << (w - 1)):
        raise ValueError(f"Signed value {signed_value} exceeds the range for {w}-bit integers.")
    
    # If the value is non-negative, return it directly
    if signed_value >= 0:
        return signed_value
    # Otherwise, convert to unsigned
    return signed_value + (1 << w)

def get_bit_pattern(value, w):
    """
    Get the bit pattern of a value as a string, padded to width w.
    """
    return f"{value & ((1 << w) - 1):0{w}b}"  # Mask and format to w bits

def main():
    # Set up argument parser
    parser = argparse.ArgumentParser(description="Convert between signed and unsigned integers and display their bit patterns.")
    parser.add_argument("type", choices=["s", "u"], help="Type of input: 's' for signed, 'u' for unsigned.")
    parser.add_argument("value", type=int, help="The integer value to convert.")
    parser.add_argument("width", type=int, help="The bit width of the integer.")
    
    # Parse arguments
    args = parser.parse_args()
    
    # Perform conversion based on input type
    if args.type == "s":
        # Input is signed
        signed_value = args.value
        unsigned_value = signed_to_unsigned(signed_value, args.width)
    else:
        # Input is unsigned
        unsigned_value = args.value
        signed_value = unsigned_to_signed(unsigned_value, args.width)
    
    # Get bit patterns
    signed_bits = get_bit_pattern(signed_value, args.width)
    unsigned_bits = get_bit_pattern(unsigned_value, args.width)
    
    # Create table
    table = [
        [signed_value, signed_bits, unsigned_value, unsigned_bits]
    ]
    
    # Print table
    headers = ["Signed", "Bit Pattern", "Unsigned", "Bit Pattern"]
    print(tabulate(table, headers=headers, tablefmt="pretty"))

if __name__ == "__main__":
    main()