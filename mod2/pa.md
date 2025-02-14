# Processor architecture
CS:APP3e.ch04


# The Y86-64 Instruction Set Architecture

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
- 🛠️ [Build local Y86-64 simulator](https://github.com/gyunseo/sim)
  ```bash
  # 1. install build tools
  sudo apt update
  sudo apt upgrade -y
  sudo apt install build-essential gdb flex bison tcl tk tcl-dev tk-dev git

  # 2. download and build Y86-64 simulator source code
  git clone https://github.com/gyunseo/sim.git
  cd sim
  chmod +x ./pipe/gen-driver.pl
  make

  # 3. use ssim
  cd seq/
  ./ssim -g ../y86-code/prog8.yo

  # use psim
  cd pipe
  ./psim -g ../y86-code/prog8.yo
  ```
- 🛠️ [Y86-64 simulator online](https://boginw.github.io/js-y86-64/)

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
  - `pushq %rsp` saves the old stack pointer 
    - while updating `%rsp` to reflect the new stack position.
- **Halt Instruction:** 
  - `halt` stops execution with a status code of `HLT`, similar to x86-64's `hlt`.

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
- Some instructions include an `8-byte constant word` for immediate data, displacement, or branch/call destinations, 
  - with absolute addressing used for simplicity instead of PC-relative addressing.
- The byte encoding for each instruction must have a unique interpretation, ensuring unambiguous execution. 
  - Disassemblers may face issues if the starting position of the instruction sequence is unknown.

---

## Instruction Encoding: Y86-64 vs. x86-64

| Feature               | x86-64                            | Y86-64                        |
|-----------------------|----------------------------------|--------------------------------|
| **Encoding Complexity** | More complex                    | Simpler                        |
| **Compactness**       | More compact                     | Less compact                   |
| **Register Fields**   | Packed into various positions   | Fixed positions in all instructions |
| **Constant Value Encoding** | 1, 2, 4, or 8 bytes         | Always requires 8 bytes |


- 🔭 Explore [X86-64 Instruction Encoding](https://wiki.osdev.org/X86-64_Instruction_Encoding)

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
- **Hybrid Approach:** Y86-64 blends CISC's complexity with RISC's efficiency.  
- **RISC vs. CISC Debate:** RISC optimized execution, while CISC minimized instructions per task.  
- **Market Trends:** RISC dominates embedded systems; x86-64 leads mainstream computing.  
- **Modern Convergence:** Both architectures now integrate each other's best features.

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

## Y86-64 Exceptions

- **Program Status Codes**: 
  - Y86-64 tracks execution state using a `Stat` code with `four` possible values.  
- **Processor Response**: 
  - The processor halts on any exception, 
  - though a full design could include exception handlers.

| Value | Name | Meaning |
|-------|------|------------------------------------|
| 1     | AOK  | `Normal` operation                 |
| 2     | HLT  | Halt instruction encountered     |
| 3     | ADR  | Invalid address encountered      |
| 4     | INS  | Invalid instruction encountered  |

---

## Function implementation in Y86-64 Instructions

- 🍎 Compute the sum of an array of integers

```c
long sum(long *start, long count) {
    long sum = 0;
    while (count) {
        sum += *start;
        start++;
        count--;
    }
    return sum;
}
```
- 📝 implement in x86-64 instructions
  ```bash
  gcc -c -fno-stack-protector -fcf-protection=none -o sum.o sum.c
  objdump -d sum.o
  ```

  ```python
  # long sum(long *start, long count)
  # start in %rdi, count in %rsi
  sum:
      movq    $0, %rax       # sum = 0
      jmp     test           # Goto test

  loop:
      addq    (%rdi), %rax   # Add *start to sum
      addq    $8, %rdi       # start++
      subq    $1, %rsi       # count--

  test:
      testq   %rsi, %rsi     # Test sum
      jne     loop           # If != 0, goto loop

      ret                    # Return
  ```

- 📝 implement in Y86-64 instructions
  ```python
  # long sum(long *start, long count)
  # start in %rdi, count in %rsi
  sum:
      irmovq  $8, %r8        # Constant 8
      irmovq  $1, %r9        # Constant 1
      xorq    %rax, %rax     # sum = 0
      andq    %rsi, %rsi     # Set CC
      jmp     test           # Goto test

  loop:
      mrmovq  (%rdi), %r10   # Get *start
      addq    %r10, %rax     # Add to sum
      addq    %r8, %rdi      # start++
      subq    %r9, %rsi      # count--, Set CC

  test:
      jne     loop           # Stop when 0

      ret                    # Return
  ```

- **x86-64 vs. Y86-64 Differences:**  
  - Y86-64 requires explicit constant loading into registers since it lacks immediate operands in arithmetic instructions.  
  - Y86-64 needs separate instructions for memory loading and arithmetic, whereas x86-64 can combine these operations.  
  - Y86-64 eliminates a redundant `testq` instruction by relying on the condition codes set by `subq`.

---

## Y86-64 Programs

- 🍎 Function sum [demo](https://boginw.github.io/js-y86-64/)
  - 📝 assemble the code

- **Program Structure in Y86-64:**  
  - Uses assembler directives (`.pos`, `.align`) to set `memory layout` and `stack initialization`.  
  - Defines a `four-element array`, aligns it on an 8-byte boundary, and calls `sum` from `main`.  
  - Stack starts at `0x200` and grows downward 
    - We must avoid growing the stack so large that it overwrites program code or data.
- **Assembly and Execution:**  
  - The Y86-64 assembler (`YAS`) translates source code into object code, 
    - showing addresses and instruction bytes.  
  - The Y86-64 simulator (`YIS`) executes machine code, 
    - tracking register and memory changes.  
  - Final output confirms `%rax` holds the correct sum, 
    - and stack operations occurred safely without corrupting executable code.

---

# Logic Design and the [Hardware Control Language HCL](./y86sim/hcl.pdf)

- Digital systems use **combinational logic**, **memory elements**, and **clock signals** for operation.  
- Hardware design now uses **HDLs** like Verilog and VHDL, replacing schematic diagrams.  
- **Logic synthesis tools** generate efficient circuits from HDL descriptions, similar to compilers.  
- **HCL** is used to describe control logic, which can be translated into Verilog.  
- Separating **control logic design and testing** simplifies microprocessor development and synthesis.

---

## Combinational Circuits in HCL

- **Logic gates** (AND, OR, NOT) compute Boolean functions on `bit-level` inputs, with HCL using `&&`, `||`, and `!` for `AND, OR, and NOT`, respectively.  
- **Logic gates** can have multiple inputs (n-way), and their outputs change `immediately` when inputs are updated.
- **Combinational circuits** connect logic gates with strict rules: 
  - inputs come from system inputs, memory, or other gates, 
  - no shared outputs, 
  - and no loops in the network.
- **HCL expressions** define outputs as functions of inputs, 
  - using C-like syntax without computation.
- 🍎**Equality and multiplexer**  
  1. EQ: `eq = (a && b) || (!a && !b)`  
  2. MUX: `out = (s && a) || (!s && b)`

---

## Word-level Combinational Circuits in HCL

- **Word-level combinational circuits** operate on bit groups like 64-bit integers for processor tasks.
- **Equality check** compares two words bit by bit: `bool Eq = (A == B)` in HCL.
- **Multiplexors** select input words based on control signals, expressed using HCL case expressions.
  ```python
  # 2-way multiplexor
  word Out = [
    s : A; # s=1 chooses A else B
    1 : B; # default case
  ]
  ```
  - **4-way multiplexor** selects from four inputs using two control signals in HCL.
  ```python
  word Out = [
    !s1 && !s0 : A; #00
    !s1        : B; #01
    !s0        : C; #10
    1          : D; #11, default case
  ]
  ```
  - **General multiplexer**
  ```python
  [
    select1 : expr1;
    select2 : expr2;
    ⋯
    selectn : exprn;
  ]
  ```
- **Min3**
  ```python
  word Min3 = [
    A <= B && A <= C: A;
    B <= A && B <= C: B;
    1               : C;
  ]
  ```
- **ALU** performs `arithmetic/logical` operations on word-level data, controlled by input signals.
  ```python
  word result = [
    f==0: X+Y;
    f==1: X-Y;
    f==2: X⋅Y;
    f==3: X÷Y;
  ]
  ```
---

## Set membership

- Processor designs often involve comparing a signal against several possible matches, such as testing instruction codes.
- Example: A 2-bit signal `code` selects high- and low-order bits for a 4-way multiplexor.
- Signals `s1` and `s0` are generated using equality tests based on `code` values:
  - `s1` is 1 when `code` is 2 or 3.
  - `s0` is 1 when `code` is 1 or 3.
- A more concise expression for the conditions:
  - `s1` is 1 when `code` is in {2, 3}.
  - `s0` is 1 when `code` is in {1, 3}.
- General set membership test format:
  - `iexpr in {iexpr1, iexpr2, ..., iexprk}` where `iexpr` and the values in the set are integer expressions.

---

## Memory and clocking

- **Combinational Circuits**: React to inputs, generate outputs based on functions of inputs, no state storage.
- **Sequential Circuits**: Require storage devices that hold bits and use a clock to control when values are loaded.
- **Memory Devices**:
  - **Clocked Registers**: 
    - Store individual bits or words, controlled by a clock to load values.
    - Output remains fixed until clock rises, new input values are captured on rising edge.
  - **Random Access Memories (RAM)**: Store multiple words, use an address to select which word to read/write.
    - Example: virtual memory system in processors or register files in Y86-64.
- **Register File**: 
  - Multi-ported RAM with read and write ports, allowing simultaneous operations.
  - Has address inputs for register selection and data inputs/outputs.
  - Writing is clock-controlled; 
    - read/write conflicts result in immediate data transition.
- **Random Access Memory**:
  - Memory with address input, data input/output, and error signal.
  - Read: Address input provides data from the corresponding memory location.
  - Write: Address input, data input, and clock control memory update.
  - Error signal indicates invalid address.
- **Read-Only Memory**: 
  - Used for reading instructions, 
  - often integrated with regular memory in real systems.

---

# Sequential Y86-64 Implementations — SEQ Processor

- A simple processor where each clock cycle processes a complete instruction, 
  - but cycle time is long, limiting the clock rate.
- SEQ serves as a starting point for designing an efficient pipelined processor.

**Instruction Processing Stages**:
1. **Fetch**: 
   - Read instruction from memory using the program counter (PC).
   - Extract `icode` (instruction code) and `ifun` (instruction function).
   - Optionally fetch register specifiers (rA, rB) and an 8-byte constant.
   - Compute `valP`, the address of the next instruction.
2. **Decode**:
   - Read operands from the register file (`valA` and/or `valB`).
   - Typically read registers `rA` and `rB`, or `%rsp` for some instructions.
3. **Execute**:
   - ALU performs the operation specified by `ifun`.
   - Calculate effective address for memory access or modify stack pointer.
   - Set condition codes and evaluate conditions for conditional moves or jumps.
4. **Memory**:
   - Read or write data to memory.
   - Read value is referred to as `valM`.
5. **Write Back**:
   - Write results to the register file.
6. **PC Update**:
   - Set the PC to the address of the next instruction.

- **Processor Loop**: 
  - The processor repeatedly performs these stages until an `exception` occurs
    - e.g., halt, invalid instruction, or memory access error.
  - In a more complete design, the processor enters an `exception-handling mode`.

---

## SEQ Processor outsides

- **Instruction Processing**: 
  - Requires multiple operations, including address computation, stack pointer updates, and next instruction determination.
- **Hardware Efficiency**: 
  - Minimize complexity by sharing components like the ALU across different instructions.
- **Instruction Processing Framework**: 
  - The general flow for all instructions follows a consistent sequence with minor variations for specific operations.

---

## 

---
---

# General Principles of Pipelining

---

# Pipelined Y86-64 Implementations

---


# References
- [Intel® 64 and IA-32 Architectures Software Developer's Manual Combined Volumes](https://www.intel.com/content/www/us/en/content-details/782158/intel-64-and-ia-32-architectures-software-developer-s-manual-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html)
  - [x86-64 Instructions Set](https://linasm.sourceforge.net/docs/instructions/index.php)
  - [x86 and amd64 instruction reference](https://www.felixcloutier.com/x86/)
- [Y86-64 simulator](https://github.com/gyunseo/sim)