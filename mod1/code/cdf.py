from decimal import Decimal, getcontext

"""
**Comparison: C vs. Python

| Feature                | C (IEEE 754-2008)                     | Python (`decimal` module)             |
|------------------------|---------------------------------------|---------------------------------------|
| **Types**              | `_Decimal128`, `_Decimal64`, `_Decimal32` | `Decimal` (arbitrary precision)       |
| **Precision**          | Fixed (34, 16, 7 decimal digits)      | Arbitrary (set by `getcontext().prec`)|
| **Ease of Use**        | Requires compiler support and casting | Easy to use, part of the standard library |
| **Portability**        | Limited to compilers supporting DFP   | Works on all Python implementations   |
| **Use Case**           | Low-level systems programming         | High-level applications, financial calculations |
"""

# Set the precision (number of significant digits)
getcontext().prec = 50

# Create decimal floating-point numbers
d1 = Decimal('1234567890123456789012345678901234.0')
d2 = Decimal('1234567890123456.0')
d3 = Decimal('1234567.0')

# Perform arithmetic operations
result = d1 + d2 * d3

# Print results
print("d1:", d1)
print("d2:", d2)
print("d3:", d3)
print("Result of d1 + d2 * d3:", result)