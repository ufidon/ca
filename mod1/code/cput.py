import argparse
from tabulate import tabulate

def compare_integer_representations(w):
    if w <= 0:
        print("Bit width must be a positive integer.")
        return

    # Unsigned integer range
    unsigned_max = (1 << w) - 1  # 2^w - 1
    unsigned_min = 0
    unsigned_zero = 0
    unsigned_one = 1
    unsigned_neg_one = "N/A"  # Not applicable for unsigned

    # Signed integer (two's complement) range
    signed_max = (1 << (w - 1)) - 1  # 2^(w-1) - 1
    signed_min = -(1 << (w - 1))     # -2^(w-1)
    signed_zero = 0
    signed_one = 1
    signed_neg_one = -1

    # Create a table for comparison
    table = [
        ["Maximum Value", unsigned_max, signed_max],
        ["Minimum Value", unsigned_min, signed_min],
        ["Zero", unsigned_zero, signed_zero],
        ["One", unsigned_one, signed_one],
        ["-1", unsigned_neg_one, signed_neg_one],
    ]

    # Print the table
    headers = ["Property", "Unsigned", "Signed"]
    print(f"Comparison for {w}-bit integers:")
    print(tabulate(table, headers=headers, tablefmt="pretty"))

def main():
    # Set up argument parser
    parser = argparse.ArgumentParser(description="Compare unsigned and signed integer representations for a given bit width.")
    parser.add_argument("w", type=int, help="Bit width (positive integer)")
    
    # Parse arguments
    args = parser.parse_args()
    
    # Call the function with the provided bit width
    compare_integer_representations(args.w)

if __name__ == "__main__":
    main()