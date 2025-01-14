# Integer Encoding and Arithmetic

---

## **PART I: Manual Calculation**

---

### **1. Unsigned Short Integer: Interesting Values**
- A `unsigned short` in C is typically **16 bits**.
- Complete the table with the following values: **maximum**, **1**, and **minimum**.
- Represent each value in **decimal**, **hexadecimal**, and **binary**.

| Value     | Decimal | Hexadecimal | Binary               |
|-----------|---------|-------------|----------------------|
| Maximum   |         |             | 1111111111111111     |
| 1         |         | 0x0001      |                      |
| Minimum   | 0       |             |                      |

- Does the function below **depend on endianness**?
```c
void print_binary(short n) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
}
```

---

### **2. Signed Short Integer: Interesting Values**
- A `signed short` in C is typically **16 bits** and uses **two's complement** encoding.
- Complete the table with the following values: **maximum**, **1**, **0**, **-1**, and **minimum**.
- Represent each value in **decimal**, **hexadecimal**, and **binary**.

| Value     | Decimal | Hexadecimal | Binary               |
|-----------|---------|-------------|----------------------|
| Maximum   | 32767   |             |                      |
| 1         |         | 0x0001      |                      |
| 0         |         |             | 0000000000000000     |
| -1        | -1      |             |                      |
| Minimum   |         |             | 1000000000000000     |

---

### **3. Unsigned Short Integer: Operations**
- Perform the following operations for `unsigned short`:
  - **Normal case**, **overflow**, and **underflow**.
- Provide examples for **addition**, **subtraction**, **multiplication**, and **division**.
  - Note: there are many solutions.

#### Example Table:

| Operation   | Example                     | Result (Decimal) | Overflow/Underflow? |
|-------------|-----------------------------|------------------|---------------------|
| Addition    |                             | 0                | Overflow            |
| Subtraction |                             | 20255            | Underflow           |
| Multiplication |                          | 2000             | Overflow            |
| Division    | 65535 / 2                   | 32767            | None                |

---

### **4. Signed Short Integer: Operations**
- Perform the following operations for `signed short`:
  - **Normal case**, **overflow**, and **underflow**.
- Provide examples for **addition**, **subtraction**, **multiplication**, and **division**.
  - Note: there are many solutions.

#### Example Table:

| Operation   | Example                     | Result (Decimal) | Overflow/Underflow? |
|-------------|-----------------------------|------------------|---------------------|
| Addition    |                             | -2025            | Overflow            |
| Addition    |                             |  2025            | Underflow           |
| Subtraction |                             | 31415            | Underflow           |
| Subtraction |                             | -31415           | Overflow            |
| Multiplication |                          | 2025             | Overflow            |
| Multiplication |                          | 2025             | Underflow           |
| Division    | -32768 / 2                  | -16384           | None                |

---

### **5. Math Functions for Casting**
- Find the piece-wise functions for:
  - Casting `unsigned short` to `signed short`.
  - Casting `signed short` to `unsigned short`.
- Draw the figures for the functions found:
  - function: `unsigned short` → `signed short`
  - function: `signed short` → `unsigned short`

#### Casting Rules:
1. **Unsigned to Signed**:
   - If the value is ≤ 32767, it remains the same.
   - If the value is > 32767, it wraps around (e.g., 65535 becomes -1).
2. **Signed to Unsigned**:
   - If the value is ≥ 0, it remains the same.
   - If the value is < 0, it wraps around (e.g., -1 becomes 65535).

---

### **6. C Expression Analysis**
- For each expression, determine if it always yields **1 (true)** (explain). If not, provide a counterexample.
  - x, y are any signed short integers
  - ux = (unsigned short)x; uy = (unsigned short)y;

| Expression | Always Yields 1? | Explanation/Counterexample |
|------------|------------------|----------------------------|
|  `(x<y) == (-x>-y)` |   |   |
|  `((x+y)<<4) + y-x == 17*y+15*x` |   |   |
|  `~x + ~y + 1 == ~(x+y)` |   |  |
|  `(ux-uy) == -(unsigned)(y-x)` |  |  |
|  `((x >> 2) << 2) <= x` |  |  |


---

## **PART II: Implementation in C**

---

### **Task: Implement Part I in C**
Write a C program to:
1. Print the interesting values for `unsigned short` and `signed short` in decimal, hexadecimal, and binary.
2. Demonstrate the operations (addition, subtraction, multiplication, division) for both `unsigned short` and `signed short`, including overflow and underflow cases.
3. Implement casting between `unsigned short` and `signed short`.
4. Evaluate the expressions from Part I, Question 1-6, and print the results.

- ⚠️ The compiler may not work correctly, find the problem.

---

## **Submission Guidelines**
1. Submit both the manual calculations (Part I) in the lab report and the C program (Part II) in source code.
2. Include comments in your C code to explain each step.
3. Provide description and screenshots of the program's output in the lab report for verification.
