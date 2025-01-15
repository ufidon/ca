import argparse
from tabulate import tabulate

def get_bit_pattern(value, width):
    """
    Get the bit pattern of a value as a string, padded to the specified width.
    """
    return f"{value & ((1 << width) - 1):0{width}b}"

def bits_to_float(bits, w, m):
    """
    Convert a bit pattern to its corresponding floating-point value.
    """
    sign_bit = (bits >> (w - 1)) & 0x1  # Extract the sign bit
    exponent_bits = (bits >> m) & ((1 << (w - 1 - m)) - 1)  # Extract the exponent bits
    mantissa_bits = bits & ((1 << m) - 1)  # Extract the mantissa bits
    
    bias = (1 << (w - 1 - m - 1)) - 1  # Bias for the exponent
    
    if exponent_bits == 0:  # Denormalized or zero
        if mantissa_bits == 0:  # Zero
            return -0.0 if sign_bit else 0.0
        else:  # Denormalized
            value = mantissa_bits / (1 << m)  # Fractional part
            return -value if sign_bit else value
    elif exponent_bits == (1 << (w - 1 - m)) - 1:  # Infinity or NaN
        if mantissa_bits == 0:  # Infinity
            return float("-inf") if sign_bit else float("inf")
        else:  # NaN
            return float("nan")
    else:  # Normalized
        exponent = exponent_bits - bias
        mantissa = 1 + (mantissa_bits / (1 << m))  # Implicit leading 1
        value = mantissa * (2 ** exponent)
        return -value if sign_bit else value

def generate_floating_point_bit_patterns(w, m):
    """
    Generate bit patterns and floating-point values for special floating-point values given total bits w and mantissa bits m.
    Also compute the total number of floating-point numbers for each type.
    """
    if w <= 1 or m <= 0 or m >= w:
        raise ValueError("Invalid values for w or m. Ensure w > 1, m > 0, and m < w.")
    
    # Calculate exponent bits
    e = w - 1 - m  # Exponent bits
    bias = (1 << (e - 1)) - 1  # Bias for exponent
    
    # Special values
    sign_bit = 1  # Negative
    max_exponent = (1 << e) - 1  # All exponent bits set to 1
    
    # −∞ (Negative Infinity)
    neg_inf = (sign_bit << (w - 1)) | (max_exponent << m)  # Sign bit + max exponent + zero mantissa
    neg_inf_bits = get_bit_pattern(neg_inf, w)
    neg_inf_value = bits_to_float(neg_inf, w, m)
    
    # NaN (Not a Number)
    nan = (sign_bit << (w - 1)) | (max_exponent << m) | 1  # Sign bit + max exponent + non-zero mantissa
    nan_bits = get_bit_pattern(nan, w)
    nan_value = bits_to_float(nan, w, m)
    
    # −Normalized (Min and Max)
    min_neg_norm = (sign_bit << (w - 1)) | (1 << m)  # Sign bit + smallest exponent (1) + zero mantissa
    max_neg_norm = (sign_bit << (w - 1)) | ((max_exponent - 1) << m) | ((1 << m) - 1)  # Sign bit + max exponent - 1 + max mantissa
    min_neg_norm_bits = get_bit_pattern(min_neg_norm, w)
    max_neg_norm_bits = get_bit_pattern(max_neg_norm, w)
    min_neg_norm_value = bits_to_float(min_neg_norm, w, m)
    max_neg_norm_value = bits_to_float(max_neg_norm, w, m)
    
    # −Denorm (Min and Max)
    min_neg_denorm = (sign_bit << (w - 1)) | 1  # Sign bit + zero exponent + smallest non-zero mantissa
    max_neg_denorm = (sign_bit << (w - 1)) | ((1 << m) - 1)  # Sign bit + zero exponent + max mantissa
    min_neg_denorm_bits = get_bit_pattern(min_neg_denorm, w)
    max_neg_denorm_bits = get_bit_pattern(max_neg_denorm, w)
    min_neg_denorm_value = bits_to_float(min_neg_denorm, w, m)
    max_neg_denorm_value = bits_to_float(max_neg_denorm, w, m)
    
    # −0 (Negative Zero)
    neg_zero = (sign_bit << (w - 1))  # Sign bit + zero exponent + zero mantissa
    neg_zero_bits = get_bit_pattern(neg_zero, w)
    neg_zero_value = bits_to_float(neg_zero, w, m)
    
    # +0 (Positive Zero)
    pos_zero = 0  # Zero sign + zero exponent + zero mantissa
    pos_zero_bits = get_bit_pattern(pos_zero, w)
    pos_zero_value = bits_to_float(pos_zero, w, m)
    
    # +Denorm (Min and Max)
    min_pos_denorm = 1  # Zero sign + zero exponent + smallest non-zero mantissa
    max_pos_denorm = (1 << m) - 1  # Zero sign + zero exponent + max mantissa
    min_pos_denorm_bits = get_bit_pattern(min_pos_denorm, w)
    max_pos_denorm_bits = get_bit_pattern(max_pos_denorm, w)
    min_pos_denorm_value = bits_to_float(min_pos_denorm, w, m)
    max_pos_denorm_value = bits_to_float(max_pos_denorm, w, m)
    
    # +Normalized (Min and Max)
    min_pos_norm = (1 << m)  # Zero sign + smallest exponent (1) + zero mantissa
    max_pos_norm = ((max_exponent - 1) << m) | ((1 << m) - 1)  # Zero sign + max exponent - 1 + max mantissa
    min_pos_norm_bits = get_bit_pattern(min_pos_norm, w)
    max_pos_norm_bits = get_bit_pattern(max_pos_norm, w)
    min_pos_norm_value = bits_to_float(min_pos_norm, w, m)
    max_pos_norm_value = bits_to_float(max_pos_norm, w, m)
    
    # +∞ (Positive Infinity)
    pos_inf = (max_exponent << m)  # Zero sign + max exponent + zero mantissa
    pos_inf_bits = get_bit_pattern(pos_inf, w)
    pos_inf_value = bits_to_float(pos_inf, w, m)
    
    # NaN (Not a Number)
    pos_nan = (max_exponent << m) | 1  # Zero sign + max exponent + non-zero mantissa
    pos_nan_bits = get_bit_pattern(pos_nan, w)
    pos_nan_value = bits_to_float(pos_nan, w, m)
    
    # Create a table of results
    table = [
        ["−∞", neg_inf_bits, neg_inf_value],
        ["NaN", nan_bits, nan_value],
        ["Min −Normalized", min_neg_norm_bits, min_neg_norm_value],
        ["Max −Normalized", max_neg_norm_bits, max_neg_norm_value],
        ["Min −Denorm", min_neg_denorm_bits, min_neg_denorm_value],
        ["Max −Denorm", max_neg_denorm_bits, max_neg_denorm_value],
        ["-0", neg_zero_bits, neg_zero_value],
        ["+0", pos_zero_bits, pos_zero_value],
        ["Min +Denorm", min_pos_denorm_bits, min_pos_denorm_value],
        ["Max +Denorm", max_pos_denorm_bits, max_pos_denorm_value],
        ["Min +Normalized", min_pos_norm_bits, min_pos_norm_value],
        ["Max +Normalized", max_pos_norm_bits, max_pos_norm_value],
        ["+∞", pos_inf_bits, pos_inf_value],
        ["NaN", pos_nan_bits, pos_nan_value],
    ]
    
    # Calculate the total number of floating-point numbers for each type
    num_neg_norm = (max_exponent - 1) * (1 << m)  # Number of negative normalized numbers
    num_neg_denorm = (1 << m) - 1  # Number of negative denormalized numbers
    num_pos_norm = (max_exponent - 1) * (1 << m)  # Number of positive normalized numbers
    num_pos_denorm = (1 << m) - 1  # Number of positive denormalized numbers
    num_zero = 2  # Two zeros: +0 and -0
    num_inf = 2  # Two infinities: +∞ and -∞
    num_nan = 2 * ((1 << m) - 1)  # Number of NaNs (all non-zero mantissas for both signs)
    
    # Create a table for counts
    count_table = [
        ["Negative Normalized", num_neg_norm],
        ["Negative Denormalized", num_neg_denorm],
        ["Positive Normalized", num_pos_norm],
        ["Positive Denormalized", num_pos_denorm],
        ["Zeros", num_zero],
        ["Infinities", num_inf],
        ["NaNs", num_nan],
    ]
    
    return table, count_table

def main():
    # Set up argument parser
    parser = argparse.ArgumentParser(description="Generate bit patterns, floating-point values, and counts for floating-point numbers.")
    parser.add_argument("w", type=int, help="Total bit width of the floating-point number.")
    parser.add_argument("m", type=int, help="Bit width of the mantissa.")
    
    # Parse arguments
    args = parser.parse_args()
    
    try:
        # Generate bit patterns, floating-point values, and counts
        bit_pattern_table, count_table = generate_floating_point_bit_patterns(args.w, args.m)
        
        # Print the bit patterns and floating-point values table
        print(f"Bit patterns and floating-point values (w={args.w}, m={args.m}):")
        print(tabulate(bit_pattern_table, headers=["Value", "Bit Pattern", "Floating Value"], tablefmt="pretty"))
        
        # Print the counts table
        print("\nTotal number of floating-point numbers for each type:")
        print(tabulate(count_table, headers=["Type", "Count"], tablefmt="pretty"))
    except ValueError as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()