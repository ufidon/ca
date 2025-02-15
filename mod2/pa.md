# Processor architecture
CS:APP3e.ch04


# The Y86-64 Instruction Set Architecture (ISA) and SEQ Implementation

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
- SEQ (sequential processor) serves as a starting point for designing an efficient pipelined processor.

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

## SEQ Processor processing flow

- **Instruction Processing**: 
  - Requires multiple operations, including address computation, stack pointer updates, and next instruction determination.
- **Hardware Efficiency**: 
  - Minimize complexity by sharing components like the ALU across different instructions.
- **Instruction Processing Framework**: 
  - The general flow for all instructions follows a consistent sequence with minor variations for specific operations.
  - `Conceptually sequential` but can be parallelized in hardware implementation.
- 📝 Execute each instruction in [basic.ys](./code/pa/basic.ys) through the six stages in GUI `ssim`
  - integer and logic operation, rr/ir movement

| Stage      | OPq rA, rB           | rrmovq rA, rB        | irmovq V, rB         |
|------------|----------------------|----------------------|----------------------|
| **Fetch**  | icode:ifun ← M₁[PC]  | icode:ifun ← M₁[PC]  | icode:ifun ← M₁[PC]  |
|            | rA:rB ← M₁[PC + 1]   | rA:rB ← M₁[PC + 1]   | rA:rB ← M₁[PC + 1]   |
|            |                      |                      | valC ← M₈[PC+8]
|            | valP ← PC + 2        | valP ← PC + 2        | valP ← PC + 10       |
| **Decode** | valA ← R[rA]         | valA ← R[rA]         |                      |
|            | valB ← R[rB]         |                      |                      |
| **Execute**| valE ← valB OP valA  | valE ← 0 + valA      | valE ← 0 + valC      |
|            | Set CC               |                      |                      |
| **Memory** |                      |                      |                      |
| **Write Back** | R[rB] ← valE     | R[rB] ← valE         | R[rB] ← valE         |
| **PC Update** | PC ← valP         | PC ← valP            | PC ← valP            |

- `OPq`: integer and logic operation: `addq, subq, andq, xorq`
- `M₁[x]/M₈[x]` → Reads/Writes `1 byte/8 bytes` at memory location `x`. 

- Memory read/write

| **Stage**      | **rmmovq rA, D(rB)**   | **mrmovq D(rB), rA**  |
|----------------|------------------------|-----------------------|
| **Fetch**      | `icode:ifun ← M₁[PC]`  | `icode:ifun ← M₁[PC]` |
|                | `rA:rB ← M₁[PC + 1]`   | `rA:rB ← M₁[PC + 1]`  |
|                | `valC ← M₈[PC + 2]`    | `valC ← M₈[PC + 2]`   |
|                | `valP ← PC + 10`       | `valP ← PC + 10`      |
| **Decode**     | `valA ← R[rA]`         |                       |
|                | `valB ← R[rB]`         | `valB ← R[rB]`        |
| **Execute**    | `valE ← valB + valC`   | `valE ← valB + valC`  |
| **Memory**     | `M₈[valE] ← valA`      | `valM ← M₈[valE]`     |
| **Write Back** |                        | `R[rA] ← valM`        |
| **PC Update**  | `PC ← valP`            | `PC ← valP`           |

- `pushq/popq` 
  - according to the Y86-64 (and x86-64) convention
    - `pushq` should `decrement` the stack pointer `before writing`
    - `popq` should `read` memory `before increment` the stack pointer

| **Stage**      | **pushq rA**           | **popq rA**            |
|----------------|------------------------|------------------------|
| **Fetch**      | `icode:ifun ← M₁[PC]`  | `icode:ifun ← M₁[PC]`  |
|                | `rA:rB ← M₁[PC + 1]`   | `rA:rB ← M₁[PC + 1]`   |
|                | `valP ← PC + 2`        | `valP ← PC + 2`        |
| **Decode**     | `valA ← R[rA]`         | `valA ← R[%rsp]`       |
|                | `valB ← R[%rsp]`       | `valB ← R[%rsp]`       |
| **Execute**    | `valE ← valB + (-8)`   | `valE ← valB + 8`      |
| **Memory**     | `M₈[valE] ← valA`      | `valM ← M₈[valA]`      |
| **Write Back** | `R[%rsp] ← valE`       | `R[%rsp] ← valE` <br> `R[rA] ← valM` |
| **PC Update**  | `PC ← valP`            | `PC ← valP`            |

- `jumps, call and ret`

| **Stage**     | **jXX Dest**             | **call Dest**          | **ret**               |
|---------------|--------------------------|------------------------|-----------------------|
| **Fetch**     | `icode:ifun ← M₁[PC]`    | `icode:ifun ← M₁[PC]`  | `icode:ifun ← M₁[PC]` |
|               | `valC ← M₈[PC + 1]`      | `valC ← M₈[PC + 1]`    |                       |
|               | `valP ← PC + 9`          | `valP ← PC + 9`        | `valP ← PC + 1`       |
| **Decode**    |                          |                        | `valA ← R[%rsp]`      |
|               |                          | `valB ← R[%rsp]`       | `valB ← R[%rsp]`      |
| **Execute**   | `Cnd ← Cond(CC, ifun)`   | `valE ← valB + (-8)`   | `valE ← valB + 8`     |
| **Memory**    |                          | `M₈[valE] ← valP`      | `valM ← M₈[valA]`     |
| **Write Back**|                          | `R[%rsp] ← valE`       | `R[%rsp] ← valE`      |
| **PC Update** | `PC ← Cnd ? valC : valP` | `PC ← valC`            | `PC ← valM`           |


---

## Computations in each SEQ stage

| Stage     | Computation | OPq rA, rB         | mrmovq D(rB), rA   |
|-----------|-------------|--------------------|--------------------|
| Fetch     | icode, ifun | icode:ifun ← M₁[PC]| icode:ifun ← M₁[PC]|
|           | rA, rB      | rA:rB ← M₁[PC+1]   | rA:rB ← M₁[PC+1]   |
|           | valC        |                    | valC ← M₈[PC+2]    |
|           | valP        | valP ← PC + 2      | valP ← PC + 10     |
| Decode    | valA, srcA  | valA ← R[rA]       |                    |
|           | valB, srcB  | valB ← R[rB]       | valB ← R[rB]       |
| Execute   | valE        | valE ← valB OP valA| valE ← valB + valC |
|           | Cond. codes | Set CC             |                    |
| Memory    | Read/write  |                    | valM ← M₈[valE]    |
| Write back| E port, dstE| R[rB] ← valE       |                    |
|           | M port, dstM|                    | R[rA] ← valM       |
| PC update | PC          | PC ← valP          | PC ← valP          |

---

## SEQ Timing

- SEQ uses `combinational` logic and `two types of memory` devices: 
  - clocked registers and random access memories.
- The processor is controlled by `a single clock signal` that triggers updates to registers and memory writes.
- Four hardware units require explicit sequencing: 
  - program counter, condition code register, data memory, and register file.
- SEQ follows the `No reading back principle`: 
  - it never needs to read back state updated by an instruction to complete processing.
- Each clock cycle triggers the execution of a new instruction:
  1. At cycle start, state elements hold values from previous instruction.
  2. Combinational logic processes current instruction.
  3. By cycle end, new values are generated but not yet stored in state elements.
  4. As clock rises to start next cycle, state elements are updated with new values.
- This process allows SEQ to achieve the same effect as sequential execution, 
  - even though all state `updates occur simultaneously at the start of each cycle`.
- 📝 time the code
  ```python
  OxOOO:     irmovq $0x100, %rbx     # %rbx <-- 0x100
  OxOOa:     irmovq $0x200, %rdx     # %rdx <-- 0x200
  Ox014:     addq %rdx, %rbx         # %rbx <-- 0x300, CC <-- 000
  Ox016:     je dest                 # Not taken
  Ox01f:     rmmovq %rbx, 0(%rdx)    # M[0x200] <-- 0x300
  Ox029:     dest: halt              # Halt
  ```
- The `halt` instruction sets the processor status to HLT, 
  - halting operation.
- The `nop` instruction passes through stages without much processing, 
  - only incrementing the PC by 1. 

---

## SEQ Stage Implementation: `Fetch`

- Instruction memory reads `10 bytes` starting at the address specified by the PC.
- The first `byte (byte 0)` is split into two 4-bit quantities: `icode and ifun`.
- If the instruction address is `invalid (imem_error)`, 
  - icode and ifun are set to `nop` values.
- Three 1-bit signals are computed based on icode:
  - `instr_valid`: Indicates if the byte is a `legal` Y86-64 instruction.
  - `need_regids`: Indicates if the instruction includes a `register specifier byte`.
  - `need_valC`: Indicates if the instruction includes a `constant word`.
- The remaining 9 bytes are processed by the "Align" unit:
  - `Byte 1` is split into `rA and rB` if `need_regids is 1`.
  - If `need_regids is 0`, both rA and rB are set to `0xF (RNONE)`.
  - `valC` is generated from either `bytes 1-8 or 2-9`, depending on need_regids.
- The PC incrementer generates valP based on `the current PC, need_regids, and need_valC`.
- The formula for valP is: $`p + 1 + r + 8i`$, 
  - where p is the PC value, r is need_regids, and i is need_valC.

---

## SEQ Stage Implementation: `Decode and Write-Back`

-  The decode and write-back stages in SEQ are `combined` 
   -  due to `shared register file access`.
-  The register file has four ports: 
   -  two for simultaneous `reads (A and B)` 
   -  two for simultaneous `writes (E and M)`.
   -  Each port has an `address` connection (register ID) and a `data` connection (64 wires for input/output).
   -  `Read` ports use `srcA and srcB` as address inputs, 
   -  `write` ports use `dstE and dstM`.
-  `OxF (RNONE)` indicates `no register` should be accessed.
-  Four blocks generate register IDs based on `icode, rA, rB, and Cnd`.
-  srcA determines which register to read for valA, depending on instruction type.
-  dstE indicates the destination register for write port E, where valE is stored.

---

## SEQ Stage Implementation: `Execute`

- **Execute Stage** involves the ALU, 
  - which performs operations (ADD, SUB, AND, XOR) on inputs `aluA` and `aluB`, 
  - based on the `alufun` signal.
- **ALU output** becomes `valE`, used in the subsequent stages.
- **Control Blocks** generate data and control signals for the ALU.
- **ALU Operand Values**: 
  - `aluA` can be `valA`, `valC`, or -8/+8 depending on the instruction.
- **ALU Behavior** for various instructions:
  - For `OPq`, ALU performs operations specified in the `ifun` field.
  - For others, ALU mostly acts as an adder.
- **Condition Codes**: 
  - Set when an `OPq` instruction is executed, 
  - based on ALU output `(zero, sign, overflow)`.
  - **Branch/Transfer Control**: 
    - A "cond" unit uses condition codes and `ifun` to decide on conditional branches or data transfers.
  - **Set_CC**: A control signal that updates condition codes for `OPq` instructions.
  - **Other Instructions**: Don't require ALU computations but use `cond` to control actions.

---

## SEQ Stage Implementation: `Memory`

- Performs the following tasks:
  - Reads or writes program data to/from memory
  - Generates memory address and input data for write operations
  - Controls read/write operations with specific signals
  - Produces valM signal for read operations
  - Uses valE or valA as the memory address for reads and writes
  - Sets mem_read control signal for instructions that read from memory
  - Computes the status code (Stat) based on icode, imem_error, instr_valid, and dmem_error
- The memory address (mem_addr) is determined as follows:
  - valE for IRMMDVQ, IPUSHQ, ICALL, and IMRMDVQ instructions
  - valA for IPDPQ and IRET instructions
  - Not needed for other instructions
- The mem_read signal is set for IMRMOVQ, IPDPQ, and IRET instructions

---

## SEQ Stage Implementation: `PC Update`

- **PC Update Stage** selects the new program counter value based on `instruction type and branch condition`: 
  - `valC` for calls or taken branches, 
  - `valM` for RET completion, 
  - and `valP` for the default incremented PC.
- **HCL Description**: The next PC is determined by the instruction and branch condition, either from `valC`, `valM`, or `valP`.

## SEQ Summary

- **SEQ Design**: 
  - Y86-64 processor uses a single clock and minimal hardware units, 
  - with control logic routing signals based on instruction types and conditions.
- **SEQ Limitation**: 
  - Slow performance due to signal propagation delays and underutilized units. 
  - `Pipelining` will improve efficiency.
- 📝 Explore SEQ [implementation](./y86sim/sim.xz)
  - in [hcl](./y86sim/hcl.pdf) 
  - in [verilog](./y86sim/verilog.pdf)

---

# References
- [Intel® 64 and IA-32 Architectures Software Developer's Manual Combined Volumes](https://www.intel.com/content/www/us/en/content-details/782158/intel-64-and-ia-32-architectures-software-developer-s-manual-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html)
  - [x86-64 Instructions Set](https://linasm.sourceforge.net/docs/instructions/index.php)
  - [x86 and amd64 instruction reference](https://www.felixcloutier.com/x86/)
- [Y86-64 simulator](https://github.com/gyunseo/sim)
- [RISC-V Instruction Set Manual](https://github.com/riscv/riscv-isa-manual)