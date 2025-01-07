# Representing and Manipulating Information
CS:APP3e.ch02

Floating Point
---

## Decimal notation of rational numbers
- Base 10: 
  - $2025.5205_{10} = 2 \times 10^3 + 0 \times 10^2 + 2 \times 10^1 + 5 \times 10^0 + 5 \times 10^{-1} + 2 \times 10^{-2} + 0 \times 10^{-3} + 5 \times 10^{-4}$
- Base 2:
  - $11011.11011_2 = 1 \times 2^4 + 1 \times 2^3 + 0 \times 2^2 + 1 \times 2^1 + 1 \times 2^0 + 1 \times 2^{-1} + 1 \times 2^{-2} + 0 \times 2^{-3} + 1 \times 2^{-4} + 1 \times 2^{-5}$
- Base 16:
  - $feed.beef_{16} = 15 \times 16^3 + 14 \times 16^2 + 14 \times 16^1 + 13 \times 16^0 + 11 \times 16^{-1} + 14 \times 16^{-2} + 14 \times 16^{-3} + 15 \times 16^{-4}$
- 📝 Practice
  - Convert $2025.5205_{10}$ to binary and hexadecimal
  - Convert $$11011.11011_2$ to decimal and hexadecimal
  - Convert $feed.beef_{16}$ to binal and decimal

---

## Generalized Formula for a Rational Number $R$ in Base $b$
- $R = I + F = (d_n d_{n-1} \dots d_1 d_0 . d_{-1} d_{-2} \dots d_{-m})_b$
  - Integer part = $I = \sum_{i=0}^n d_i \cdot b^i$
  - Fractional part = $\sum_{j=1}^m d_{-j} \cdot b^{-j}$
  - The $b$ digits $d_i,\ i=0,1,⋯, b-1$ must satisfy $0 \leq d_i < b$.
- Fractional binary numbers
  - $R = I + F = (d_n d_{n-1} \dots d_1 d_0 . d_{-1} d_{-2} \dots d_{-m})_2$
  - = $\sum_{i=0}^n d_i \cdot 2^i + \sum_{j=1}^m d_{-j} \cdot 2^{-j}$
  - binary digits: 0,1
- 📝 Represent the fractional decimal numbers in fractional binary numbers
  - 5 and 3/4, 3 and 7/8, 1 and 11/16
- 📝 What is the limit of 0.1111111⋯₂ when the number of digit 1 → ∞?
  - 0.1111111⋯₂ is notated as 1.0-ϵ

---

## Limitations of fractional binary numbers
- Limitation ➊: 
  - Can only exactly represent numbers of the form x/2ᵏ
  - Other rational numbers have repeating bit representations

| Value   | Representation    |
|---------|---------------------------------|
| 1/3     | 0.0101010101[01]…₂|
| 1/5     | 0.001100110011[0011]…₂   |
| 1/10    | 0.0001100110011[0011]…₂  |

- Limitation ➋:
  - Just one setting of binary point within the w bits
    - called `fixed-point`
  - Limited range of numbers (📝 find the range of $w_i$ bits.$`w_f`$ bits)

---

## IEEE Floating Point Standard  
- Established in 1985 as a uniform standard [IEEE 754](https://en.wikipedia.org/wiki/IEEE_754) for floating-point arithmetic.    
- Driven by numerical concerns:  
  - Standards for rounding, overflow, and underflow.  
  - Ensures consistency across hardware and software.  
- Supported by all major CPUs.

---

## Floating Point Representation  
- $\text{Value} = (-1)^s \cdot M \cdot 2^E$  
  - **Sign bit (s):** Determines if the number is negative or positive.  
  - **Significand (M):** Fractional value in the range [1.0, 2.0).  
  - **Exponent (E):** Weights (unsigned) the value by a power of two.  
- Encoding:  
  - **Sign bit (s):** 1 bit 
  - **Exponent (exp):** encodes E (biased)
  - **Fraction (frac):** encodes M (called Mantissa)

---

## Precision Options  
| Precision | Total Bits | Sign Bit | Exponent | Fraction  |
|------|------------|----------|----------|-------|
| Single Precision | 32  | 1 | 8 | 23      |
| Double Precision | 64  | 1 | 11| 52      |
| Extended Precision<br>(x86 architectures) | 80  | 1 | 15| 64|
 
---

## Normalized Values
- Values with  `exp ≠ 000…0` and `exp ≠ 111…1=2ᵏ`
  - i.e. exp in the range 1 to 2ᵏ-2
- Exponent:  $E = \text{Exp} - \text{Bias}$  
  - Bias  = 2ᵏ⁻¹ - 1
  - where $k$ is the number of exponent bits.  

| Precision  | Exponent Bits (k) | Bias (2ᵏ⁻¹ - 1) | Exponent Range (Exp) | Actual Exponent (E) |
|------------|-------------------|------------------|----------------------|---------------------|
| Single Precision    | 8        | 127     | 1 to 254    | -126 to 127 |
| Double Precision    | 11       | 1023    | 1 to 2046   | -1022 to 1023       |
| Extended Precision  | 15       | 16383   | 1 to 32766  | -16382 to 16383     |


- Significand coded with implied leading 1: $M = 1.\text{frac}$  
  - Minimum when frac=000⋯0 (M = 1.0)
  - Maximum when frac=111⋯1 (M = 2.0 – ε)

---

## 🍎 Encoding the Number 6.75 in IEEE 754 Single Precision
- Convert to binary: 6.75 → 110.11
- Normalize the binary number: 110.11 → 1.1011 × 2² = 1.10110000000000000000000 × 2²
  - ∴ frac = 10110000000000000000000 (drop the leading 1.), E = 2
- Calculate the biased exponent:
  - $E = \text{Exp} - \text{Bias} ⇒ 2 = \text{Exp} - 127 ⇒ \text{Exp}=129=10000001_2$
- Assemble the components: 

| Component  | Bits                      | Value                     |
|------------|---------------------------|---------------------------|
| Sign       | 1                         | 0 (positive)              |
| Exponent   | 8                         | 10000001 (129 in decimal) |
| Fraction   | 23                        | 10110000000000000000000   |

- Final IEEE 754 encoding (Hex): `0x40D80000`
- 📝 Encode -6.75 in IEEE 754 single precision and double precision
  - Check your answers with [me.c](./code/me.c)

---

## Denormalized Values    
- Values with `exp = 000…0`
  - used to fill the gap between zero and the `smallest normalized number` (what is it?)
- Exponent fixed as: $E = 1 - \text{Bias}$  (instead of $E = 0 - \text{Bias}$)
- Significand coded with implied leading 0:  $M = 0.\text{frac}$
  - This allows for smaller numbers to be represented 
- Special cases:  
  - **Zero:** `exp = 000…0`, `frac = 000…0`
    - Note +0 and -0 has distinct code 
  - **Closest to Zero:** `exp = 000…0`, `frac ≠ 000…0`
    - These numbers are equispaced (what is the space?)
- 🍎 Single Precision (32-bit)
  - The smallest normalized number:  $1.0 \times 2^{-126}$
  - The smallest denormalized number: $0.00000000000000000000001_2 \times 2^{-126} = 2^{-149}$


---

## Special Values  
- Infinity with `exp = 111…1`, `frac = 000…0`.
  - Represents overflow or division by zero. 
  - e.g., 1.0/0.0 = −1.0/−0.0 = +∞,  1.0/−0.0 = -1.0/0.0 = −∞
- NaN (Not a Number) with `exp = 111…1`, `frac ≠ 000…0`.  
  - Represents undefined results (e.g., $\sqrt{-1}$, ∞-∞, 0/0).  
- 📝 Practice these special values in [C](./code/sv.c)

---

## Floating Point Operations  
### Basic Idea:  
- **Addition:** $x +_f y = \text{Round}(x + y)$.  
- **Multiplication:** $x \times_f y = \text{Round}(x \times y)$.  

### Steps:  
1. Compute exact result.  
2. Fit into desired precision.  
3. Handle overflow and rounding.  

---

## Rounding  
### Rounding Modes:  
1. **Toward Zero:** Truncate.  
2. **Round Down (Toward -∞).**  
3. **Round Up (Toward +∞).**  
4. **Nearest Even (Default).**  

---

## Floating Point in C  
### Precision:  
- **Single Precision:** `float`.  
- **Double Precision:** `double`.  

### Conversions:  
- **Casting:**  
  - `int` to `float` or `double`.  
  - `float` or `double` to `int` (truncates fractional part).  

### Common Pitfalls:  
- **Precision Loss:** Not all decimal numbers can be represented exactly.  
- **Rounding Errors:** Can accumulate in complex calculations.  

---

## Summary  
### Key Takeaways:  
- **IEEE Floating Point:** Ensures consistency, precision, and portability.  
- **Form:** $M \times 2^E$.  
- **Operations:** Computed as if with perfect precision, then rounded.  

### Limitations:  
- **Not Real Arithmetic:** Violates associativity and distributivity.  
- **Precision Loss:** Not all decimal numbers can be represented exactly.  

---

## Fixed-Point vs. Floating-Point
| Feature  | Fixed-Point Representation  | Floating-Point Representation  |
|----------|----------|--------------------------------------------------|
| **Definition**  | Represents numbers with a fixed number of digits for integer and fractional parts. | Represents numbers in scientific notation, with a sign, mantissa, and exponent. |
| **Precision**   | Fixed precision for both integer and fractional parts. | Variable precision, depending on the value of the exponent. |
| **Range**| Limited range due to fixed number of digits.| Larger range due to the use of an exponent.      |
| **Usage**| Suitable for applications where range is predictable and precision is constant (e.g., financial calculations). | Suitable for applications requiring a wide range of values (e.g., scientific computations). |
| **Complexity**  | Simpler to implement and requires less hardware.   | More complex to implement due to exponent handling. |
| **Example**     | 8.75 in 8-bit fixed-point (4 integer bits, 4 fractional bits): `1000.1100` | 8.75 in 32-bit floating-point (IEEE 754): `0 10000010 00011000000000000000000` |
| **Advantages**  | - Simple and fast arithmetic operations.    | - Can represent a wide range of values.   |
|   | - Predictable precision.      | - Better suited for scientific and engineering applications. |
| **Disadvantages**      | - Limited range and precision.| - More complex arithmetic operations.     |
|   | - Inefficient for very large or very small numbers.| - Potential loss of precision due to rounding.   |