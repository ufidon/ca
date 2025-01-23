# IEEE 754 Floating-Point Number Representation and Operations

---

## **Part I: Manual Calculation**

### **1. IEEE Single-Precision Representation**
Find the IEEE single-precision (32-bit) representation of the following numbers. Show all steps, including:
- Conversion to binary.
- Normalization.
- Calculation of the biased exponent.
- Rounding and possible post normalization.
- Assembly of the sign bit, exponent, and mantissa.
  - Show the result in both binary and hexadecimal.
- Calculate the representation errors or discrepancies between the result floating numbers and the original values.

#### Numbers:
1. $1.6180339887$
2. $314159265358979$
3. $1.6726219×10^{−27}$

---

### **2. 5-Bit Floating-Point Representation**
Consider a simplified 5-bit floating-point representation with:
- **1 sign bit**
- **2 exponent bits**
- **2 mantissa bits**
- 💡 [hint](./hint.md)

#### Tasks:
1. **Categorize all possible numbers** into the following groups:
   - **NaNs**
   - **Infinities**
   - **Normalized values**
   - **Denormalized values**
   - **Zeros**

   Present the numbers in a table, showing their binary representation, category, and decimal value.

2. **Plot all values** on a horizontal axis. Place:
   - **+NaNs** to the right of **+∞**
   - **-NaNs** to the left of **-∞**
3. Draw a histogram of these categories.

---

### **3. Truth of Statements**
Given integers `x`, `y`, and `z` in 32-bit two's complement representation, let `dx`, `dy`, and `dz` be their cast to `double` (e.g., `double dy = (double) y`). Determine the truth of the following statements. For each:
- If the statement is **always true**, provide an explanation.
- If the statement is **not always true**, provide a counterexample.

Consider **normal values** as well as **special values** such as **TMin**, **TMax**, and **0**.

#### Statements:
1. `(float) x == (float) dx`
2. `dx - dy == (double) (x - y)`
3. `(dx + dy) + dz == dx + (dy + dz)`
4. `(dx * dy) * dz == dx * (dy * dz)`
5. `dx / dx == dz / dz`

---

## **Part II: Programming in C**

### **Task:**
Write a C program to verify your solutions for **Part I**. Your program should:
1. **Compute and print** the IEEE single-precision representation of the three numbers.
2. **Simulate the 5-bit floating-point representation** and print all possible values, categorized as in **Part I, Question 2**.
3. **Test the statements** in **Part I, Question 3** using specific values for `x`, `y`, and `z`. Include test cases for:
   - Normal values.
   - Special values (e.g., ±NaNs, ±∞, ±0).

### **Requirements:**
- Use **bitwise operations** to extract and manipulate the IEEE 754 representation.
- Use **type casting** and **floating-point operations** to verify the statements.
- Include **comments** in your code to explain each step.
- Take **screenshots** of the program outputs and include them in your report.

---

### **Example Code Structure:**

```c
#include <stdio.h>
#include <stdint.h>
#include <math.h>

// Function to print IEEE 754 representation of a float
void print_float_representation(float f) {
    uint32_t* p = (uint32_t*)&f;
    printf("Float: %.100e, IEEE 754: 0x%08X\n", f, *p);
}

// Function to simulate 5-bit floating-point representation
void simulate_5bit_float() {
    // Implement logic to generate and categorize all 5-bit floating-point numbers
}

// Function to test statements in Part I, Question 3
void test_statements() {
    // Implement test cases for the statements
}

int main() {
    // Part I, Question 1
    printf("Part I, Question 1:\n");
    print_float_representation(1.6180339887f);
    print_float_representation(314159265358979.0f);
    print_float_representation(1.6726219e-27f);

    // Part I, Question 2
    printf("\nPart I, Question 2:\n");
    simulate_5bit_float();

    // Part I, Question 3
    printf("\nPart I, Question 3:\n");
    test_statements();

    return 0;
}
```

---

### **Submission Guidelines:**
1. **Report:**
   - Include detailed solutions for **Part I**.
   - Attach **screenshots** of the program outputs for **Part II**.
   - Provide explanations for any discrepancies between manual calculations and program outputs.

2. **Code:**
   - Submit the C program file(s) used for **Part II**.
   - Ensure the code is well-commented and easy to understand.
