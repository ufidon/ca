# Representing and Manipulating Information
CS:APP3e.ch02

Floating Point
---

## Decimal notation of rational numbers
- Base 10: *decimal point*
  - $2025.5205_{10} = 2 \times 10^3 + 0 \times 10^2 + 2 \times 10^1 + 5 \times 10^0 + 5 \times 10^{-1} + 2 \times 10^{-2} + 0 \times 10^{-3} + 5 \times 10^{-4}$
- Base 2: *binary point*
  - $11011.11011_2 = 1 \times 2^4 + 1 \times 2^3 + 0 \times 2^2 + 1 \times 2^1 + 1 \times 2^0 + 1 \times 2^{-1} + 1 \times 2^{-2} + 0 \times 2^{-3} + 1 \times 2^{-4} + 1 \times 2^{-5}$
- Base 16: *hexadecimal point*
  - $feed.beef_{16} = 15 \times 16^3 + 14 \times 16^2 + 14 \times 16^1 + 13 \times 16^0 + 11 \times 16^{-1} + 14 \times 16^{-2} + 14 \times 16^{-3} + 15 \times 16^{-4}$
- 📝 Practice
  - Convert $2025.5205_{10}$ to binary and hexadecimal
  - Convert $11011.11011_2$ to decimal and hexadecimal
  - Convert $feed.beef_{16}$ to binal and decimal
- 📝 Practice
  - What will happen when we move the point leftward or rightward?

---

## Generalized Formula for a Rational Number $R$ in Base $b$
- $R = I + F = (d_n d_{n-1} \dots d_1 d_0 . d_{-1} d_{-2} \dots d_{-m})_b$
  - Integer part = $I = \sum_{i=0}^n d_i \cdot b^i$
  - Fractional part = $\sum_{j=1}^m d_{-j} \cdot b^{-j}$
  - The $b$ digits $d_i,\ i=0,1,⋯, b-1$ must satisfy $0 \leq d_i < b$.
- **Fractional binary numbers**
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
- 📝 Convert 314, 3.14, 3/14 into fractional binary numbers
  - check your solution with [r2b.py](./code/r2b.py)

---

## IEEE Floating Point Standard  
- Established in 1985 as a uniform standard [IEEE 754](https://en.wikipedia.org/wiki/IEEE_754) for floating-point arithmetic.    
- Driven by numerical concerns:  
  - Standards for rounding, overflow, and underflow.  
  - Ensures consistency across hardware and software.  
- Supported by all major CPUs.

---

## Floating Point Representation  
- Uses $V = (-1)^s \cdot M \cdot 2^E$ to represent a `wide range` of rational numbers
  - **Sign bit (s):** Determines if the number is negative or positive.  
  - **Significand (M):** Fractional value in the range [1.0, 2.0).  
  - **Exponent (E):** Weights the value by a power of 2. 
- Encoding:  
  - **Sign bit (s):** 1 bit (1 negative, 0 positive)
  - **Exponent (exp):** encodes E (biased)
  - **Fraction (frac):** encodes M (called Mantissa)
    - represents the fractional value $0≤ f <1$
- Supports efficient computations on very large $|V|≫0$ and very small $|V|≪1$
  - a set of finite numbers: 
    - `normalized` values, 
    - `denormalized` values (including `+0` and `-0`)
  - two infinities: `+∞` and `-∞`
  - two kinds of NaN: a quiet NaN (`qNaN`) and signaling NaN (`sNaN`)

---

## Precision Options  
| Precision | Total Bits | Sign Bit (s) | Exponent (exp) | Fraction (frac)  |
|------|------------|----------|----------|-------|
| Single Precision | 32  | 1 | 8 | 23      |
| Double Precision | 64  | 1 | 11| 52      |
| [Extended Precision](https://en.wikipedia.org/wiki/Extended_precision)<br>(x86 architectures) | 80  | 1 | 15| 64|

- Categories of single-precision floating-point values
  - [fp categories](./imgs/fp-cases.png)

---

## Normalized Values
- Values with  `000…0 < exp < 111…1=2ᵏ` as unsigned integer
  - i.e. exp in the range 1 to 2ᵏ-2
- Exponent:  $E = \text{exp} - \text{bias}$  
  - bias  = 2ᵏ⁻¹ - 1 
  - where $k$ is the number of exponent bits.  

| Precision  | Exponent Bits (k) | bias (2ᵏ⁻¹ - 1) | Exponent Range (exp)<br>1 to 2ᵏ-2 | Actual Exponent (E)<br>-(2ᵏ⁻¹-2) to 2ᵏ⁻¹ - 1 |
|------------|-------------------|------------------|----------------------|---------------------|
| Single Precision    | 8        | 127     | 1 to 254    | -126 to 127 |
| Double Precision    | 11       | 1023    | 1 to 2046   | -1022 to 1023       |
| Extended Precision  | 15       | 16383   | 1 to 32766  | -16382 to 16383     |

- Significand coded with `implied leading 1`: $M = 1+f = 1.\text{frac}$  
  - Minimum when frac=000⋯0 ($M_{min} = 1.0$)
  - Maximum when frac=111⋯1 ($M_{max} = 2.0 – ε$)
- 📝 For each precision, find
  - the total number of normalized values (don't miss the sign bit)
    - $2 ⋅ 2^m ⋅ (E_{max} - 1)$
  - the maximum and minimum normalized values in magnitude
    - $M_{max} ⋅ 2^{E_{max}}$, $M_{min} ⋅ 2^{E_{min}}$

---

## 🍎 Encoding the Number 6.75 in IEEE 754 Single Precision
- ➊ Convert to binary: 6.75 → 110.11
- ➋ Normalize the binary number: 110.11 → 1.1011 × 2² = 1.10110000000000000000000 × 2²
  - ∴ frac = 10110000000000000000000 (drop the leading 1.), E = 2
- ➌ Calculate the biased exponent:
  - $E = \text{exp} - \text{bias} ⇒ 2 = \text{exp} - 127 ⇒ \text{exp}=129=10000001_2$
- ➍ Assemble the components: 

| Component  | Bits                      | Value                     |
|------------|---------------------------|---------------------------|
| Sign       | 1                         | 0 (positive)              |
| Exponent   | 8                         | 10000001 (129 in decimal) |
| Fraction   | 23                        | 10110000000000000000000   |

- Final IEEE 754 encoding (Hex): `0x40D80000`
- 📝 Encode -6.75 in IEEE 754 single precision and double precision
  - Check your solution with [me.c](./code/me.c) or [r2f.py](./code/r2f.py)

---

## [Denormalized Values](https://en.wikipedia.org/wiki/Subnormal_number)
- Values with `exp = 000…0`
  - used to fill the gap between `zero` and the `smallest normalized number in magnitude` (what is it?)
- Exponent designed as: $E = 1 - \text{bias}$  (instead of $E = 0 - \text{bias}$)
- Significand coded with implied leading 0:  $M = f = 0.\text{frac}$
  - This allows for a gradual underflow and smaller numbers to be represented
- Special cases:  
  - **Zero:** `exp = 000…0`, `frac = 000…0`
    - Note +0 and -0 has distinct code 
  - **Numbers very close to Zero:** `exp = 000…0`, `frac ≠ 000…0`
    - These numbers are equispaced (what is the space?)
- 🍎 Single Precision (32-bit)
  - The smallest normalized number:  
    - $1.0 \times 2^{-126} \approx 1.17549410^{-38}$
  - The smallest denormalized number: 
    - $0.00000000000000000000001_2 \times 2^{-126} = 2^{-23} \times 2^{-126} = 2^{-149}≈1.401298^{-45}$
- 📝 find the smallest normalized number and denormalized number for double, long double
  - verify your solution with [min.c](./code/min.c)

---

## Special Values  
- `Infinity ∞` with `exp = 111…1`, `frac = 000…0`.
  - Represents overflow or division by zero. 
  - e.g., 1.0/0.0 = −1.0/−0.0 = +∞,  1.0/−0.0 = -1.0/0.0 = −∞
- `NaN` (Not a Number) with `exp = 111…1`, `frac ≠ 000…0`.  
  - Represents undetermined results (e.g., $\sqrt{-1}$, ∞-∞, 0/0).  
- 📝 Practice these special values in [C](./code/sv.c)

---

## Distribution of Floating-Point encodings

| **Category**    | **Sign Bit** | **Exponent**       | **Mantissa**       | **Description**                                                   |
|-----------------|--------------|--------------------|--------------------|-------------------------------------------------------------------|
| **NaN**         | 1            | All 1s             | Non-zero           | Not a Number, represents undefined or unrepresentable results.    |
| **−∞**          | 1            | All 1s             | All 0s             | Negative infinity, represents the smallest possible value.        |
| **−Normalized** | 1            | Not all 0s or 1s   | Normalized         | Negative real numbers with full precision.                        |
| **−Denorm**     | 1            | All 0s             | Non-zero           | Very small negative numbers close to zero, with reduced precision.|
| **−0**          | 1            | All 0s             | All 0s             | Negative zero, distinct from +0 in some operations.               |
| **+0**          | 0            | All 0s             | All 0s             | Positive zero, distinct from −0 in some operations.               |
| **+Denorm**     | 0            | All 0s             | Non-zero           | Very small positive numbers close to zero, with reduced precision.|
| **+Normalized** | 0            | Not all 0s or 1s   | Normalized         | Positive real numbers with full precision.                        |
| **+∞**          | 0            | All 1s             | All 0s             | Positive infinity, represents the largest possible value.         |
| **NaN**         | 0            | All 1s             | Non-zero           | Not a Number, represents undefined or unrepresentable results.    |


## Interesting Floating Point Values
| **Type** | **Bit Representation**| **Fraction/Significand (M)** | **Exponent (E)**  | **Numeric Value (V)** |
|-----|------------|-----|---------|---|
| **+0.0** | All zeros  | $M = 0$   | $E = 0$  | $V = 0$ |
| **Smallest Positive Denormalized**| 1 in the least significant bit, otherwise all zeros| $M = f = 2^{-m}$ | $E = -2^{k-1} + 2$ | $V = 2^{-m - 2^{k-1} + 2}$  |
| **Largest Denormalized**| Exponent field: all zeros; Fraction field: all ones| $M = f = 1 - 2^{-m}$| $E = -2^{k-1} + 2$ | $V = (1 - 2^{-m}) \times 2^{-2^{k-1} + 2}$ |
| **Smallest Positive Normalized**  | 1 in the least significant bit of the exponent field, otherwise all zeros   | $M = 1$   | $E = -2^{k-1} + 2$ | $V = 2^{-2^{k-1} + 2}$ |
| **Value 1.0** | All but the most significant bit of the exponent field equal to 1, others equal to 0  | $M = 1$   | $E = 0$  | $V = 1$ |
| **Largest Normalized**  | Sign bit: 0; Least significant bit of exponent: 0; Others: 1 | $M = 1+f= 2 - 2^{-m}$ | $E = 2^{k-1} - 1$  | $V = (2 - 2^{-m}) \times 2^{2^{k-1} - 1} = (1 - 2^{-m-1}) \times 2^{2^{k-1}}$  |

- 📝 Find the bit patterns and decimal values of the minimums and maximums of
  - -normalized, -denormalized, +denormalized, and +normalized
  - check you solution with [fv.py](./code/fv.py)

---

## Counts of Floating-Point Numbers

| **Type**     | **Formula**| **Explanation**|
|-------------|-------------|-----------|
| **Negative Normalized**    | `(2ᵏ-2) * (1 << m)`     | Number of negative normalized numbers.   |
| **Positive Normalized**    | `(2ᵏ-2) * (1 << m)`     | Number of positive normalized numbers.   |
| **Negative Denormalized**  | `(1 << m) - 1`   | Number of negative denormalized numbers. |
| **Positive Denormalized**  | `(1 << m) - 1`   | Number of positive denormalized numbers. |
| **Zeros**    | `2` | Two zeros: +0 and -0.      |
| **Infinities**     | `2` | Two infinities: +∞ and -∞. |
| **NaNs**     | `2 * ((1 << m) - 1)`   | Number of NaNs (all non-zero mantissas for both signs).     |

- 📝 Fill out the table for single and double precisions.
  - check your solution with [floatdist.py](./code/floatdist.py)

---

## Tiny Floating Point Examples
- 8-bit IEEE-like floating point representation

| s | exp | frac |
|--|--|--|
| 1 | 4-bits | 3-bits |

- 6-bit IEEE-like floating point representation

| s | exp | frac |
|--|--|--|
| 1 | 3-bits | 2-bits |

- Complete range of 6-bit IEEE-like floating point values
  - ![complete distribution](./imgs/fp-values-full.png)
- 6-bit IEEE-like floating point values between -1.0 and +1.0
  - ![unit distribution](./imgs/fp-values-small.png)

- 5-bit IEEE-like floating point representation

| s | exp | frac |
|--|--|--|
| 1 | 2-bits | 2-bits |

- 📝 find all interesting values and their representations
  - normalized, denormalized, ±0, NaN, ±∞
  - verify your solution with [fv.py](./code/fv.py) and [floatdist.py](./code/floatdist.py)

---

## Special Properties of IEEE Encoding
- FP zero has the same bit encoding as integer zero
  - all bits = 0
- Can (almost) use unsigned integer comparison.  
  - Must first compare sign bits.  
    - Must specify -0 = 0.  
  - NaNs are problematic:  
    - Greater than ∞ and any finite values.  
    - The comparison of NaN with any value (including another NaN) is undefined or implementation-dependent 
  - Otherwise, comparisons are generally okay.  
  - Considerations needed for different bit representations:  
    - Denormalized numbers vs. normalized numbers.  
    - Normalized numbers vs. infinity.
      - ∞ > any finite values
- 📝 In C/C++, compare all the special values with all relational operators:
  - NaN, ∞, -∞, +0, -0, 1.0, -1.0
  - ref to [sv.c](./code/sv.c) for creating special values

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