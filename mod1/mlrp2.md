# Machine-Level Representation of Programs
CS:APP3e.ch03

Control Structures
---
- C constructs (e.g., conditionals, loops) use `conditional execution` based on `data tests`.  
- Machine code implements this via `data tests and jump instructions` to alter control flow.  
- Compilers translate C control constructs into low-level machine code mechanisms.

---

## X86-64 CPU Flags (Condition Codes)
| **Flag** | **Name**               | **Indication**                                                                 |
|----------|------------------------|---------------------------------------------------------------------------------|
| **CF**   | `Carry` Flag           | Set if the last operation resulted in a `carry-out or borrow (unsigned overflow)`.|
| **ZF**   | `Zero` Flag            | Set if the result of the last operation was `zero`.                               |
| **SF**   | `Sign` Flag            | Set if the result of the last operation is `negative (MSB is 1)`.                 |
| **OF**   | `Overflow` Flag        | Set if the last operation caused `signed overflow (two's-complement overflow)`.   |
| **PF**   | `Parity` Flag          | Set if the number of set bits in the result is `even`.                            |
| **AF**   | `Auxiliary Carry` Flag | Set if there was a `carry-out or borrow in the lower nibble (BCD operations)`.    |
| **DF**   | `Direction` Flag       | Controls the `direction of string operations` (increment/decrement).             |
| **IF**   | `Interrupt` Flag       | Enables or disables hardware `interrupts`.                                        |
| **TF**   | `Trap` Flag            | Enables single-step `debugging`.                                                  |

- **CF**, **ZF**, **SF**, and **OF** 
  - most commonly used flags for `arithmetic and logical operations`.
- **PF**, **AF**, **DF**, **IF**, and **TF** 
  - used for specific purposes like `BCD arithmetic, string operations, and system-level control`.

- 🍎 [ADD D, S ↔ t = a + b](https://hjlebbink.github.io/x86doc/html/ADD.html)

| **Flag** | **Condition** | **Indication**  |
|-----|---------------|------------------|
| CF  | `(unsigned) t < (unsigned) a`         | Unsigned overflow |
| ZF  | `(t == 0)`                            | Zero result       |
| SF  | `(t < 0)`                             | Negative result   |
| OF  | `(a < 0 == b < 0) && (t < 0 != a < 0)`| Signed overflow   |

- Most instructions set CPU flags
  - [lea](https://www.felixcloutier.com/x86/lea) does NOT

---

## Comparison and Test Instructions
- Set the condition codes without altering any other registers

| **Intel Syntax** | **AT&T Syntax** | **Function** |
|------------------|-----------------|--------------------------|
| `CMP S1, S2`     | `cmpb S2, S1`   | Compare byte             |
| `CMP S1, S2`     | `cmpw S2, S1`   | Compare word             |
| `CMP S1, S2`     | `cmpl S2, S1`   | Compare double word      |
| `CMP S1, S2`     | `cmpq S2, S1`   | Compare quad word        |
| `TEST S1, S2`    | `testb S2, S1`  | Test byte                |
| `TEST S1, S2`    | `testw S2, S1`  | Test word                |
| `TEST S1, S2`    | `testl S2, S1`  | Test double word         |
| `TEST S1, S2`    | `testq S2, S1`  | Test quad word           |

- [CMP](https://www.felixcloutier.com/x86/cmp): 
  - `Compares` two operands without updating the destination;
    - based on `S₂ - S₁`
  - sets flags (`ZF`, `SF`, `CF`, `OF`) for `equality or ordering`.
    - `ZF` ← 1 if `S₂ - S₁=0`; else 0. 
    - `SF` ← 1 if `S₂ - S₁<0`; else 0.
    - `CF` ← 1 if unsigned overflow; else 0.
    - `OF` ← 1 if signed overflow; else 0.
      - (S₂ >0 && S₁ < 0 && S₂ - S₁ <0) || (S₂ < 0 && S₁ > 0 && S₂ - S₁>0)
- [TEST](https://www.felixcloutier.com/x86/test): 
  - Performs `bitwise AND` without updating the destination;
    - based on `S₂ & S₁`
  - sets flags (`ZF`, `SF`) to test for `zero, negative, or specific bits`.
    - `ZF` ← 1 if `S₂ & S₁=0`; else 0. 
    - `SF` ← 1 if `S₂ & S₁<0`; else 0.
    - `CF` ← 0.  `OF` ← 0.
- Machine code often uses the same instructions for signed and unsigned values due to similar bit-level behavior.  
- Some operations require different instructions for signed vs. unsigned handling.
  - e.g., right shifts, division, multiplication, and condition codes
- 📝 Explore [CMP and TEST](./code/ctrl/cmtst.c)

---

## Accessing Condition Codes
- Many instructions act based on the condition codes
  - **SET instruction** `set` a single byte to 0 or 1 without altering remaining 7 bytes
  - **Conditional jumps** `jump` to different parts of the program
  - **Conditional data transfers** `transfer` data 
- The [SET](https://www.felixcloutier.com/x86/setcc) instructions

| **Instruction** | **Synonym** | **Effect**      | **Set condition**            |
|------------|-----------|------------------------|------------------------------|
| `sete D`   | `setz D`  | `D ← ZF`               | Equal (zero)                 |
| `setne D`  | `setnz D` | `D ← ~ZF`              | Not equal (not zero)         |
| `sets D`   |           | `D ← SF`               | Negative                     |
| `setns D`  |           | `D ← ~SF`              | Nonnegative                  |
| `setg D`   | `setnle D`| `D ← ~(SF ^ OF) & ~ZF` | Greater (signed >)           |
| `setge D`  | `setnl D` | `D ← ~(SF ^ OF)`       | Greater or equal (signed >=) |
| `setl D`   | `setnge D`| `D ← SF ^ OF`          | Less (signed <)              |
| `setle D`  | `setng D` | `D ← (SF ^ OF) \| ZF`  | Less or equal (signed <=)    |
| `seta D`   | `setnbe D`| `D ← ~CF & ~ZF`        | Above (unsigned >)           |
| `setae D`  | `setnb D` | `D ← ~CF`              | Above or equal (unsigned >=) |
| `setb D`   | `setnae D`| `D ← CF`               | Below (unsigned <)           |
| `setbe D`  | `setna D` | `D ← CF \| ZF`         | Below or equal (unsigned <=) |

- 📝 Explore [cmp and set instruction](./code/ctrl/comp.c)
  - in assembly [comas.s](./code/ctrl/comas.s) or [comnas.s](./code/ctrl/comnas.s)

---

## Jump Instructions
- redirect execution to a new position usually marked by a `label` in assembly code.
  - `jump target` is the address of the destination instruction in memory
  - two types: [unconditional jumps](https://www.felixcloutier.com/x86/jmp) and [conditional jumps](https://www.felixcloutier.com/x86/jcc)

| **Instruction** | **Synonym** | **Jump Condition**    | **Description**       |
|---------------|-------|-------------------|------------------------------------------|
| `jmp Label`   |       |  1     | `Direct unconditional` jump to a label            |
| `jmp *Operand`|       |  1     | `Indirect unconditional` jump to an `address` in memory or register |
| `je Label`    | `jz`  | `ZF`              | equal (zero)                |
| `jne Label`   | `jnz` | `~ZF`             | not equal (not zero)        |
| `js Label`    |       | `SF`              | negative                    |
| `jns Label`   |       | `~SF`             | nonnegative                 |
| `jg Label`    | `jnle`| `~(SF ^ OF) & ~ZF`| greater (signed >)          |
| `jge Label`   | `jnl` | `~(SF ^ OF)`      | greater or equal (signed >=)|
| `jl Label`    | `jnge`| `SF ^ OF`         | less (signed <)             |
| `jle Label`   | `jng` | `(SF ^ OF) \| ZF` | less or equal (signed <=)   |
| `ja Label`    | `jnbe`| `~CF & ~ZF`       | above (unsigned >)          |
| `jae Label`   | `jnb` | `~CF`             | above or equal (unsigned >=)|
| `jb Label`    | `jnae`| `CF`              | below (unsigned <)          |
| `jbe Label`   | `jna` | `CF \| ZF`        | below or equal (unsigned <=)|

- 📝 Analyze the encoding of [jump instructions](./code/ctrl/jumps.c)

---

## Express C Conditional Branch with `goto`

![c branch to asm](./imgs/ctrl/c2ab.png)

---