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
    - based on `S₁ - S₂`
  - sets flags (`ZF`, `SF`, `CF`, `OF`) for `equality or ordering`.
    - `ZF` ← 1 if `S₁ - S₂=0`; else 0. 
    - `SF` ← 1 if `S₁ - S₂<0`; else 0.
    - `CF` ← 1 if unsigned overflow; else 0.
    - `OF` ← 1 if signed overflow; else 0.
      - (S₂ >0 && S₁ < 0 && S₁ - S₂ <0) || (S₂ < 0 && S₁ > 0 && S₁ - S₂>0)
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
  - **SETcc instruction** `set` a single byte to 0 or 1 without altering remaining 7 bytes
  - **Conditional jumps** `jump` to different parts of the program
  - **Conditional data transfers** `transfer` data 
- The [SETcc](https://www.felixcloutier.com/x86/setcc) instructions

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

## 📝 Determine the C code

- 1️⃣ Determine the `data_t` and the `COMP` for each block of assembly codes

```c
// `data_t` is one of C integer types including pointers
int comp(data_t a, data_t b){
  // a in some portion of rdi, b in rsi
  // `COMP` is one of C relational operators (==, !=, <, >, <=, >=)
  return a COMP b;
}
```

generates the assembly codes below:


| **#** | **Intel Syntax**    | **AT&T Syntax**   |
|-------|---------------------------|----------------------------|
| ➊     | `cmp edi, esi`<br>`setl al` | `cmpl %esi, %edi`<br>`setl %al` |
| ➋     | `cmp di, si`<br>`setge al`  | `cmpw %si, %di`<br>`setge %al`  |
| ➌     | `cmp dil, sil`<br>`setbe al` | `cmpb %sil, %dil`<br>`setbe %al` |
| ➍     | `cmp rdi, rsi`<br>`setne al`| `cmpq %rsi, %rdi`<br>`setne %al`|


- 2️⃣ Determine the `data_t` and the `TEST` for each block of assembly codes

```c
// `data_t` is one of C integer types including pointers
int test(data_t a){
  // a in some portion of rdi
  // `TEST` is one of C relational operators (==, !=, <, >, <=, >=) 
  return a TEST 0; 
}
```

generates the assembly codes below:

| **#** | **Intel Syntax**  | **AT&T Syntax**  |
|-------|------------------|----------------|
| ➊ | `test rdi, rdi`<br>`setge al` | `testq %rdi, %rdi`<br>`setge %al` |
| ➋ | `test di, di`<br>`sete al`    | `testw %di, %di`<br>`sete %al`    |
| ➌ | `test dil, dil`<br>`seta al`  | `testb %dil, %dil`<br>`seta %al`  |
| ➍ | `test edi, edi`<br>`setle al` | `testl %edi, %edi`<br>`setle %al` |

---

## Jump Instructions
- redirect execution to a new position usually marked by a `label` in assembly code.
  - `jump target` is the address of the destination instruction in memory
  - two types: [unconditional jumps](https://www.felixcloutier.com/x86/jmp) and [conditional jumps](https://www.felixcloutier.com/x86/jcc)

- 🍎 The assembler calculates `labeled instruction addresses` 
  - encodes `jump targets` as part of the jump instructions.


| **Intel Syntax** | **AT&T Syntax**     | **Description**     |
|------------------|---------------------|---------------------|
| `mov rax, 0`     | `movq $0, %rax`     | Set `%rax` to 0.    |
| `jmp .L1`        | `jmp .L1`           | Jump to label `.L1`.|
| `mov rsi, [rax]` | `movq (%rax), %rsi` | Dereference `%rax` and move to `%rsi`. <br>(Potential null pointer dereference, skipped.) |
| `.L1:`           | `.L1:`              | Define label `.L1`.   |
| `pop rdx`        | `popq %rdx`         | Pop a value from the stack into `%rdx`. |


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

- Indirect jumps: `jmp *Operand`
  - Conditional jumps can only be `direct`

| **Intel Syntax**| **AT&T Syntax**   | **Description**  |
|-------------|----------------|---------------------|
| `jmp rax`   | `jmp *%rax`   | Uses the value in register `rax` as the jump target.   |
| `jmp [rax]` | `jmp *(%rax)` | Reads the jump target from memory with address in `rax`. |

---

## Jump instruction encodings

- **PC-relative jumps**: Encode the `offset` between the `target` and `the instruction following the jump`, using 1, 2, or 4 bytes.  
- **Absolute jumps**: Directly specify the target address with a 4-byte encoding.  
- **Encoding selection**: The assembler and linker determine the appropriate jump encoding based on the target.  

- 🍎 PC-relative [jumps](./code/ctrl/jmp.s)
  - `offset = target - the instruction following the jump`

| **Intel Syntax** | **AT&T Syntax** | **Description**   |
|------------------|-----------------|-------------------|
| `mov rax, rdi`   | `movq %rdi, %rax` | Move the value in `%rdi` to `%rax`.   |
| `jmp .L2`        | `jmp .12`         | Unconditionally jump to label `.L2`.  |
| `.L3:`           | `.13:`            | Define label `.L3`.                   |
| `sar rax`        | `sarq %rax`       | Perform an arithmetic right shift on `%rax`.   |
| `.L2:`           | `.12:`            | Define label `.L2`.                            |
| `test rax, rax`  | `testq %rax, %rax`| Perform a bitwise AND of `%rax` with itself (sets flags).   |
| `jg .L3`         | `jg .13`          | Jump to label `.L3` if greater than (based on flags).        |
| `rep ret`        | `rep; ret`        | Return from the function, with `rep` prefix for compatibility. |

generates object codes, analyze the jump encoding ➊ and ➋ 

```asm
0000000000000000 <_start>:
   0:	48 89 f8             	mov    %rdi,%rax
   3:	eb 03                	jmp    8 <_start+0x8> ;➊ 0x03=0x8-0x5
   5:	48 d1 f8             	sar    %rax
   8:	48 85 c0             	test   %rax,%rax
   b:	7f f8                	jg     5 <_start+0x5> ;➋ 0xf8=0x5-0xd=-8
   d:	f3                   	repz
```

- The instructions can be compactly encoded in just 2 bytes, 
  - allowing the object code to be relocated in memory without any modification. 

```asm
0000000000401000 <_start>:
  401000:	48 89 f8             	mov    %rdi,%rax
  401003:	eb 03                	jmp    401008 <_start+0x8> ;➊
  401005:	48 d1 f8             	sar    %rax
  401008:	48 85 c0             	test   %rax,%rax
  40100b:	7f f8                	jg     401005 <_start+0x5> ;➋
  40100d:	f3                   	repz
```

- 📝 Determine the target addresses

| **Question** | **Machine Code**  | **Intel Syntax**    | **AT&T Syntax**    | **Target Address**  |
|---------|----------------------------------|-------------------------------------------|-------------------------------|---------------------|
| **A.**  | 4003fa: 74 02 <br> 4003fc: ff d0 | `je XXXXXX` <br> `call qword ptr [rax]`   | `je XXXXXX` <br> `call *%rax` | Target of `je` is `XXXXXX` |
| **B.**  | 40042f: 74 f4 <br> 400431: 5d    | `je XXXXXX` <br> `pop rbp`       | `je XXXXXX` <br> `pop %rbp`    | Target of `je` is `XXXXXX` |
| **C.**  | XXXXXX: 77 02 <br> XXXXXX: 5d    | `ja 0x400547` <br> `pop rbp`     | `ja 0x400547` <br> `pop %rbp`  | Address of `ja` and `pop` instructions is `XXXXXX` |
| **D.**  | 4005e8: e9 73 ff ff ff <br> 4005ed: 90| `jmp 0xFFFFFF73` <br> `nop` | `jmp 0xFFFFFF73` <br> `nop`    | Address of jump target is calculated from 4-byte PC-relative offset `0xFFFFFF73` |



- 📝 Analyze the encoding of [jump instructions](./code/ctrl/jumps.c)

---

## Two ways implementing C conditional structures
- **Old way**: `goto`
  - ![c branch to asm](./imgs/ctrl/c2ab.png)

- 📝 Rewrite [`if⋯else` with `goto`](./code/ctrl/dist.c)
- 📝 Disassemble [goat.s](./code/ctrl/goat.s) into C

- **New way**: `conditional transfer of data`
  - Computes `both outcomes` of a conditional operation.
    - `Selects` the outcome based on the condition's truth value.
  - Effective in `limited` cases but optimized for `modern` processors.

- 📝 Inspect the [conditional move](./code/ctrl/cmov.c)
  - in [assembly](./code/ctrl/atdist.s)

---

## The [CMOVcc](https://www.felixcloutier.com/x86/cmovcc) instructions
- if cc = true: R ← S

| **Intel Syntax** | **AT&T Syntax**  | **Synonym** | **Move Condition** | **Description**       |
|--------------|---------------|-----------|---------------------|-------------------------------|
| `cmove R, S` | `cmove S, R`  | `cmovz`   | `ZF`               | Equal / Zero                   |
| `cmovne R, S`| `cmovne S, R` | `cmovnz`  | `~ZF`              | Not equal / Not zero           |
| `cmovs R, S` | `cmovs S, R`  | -         | `SF`               | Negative                       |
| `cmovns R, S`| `cmovns S, R` | -         | `~SF`              | Non-negative                   |
| `cmovg R, S` | `cmovg S, R`  | `cmovnle` | `~(SF ^ OF) & ~ZF` | Greater (signed `>`)           |
| `cmovge R, S`| `cmovge S, R` | `cmovnl`  | `~(SF ^ OF)`       | Greater or equal (signed `>=`) |
| `cmovl R, S` | `cmovl S, R`  | `cmovnge` | `(SF ^ OF)`        | Less (signed `<`)              |
| `cmovle R, S`| `cmovle S, R` | `cmovng`  | `(SF ^ OF) \| ZF`  | Less or equal (signed `<=`)    |
| `cmova R, S` | `cmova S, R`  | `cmovnbe` | `~CF & ~ZF`        | Above (unsigned `>`)           |
| `cmovae R, S`| `cmovae S, R` | `cmovnb`  | `~CF`              | Above or equal (unsigned `>=`) |
| `cmovb R, S` | `cmovb S, R`  | `cmovnae` | `CF`               | Below (unsigned `<`)           |
| `cmovbe R, S`| `cmovbe S, R` | `cmovna`  | `CF \| ZF`         | Below or equal (unsigned `<=`) |

![movcc equivalent](./imgs/ctrl/movcc.png)

---

## MOVcc limitations
- Evaluating both true/false expressions causes errors or side effects
  - e.g., null pointer dereferencing: `p? *p : 0`   
- Waste computation if one expression is complex and the condition fails.  
- Compilers favor conditional moves for `simple` cases but avoid them for complex or unpredictable scenarios.

- 📝 Disassemble [exatbrch.s](./code/ctrl/exatbrch.s)

---

## Implement C loops

- `do while`

![do while](./imgs/ctrl/dowhile.png)

- 📝 Convert [`do while` to `goto`](./code/ctrl/dowhile.c)
  - Disassemble [dowhile.s](./code/ctrl/dowhile.s)

- `while`

![while](./imgs/ctrl/while.png)

- 📝 Convert [`while` to `goto`](./code/ctrl/while.c)
  - Disassemble [while.s](./code/ctrl/while.s)

- `for`

![for](./imgs/ctrl/for.png)

- 📝 Convert [`for` to `goto`](./code/ctrl/for.c)
  - Disassemble [for.s](./code/ctrl/for.s)

---

## Switch statement
- A switch statement enables `multiway branching` based on an integer index, 
  - improving readability and efficiency.
- It uses a `jump table` to map indices to corresponding code segments.
- Jump tables provide `faster` performance than if-else statements, 
  - especially for cases with a small range of values.

- 📝 Convert [`switch` to `goto`](./code/ctrl/switch.c)
  - Disassemble [switch.s](./code/ctrl/switch.s) and [inswitch.s](./code/ctrl/inswitch.s)
- ☠️ GNU c extension: [pointer to label](./code/ctrl/dlabel.c)

---