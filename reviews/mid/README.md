# Midterm Review
- Covers mod 0&1
- Only for x86-64 ISA

---

## Mod 0: Overview of Computer Architecture
- Which addition is associate?
  - Floating-point addition or integer addition?
- Why is memory access performance critical in system optimization?
- Why do you need to know assembly language?
- Explain and apply `Amdahl's law`.

---

## Mod 1: Program Structure and Construction

## Bits, Bytes, and Integers
- What are the sizes in bytes of primitive C types?
  - char(1), short(2), int(4), `long(8), long long(8)`, float(4), `double(8), long double(16), pointer(8)`
- How to represent an integer in two's complement with word width `w`?
- How to convert an unsigned integer to a signed integer of the same word width and vice versa?
- How to determine the result when the sum of two signed integers overflowed?

---

## Floating Point
- Given an IEEE-754 like floating-point representation with `(W, E, M)`, find all its interesting values.
  - W: word width in bits
  - E: exponent width in bits
  - M: mantissa width in bits

| **Category**    | **Sign Bit** | **Exponent**       | **Mantissa**       | **Description**                                                   |
|-----------------|--------------|--------------------|--------------------|-------------------------------------------------------------------|
| **NaN**         | 1            | All 1s             | Non-zero           | Not a Number, represents undefined or unrepresentable results.    |
| **−∞**          | 1            | All 1s             | All 0s             | -∞, represents the smallest possible value.        |
| **−Normalized** | 1            | Not all 0s or 1s   | Normalized         | Negative real numbers with full precision.                        |
| **−Denorm**     | 1            | All 0s             | Non-zero           | Very small negative numbers close to zero, with reduced precision.|
| **−0**          | 1            | All 0s             | All 0s             | Negative zero, distinct from +0 in some operations.               |
| **+0**          | 0            | All 0s             | All 0s             | Positive zero, distinct from −0 in some operations.               |
| **+Denorm**     | 0            | All 0s             | Non-zero           | Very small positive numbers close to zero, with reduced precision.|
| **+Normalized** | 0            | Not all 0s or 1s   | Normalized         | Positive real numbers with full precision.                        |
| **+∞**          | 0            | All 1s             | All 0s             | + ∞, represents the largest possible value.         |
| **NaN**         | 0            | All 1s             | Non-zero           | Not a Number, represents undefined or unrepresentable results.    |

- How to find the IEEE-754 like floating-point representation for a given rational number?
- Given the IEEE-754 like floating-point representation for a given rational number, how to find its decimal value?
  - [hint](../../labs/lab03/hint.md)

---

## Basics

- What are the x86-64 integer registers and their typical usages?
  - and their usages in x86-64 `Linux` calling conventions
- Explain X86-64 memory mode addressing
  - calculate memory addressing operand, i.e. do `lea`'s task manually
  - d(b,i,s) : b+i*s+d
  - d(,i,s): i*s+d
- Describe the change of `rsp` value 

---

## Control
- What are the criteria for instruction `CMP` and `TEST`?
  - What are the condition codes (or CPU flags) used for what indication?
- What are the difference between `unconditional` and `conditional` jump?
- How to determine jump offset?
  - `offset = target - the instruction following the jump`

```python
0000000000000000 <_start>:
   0:	48 89 f8             	mov    %rdi,%rax
   3:	eb 03                	jmp    8 <_start+0x8> ;➊ 0x03=0x8-0x5
   5:	48 d1 f8             	sar    %rax
   8:	48 85 c0             	test   %rax,%rax
   b:	7f f8                	jg     5 <_start+0x5> ;➋ 0xf8=0x5-0xd=-8
   d:	f3                   	repz
```   

---

## Procedures
- What is the difference between leaf and non-leaf functions?
- List the registers used in System V AMD64 ABI
- How do the instruction `call` and `ret` change the stack?
- If a function starts with `push rbp` followed by `sub rsp, 32`, what will be the value of `RSP` if it was `0x7fffffffdff0` before the function was started?
  - `push rbp` decrements `RSP` by 8 bytes: `0x7fffffffdff0 - 8 = 0x7fffffffdfe8`
  - `sub rsp, 32` reserves 32 bytes for local variables: `0x7fffffffdfe8 - 32 = 0x7fffffffdfc8`
- If a function call pushes a return address onto the stack and then pushes `RBP`, what was the value of `RSP` before the function call if it is `0x7fffffffdff0` after the `PUSH RBP` instruction?
  - `0x7fffffffdff0 + 16 = 0x7fffffffe000`

---
## Data and Beyond
- How to calculate the address of elements in a one dimensional C array?
  - `T A[N]: Addr([A[i]]) = Aval + i*sizeof(T)`
  - ⚠️ Pointer arithmetic: `&A[i] - &A[j] = i-j`, but
    - `(unsigned long)&A[i] - (unsigned long)&A[j] = (i-j)*sizeof(T)`
- How to calculate the address of elements in a two dimensional C array?
  - `T A[R][C]: Addr(A[i][j]) = Aval + (i*C + j)*sizeof(T)`
- Complying with alignment rules on x86-64,
  - How to calculate the size of a structure?
  - How to get a maximum/minimum size of the structure by rearranging its fields?
    - and their paddings?
  - Take the following structure as an example

  ```c
  struct Person{
    char sex;
    short height;
    float weight;
  };
  ```

---
## Building executables

- What are the symbol resolutions?
- What are the differences between dynamic and static links?
- In an ELF relocatable object file, if a function `foo` is defined at offset `0x100` within the `.text` section and the section's start address in memory is `0x400000`, the actual memory address of `foo` is:
  - `0x400100 = 0x400000 + 0x100`