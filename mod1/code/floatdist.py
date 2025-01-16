import sys
from tabulate import tabulate


def print_table(w, m):
    # Calculate k (exponent bits)
    k = w - m - 1  # w = k + m + 1 (sign bit)

    # Compute values for the table
    negative_normalized = (2**k - 2) * (1 << m)
    positive_normalized = (2**k - 2) * (1 << m)
    negative_denormalized = (1 << m) - 1
    positive_denormalized = (1 << m) - 1
    zeros = 2
    infinities = 2
    nans = 2 * ((1 << m) - 1)

    # Prepare the table data
    table = [
        [
            "Negative Normalized",
            f"(2^{k}-2) * (1 << {m})",
            negative_normalized,
            "Number of negative normalized numbers.",
        ],
        [
            "Positive Normalized",
            f"(2^{k}-2) * (1 << {m})",
            positive_normalized,
            "Number of positive normalized numbers.",
        ],
        [
            "Negative Denormalized",
            f"(1 << {m}) - 1",
            negative_denormalized,
            "Number of negative denormalized numbers.",
        ],
        [
            "Positive Denormalized",
            f"(1 << {m}) - 1",
            positive_denormalized,
            "Number of positive denormalized numbers.",
        ],
        ["Zeros", "2", zeros, "Two zeros: +0 and -0."],
        ["Infinities", "2", infinities, "Two infinities: +∞ and -∞."],
        [
            "NaNs",
            f"2 * ((1 << {m}) - 1)",
            nans,
            "Number of NaNs (all non-zero mantissas).",
        ],
    ]

    # Print the table using tabulate
    headers = ["Type", "Formula", "Value", "Explanation"]
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

    print_table(w, m)
