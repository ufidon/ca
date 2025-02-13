# Processor architecture
CS:APP3e.ch04


---

## 🔭 Explore the most advanced processors

- [Laptop Processors Ranking](https://nanoreview.net/en/cpu-list/laptop-chips-rating)
  - [Laptop GPU Ranking](https://nanoreview.net/en/gpu-list/laptop-graphics-rating)
- [Desktop CPU Performance Ranking](https://nanoreview.net/en/cpu-list/desktop-chips-rating)
  - [Desktop GPU Ranking](https://nanoreview.net/en/gpu-list/desktop-graphics-rating)

---

## Overview

- **Microprocessors**: 
  - Powerful chips with multiple cores and large caches, 
  - surpassing past supercomputers and embedded in everyday devices.  
- **ISA**: 
  - Defines machine instructions for processor families (e.g., x86-64, ARM), 
  - ensuring compatibility within but not across families.  
- **Execution**: 
  - Modern processors optimize performance with parallel execution 
  - while maintaining sequential ISA behavior.  

---

## Why do we learn processor insides?

- **Intellectual Value**: 
  - Understanding processor design reveals the inner workings of a crucial system in computing.  
- **Technological Progress**: 
  - Comparing the [1976 Cray-1 supercomputer](https://en.wikipedia.org/wiki/Cray-1) to the 2025 [Ryzen AI Max+ 395 chip](https://nanoreview.net/en/cpu/amd-ryzen-ai-max-395) highlights immense advancements in performance, size, and efficiency.  
- **System Understanding**: 
  - Knowing how processors work improves comprehension of overall computer architecture, including memory systems.  
- **Embedded Systems**: 
  - Many modern devices contain processors, requiring engineers to understand their design for low-level programming.  
- **Career Potential**: 
  - Though few companies design processors, large and growing teams provide opportunities in processor development.  

---

## What we are going to learn?

- **Y86-64 Instruction Set**: 
  - A simplified version of x86-64 with fewer features but easier CPU decoding
- **Digital Hardware Basics**: 
  - Covers processor building blocks, Boolean logic, and HCL for hardware control
- **Sequential Processor**: 
  - A basic Y86-64 processor executing one instruction per cycle,
  - functional but inefficient.  
- **Pipelined Processor**: 
  - Improves performance by breaking execution into five stages,
  - allowing multiple instructions to be processed simultaneously.  
- **Simulation & Experimentation**: 
  - Tools include assemblers, simulators, and exercises for modifying instructions and processor behavior using HCL.  
- **Verilog Implementation**: 
  - Translates HCL designs into Verilog for simulation and synthesis, 
  - enabling real-world processor hardware development.  

---

# The Y86-64 instruction set architecture
- 🛠️ [Y86-64 simulator](https://boginw.github.io/js-y86-64/)

---

## Programmer-visible state
 
- **Registers**: 
  - Y86-64 has 15 general-purpose 64-bit registers, 
  - with `%rsp` serving as the stack pointer for function calls and stack operations.  
- **Condition Codes**: 
  - Three single-bit flags `(ZF, SF, OF)` indicate features of results of the most recent arithmetic or logical operation.  
- **Memory & Addressing**: 
  - Programs use `virtual addresses`, 
  - which are translated by hardware and the OS into physical memory locations.  
- **Program Status (Stat)**: 
  - Indicates execution state, detecting errors like invalid memory access or exceptions.  

| **15 Register** | **Encoding Identifier** | **Purpose** |  
|-------------|----|------------| 
| %rax        | 0 | General-purpose |  
| %rcx        | 1 | General-purpose |  
| %rdx        | 2 | General-purpose |  
| %rbx        | 3 | General-purpose |  
| %rsp        | 4 | Stack pointer (used by push, pop, call, return) |  
| %rbp        | 5 | General-purpose |  
| %rsi        | 6 | General-purpose |  
| %rdi        | 7 | General-purpose |  
| %r8 - %r14  | 8-E | General-purpose |  

| **3 Condition Code** | **Meaning** |  
|-------------------|------------|  
| ZF (Zero Flag)   | Set if the result of an operation is zero |  
| SF (Sign Flag)   | Set if the result is negative |  
| OF (Overflow Flag) | Set if an arithmetic operation causes an overflow |  

| **Program Counter** | **Purpose** |  
|----------|------------|  
| PC| Holds the address of the currently executing instruction |  

---

## [Y86-64 instructions](https://github.com/YuanjieZhao/Y86-Disassembler/blob/release/Y86-64%20Instruction%20Set%20Architecture.pdf)

Y86-64 is a simplified x86-64 subset with only 8-byte integer operations and fewer addressing modes and instructions.

- **Data Transfer Instructions:** 
  - Y86-64 splits `movq` into `irmovq`, `rrmovq`, `mrmovq`, and `rmmovq`, 
  - explicitly defining source and destination types. 
  - Memory references use a base and displacement format.  
- **Integer Operations:** 
  - Includes `addq`, `subq`, `andq`, and `xorq`, 
  - operating only on registers and updating condition codes (`ZF`, `SF`, `OF`).  
- **Jump Instructions: `jXX`** 
  - Seven conditional jumps (`jmp`, `jle`, `jl`, `je`, `jne`, `jge`, `jg`) follow x86-64 branch conditions.  
- **Conditional Moves: `cmovXX`** 
  - Six conditional move instructions (`cmovle`, `cmovl`, `cmove`, `cmovne`, `cmovge`, `cmovg`) update registers based on condition codes.  
- **Function Calls:** 
  - `call` pushes the return address and jumps, while `ret` restores it.  
- **Stack Operations:** 
  - `pushq` and `popq` work the same as in x86-64.  
- **Halt Instruction:** 
  - `halt` stops execution with a status code of `HLT`, similar to x86-64’s `hlt`.

---

## Y86-64 instruction encoding I

| **Instruction** | **Byte 0** | **Byte 1** | **Byte 2-8** | **Byte 9** | **Description** |
|---------------|---------|---------|---------|------------|--------------|
| **halt**     | 0 0     | -       | -       | -          | Stops execution |
| **nop**      | 1 0     | -       | -       | -          | No operation |
| **rrmovq rA, rB** | 2 0 | rA rB  | -       | -          | Register-to-register move |
| **irmovq V, rB** | 3 0 | F rB  | V       |           | Immediate-to-register move |
| **rmmovq rA, D(rB)** | 4 0 | rA rB | D      |           | Register-to-memory move |
| **mrmovq D(rB), rA** | 5 0 | rA rB | D      |           | Memory-to-register move |
| **OPq rA, rB** | 6 fn | rA rB  | -       | -          | Integer operations (`addq`, `subq`, `andq`, `xorq`) |
| **jXX Dest** | 7 fn   | Dest    |        | -          | Conditional jumps (`jmp`, `jle`, `jl`, `je`, `jne`, `jge`, `jg`) |
| **cmovXX rA, rB** | 2 fn | rA rB  | -       | -          | Conditional moves (`cmovle`, `cmovl`, `cmove`, `cmovne`, `cmovge`, `cmovg`) |
| **call Dest** | 8 0    | Dest    |        | -          | Call subroutine |
| **ret**      | 9 0     | -       | -       | -          | Return from subroutine |
| **pushq rA** | A 0    | rA F    | -       | -          | Push register onto stack |
| **popq rA**  | B 0    | rA F    | -       | -          | Pop register from stack |

- **fn**: Specifies a particular integer operation (`OPq`), data movement (`cmovXX`), or branch condition (`jXX`).
- **D**: Displacement value for memory addressing.
- **F**: 0xF, No register field.
- **V**: 8-byte immediate value.
- **Dest**: Destination address for jump and call instructions.

---

## Y86-64 instruction encoding II

- Y86-64 instructions are encoded in 1 to 10 bytes, 
  - depending on the required fields, 
  - with an `initial byte` identifying the instruction type.
- The initial byte is split into a high-order nibble "code" and low-order nibble "function" part, 
  - with codes ranging from 0 to 0xB. 
  - Function values are used for related instructions sharing the same code.

| Operations | Branches | Moves |
|---|---|---|
| `addq` 6 0 | `jmp` 7 0 `jne` 7 4 | `rrmovq` 2 0 `cmovne` 2 4 |
| `subq` 6 1 | `jle` 7 1 `jge` 7 5 | `cmovle` 2 1 `cmovge` 2 5 |
| `andq` 6 2 | `jl`  7 2 `jg`  7 6 | `cmovl`  2 2 `cmovg`  2 6 |
| `xorq` 6 3 | `je`  7 3 | `cmove`  2 3 |

- Each program register has a unique identifier (ID) from 0 to 0xE, 
  - with ID 0xF indicating no register access.
- Instructions may require additional register specifiers (rA, rB) for operands, 
  - depending on the instruction type, 
  - with specific values for single or no register operand instructions.
- Some instructions include an 8-byte constant word for immediate data, displacement, or branch/call destinations, 
  - with absolute addressing used for simplicity instead of PC-relative addressing.
- The byte encoding for each instruction must have a unique interpretation, ensuring unambiguous execution. 
  - Disassemblers may face issues if the starting position of the instruction sequence is unknown.

---

## 💡 Assemble & disassemble
- **Assemble the assembly code**

```python
.pos 0x100        # Start code at address Ox100

irmovq $15, %rbx   # Initialize rbx with value 15
rrmovq %rbx, %rcx   # Copy rbx to rcx

loop:
    rmmovq %rcx, -3(%rbx)  # Store rcx at address rbx - 3
    addq %rbx, %rcx       # Add rbx to rcx
    jmp loop              # Jump back to loop
```
- verify your [solution](https://boginw.github.io/js-y86-64/)

- **Disassemble the machine code**
  - find the first possible invalid nibble if there is a mistake

```python
# PC : machine code
Ox100: 30f3fcffffffffffffff40630008000000000000
Ox200: a06f800c020000000000000030f30a00000000000000
Ox300: 505407000000q000000010f0b01f
Ox400: 611373000400000000000000
Ox500: 6362a0f0
```
- verify your [solution](https://github.com/YuanjieZhao/Y86-Disassembler)

---

## CISC vs. RISC

- **CISC Evolution:** x86-64 grew from increasingly complex instruction sets.  
- **RISC Philosophy:** RISC prioritized simplicity, pipelining, and compiler efficiency.  
- **Hybrid Approach:** Y86-64 blends CISC’s complexity with RISC’s efficiency.  
- **RISC vs. CISC Debate:** RISC optimized execution, while CISC minimized instructions per task.  
- **Market Trends:** RISC dominates embedded systems; x86-64 leads mainstream computing.  
- **Modern Convergence:** Both architectures now integrate each other’s best features.

---

## **CISC vs. Early RISC Comparison**  

| **Feature**           | **CISC** | **Early RISC** |
|----------------------|---------|--------------|
| **Instruction Count** | Large set (1,200+ pages) | Fewer than 100 |
| **Execution Time**   | Some slow instructions (e.g., block copy) | No long-execution instructions |
| **Encoding**         | Variable (1–15 bytes) | Fixed (4 bytes) |
| **Operand Handling** | Complex, multiple addressing formats | Simple base + displacement addressing |
| **Memory Access**    | Arithmetic/logical ops on registers & memory | Load/store architecture (register-only ops) |
| **Abstraction**      | Hides implementation details | Exposes some hardware constraints |
| **Condition Codes**  | Uses flags for branching | Explicit test instructions store results in registers |
| **Procedure Linkage** | Stack-based (arguments & return addresses) | Register-based, reducing memory use |

---


# References
- [Intel® 64 and IA-32 Architectures Software Developer's Manual Combined Volumes](https://www.intel.com/content/www/us/en/content-details/782158/intel-64-and-ia-32-architectures-software-developer-s-manual-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html)
  - [x86-64 Instructions Set](https://linasm.sourceforge.net/docs/instructions/index.php)
  - [x86 and amd64 instruction reference](https://www.felixcloutier.com/x86/)