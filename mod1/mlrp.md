# Machine-Level Representation of Programs
CS:APP3e.ch03

Basics
---

## 🔭 Explore 
- [List of Intel processors](https://en.wikipedia.org/wiki/List_of_Intel_processors)
  - [Intel history](https://timeline.intel.com/)
- [List of ARM processors](https://en.wikipedia.org/wiki/List_of_ARM_processors)
- [List of RISC V cores](https://github.com/riscvarchive/riscv-cores-list)
- [processor lineage](https://csgenome.org/lineage)

---

## ISA:	Instruction Set Architecture
- Defines **what** a CPU can do
- **Key Components**:
  - **Instruction Format**: Structure of instructions (opcode, operands).
  - **Instruction Types**: Data transfer, arithmetic/logical, control flow.
  - **Addressing Modes**: Methods to access operands (immediate, direct, indirect).
  - **Registers and Data Types**:
    - Number, size, and type (e.g., integers, floating-point).
  - **Memory Model**:
    - Defines endianness, alignment, and virtual memory behavior.
- **Microarchitecture** defines **how** the CPU performs those tasks:
  - Instruction fetching, decoding, and execution.
  - Handling parallelism and optimizing performance.

---

## Examples and Types of ISA**
- **Examples**:
  - **x86**: CISC, used in desktops/servers.
    - IA32 → **x86-64**
  - **ARM**: RISC, popular in mobile/embedded systems.
  - **RISC-V**: Open-source, modular.
- **ISA Types**:
  - **RISC**: complex instruction set computer
    - Simple, fast instructions optimized for speed.
  - **CISC**: reduced Instruction Set Computer
    - Complex instructions, fewer lines of code, optimized for functionality.

---

## Machine-Level Representation of Programs
- Represented in `byte-level` programs (`machine Code`) that a processor executes
  - Show in `assembly` code (a `mnemonic` text representation of machine code) for readability
- 💡 View [machine code/assembly](./code/mlrp/mam.c) and programmer visible `computer state` in Visual Studio
  - PC — program counter holds the address of the next instruction
    - called `RIP` in x86-64
  - Condition codes (`CPU flags`) store status information about most recent arithmetic or logical operation
    - Used for `conditional branching`
  - `Register files` hold heavily used program data
  - `Memory` holds code, user data, `stack` to support procedures

---

## `AT&T` and `Intel` assembly code formats
```assembly
# AT&T Syntax:
movl $5, %eax       # Load 5 into eax
movl %eax, 8(%ebp)  # Store eax into memory at ebp+8

; Intel Syntax:
mov eax, 5          ; Load 5 into eax
mov [ebp + 8], eax  ; Store eax into memory at ebp+8
```

| **Feature**              | **AT&T Syntax**                                         | **Intel Syntax**                                       |
|--------------------------|--------------------------------------------------------|------------------------------------------------------|
| **Operand Order**        | Source → Destination                                    | Destination ← Source                                  |
| **Instruction Example**  | `movl %eax, %ebx` (`eax` → `ebx`)                | `mov ebx, eax` (`ebx` ← `eax`)                |
| **Register Prefix**      | Registers prefixed with `%` (e.g., `%eax`)             | No prefix (e.g., `eax`)                             |
| **Immediate Values**     | Prefixed with `$` (e.g., `$10`)                        | No prefix (e.g., `10`)                              |
| **Memory Operands**      | `offset(base, index, scale)`                           | `[base + index*scale + offset]`                     |
| **Instruction Suffixes** | Suffixes indicate operand size: `b` (byte), `w` (word), `l` (long), `q` (quad) | Operand size implied or `specified with directives` (e.g., `DWORD PTR`) |
| **Size Example**         | `movl %eax, %ebx` (move 32 bits)                      | `mov ebx, eax` (move 32 bits)                      |
| **Memory Example**       | `movl 8(%ebp), %eax` (load from `ebp+8` to `eax`)     | `mov eax, [ebp + 8]`                                |
| **Comments**             | Start with `#`                                        | Start with `;`                                      |
| **Segmentation**         | `movw %gs:offset, %ax`                                | `mov ax, gs:offset`                                 |
| **Index Scaling**        | `offset(base, index, scale)` (e.g., `4(%ebx, %esi, 2)`) | `[base + index*scale + offset]` (e.g., `[ebx + esi*2 + 4]`) |

---

## 💡 Generate assembly code in AT&T and Intel formats
- Generate assembly code from [C](./code/mlrp/mam.c)
  ```bash
  # 1. AT&T
  gcc -S -o mam.s mam.c # in AT&T syntax by default.

  # 2. Intel
  gcc -S -masm=intel -o mam.si mam.c

  # 3. Assemble and Run (Optional)
  gcc -o mam mam.s
  ```

---

## **x86-64 Integer Registers**

| **Register** | **Purpose**                                   | **64-bit** | **32-bit** | **16-bit** | **8-bit**   |
|--------------|-----------------------------------------------|------------|------------|------------|-------------|
| **Basic General-Purpose Registers**                                                                               |
| RAX          | Accumulator (used in arithmetic and returns) | `rax`      | `eax`      | `ax`       | `al`        |
| RBX          | Base register (callee-saved)                 | `rbx`      | `ebx`      | `bx`       | `bl`        |
| RCX          | Counter (used in loops and shifts)           | `rcx`      | `ecx`      | `cx`       | `cl`        |
| RDX          | Data register (I/O and multiplications)      | `rdx`      | `edx`      | `dx`       | `dl`        |
| RSI          | Source index (string operations)            | `rsi`      | `esi`      | `si`       | `sil`       |
| RDI          | Destination index (string operations)        | `rdi`      | `edi`      | `di`       | `dil`       |
| RBP          | Base pointer (→ stack frames)         | `rbp`      | `ebp`      | `bp`       | `bpl`       |
| RSP          | Stack pointer (→ stack top)           | `rsp`      | `esp`      | `sp`       | `spl`       |
| **Additional General-Purpose Registers (x86-64 specific)**                                                    |
| R8           | General-purpose                             | `r8`       | `r8d`      | `r8w`      | `r8b`       |
| R9           | General-purpose                             | `r9`       | `r9d`      | `r9w`      | `r9b`       |
| R10          | General-purpose                             | `r10`      | `r10d`     | `r10w`     | `r10b`      |
| R11          | General-purpose                             | `r11`      | `r11d`     | `r11w`     | `r11b`      |
| R12          | General-purpose (callee-saved)              | `r12`      | `r12d`     | `r12w`     | `r12b`      |
| R13          | General-purpose (callee-saved)              | `r13`      | `r13d`     | `r13w`     | `r13b`      |
| R14          | General-purpose (callee-saved)              | `r14`      | `r14d`     | `r14w`     | `r14b`      |
| R15          | General-purpose (callee-saved)              | `r15`      | `r15d`     | `r15w`     | `r15b`      |
| **Special Registers**                                                                                         |
| RIP          | Instruction pointer                         | `rip`      | -          | -          | -           |
| FLAGS        | Status flags                                | `rflags`   | `eflags`   | `flags`    | -           |

---

## **Assembly Data Types**

| **Category**    | **Type**    | **Size**  | **Description**     | **Assembly Size Specifier** |
|-----------------|------------|--------|---------|---------|
| **Integer Data**         | Byte                     | 1 byte (8 bits)    | Smallest integer type.   | `BYTE` |
|                          | Word                     | 2 bytes (16 bits)  | Used for larger integers or addresses.    | `WORD` |
|                          | Double Word (DWord)      | 4 bytes (32 bits)  | Standard integer size for many 32-bit systems.  | `DWORD` |
|                          | Quad Word (`QWord`)        | 8 bytes (64 bits)  | Standard integer size for 64-bit systems.   | `QWORD` |
|                          | `Address (Pointer)`        | 4 or 8 bytes        | Untyped memory address (4 bytes on 32-bit, `8 bytes on 64-bit`).    | `DWORD/QWORD` |
| **Floating-Point Data**  | Single-Precision Float   | 4 bytes (32 bits)  | IEEE 754 single-precision floating-point number.     | `DWORD` |
|                          | Double-Precision Float   | 8 bytes (64 bits)  | IEEE 754 double-precision floating-point number. | `QWORD` |
|                          | Extended Precision Float | 10 bytes (80 bits) | Extended precision for floating-point operations (x87 FPU registers).          | `TBYTE` |
| **Code**                 | Machine Code             | Variable           | ➤Byte sequences representing instructions for the CPU. <br>➤Each byte encodes an operation or part of an operation.                          | N/A |
| **Aggregate Types**      | No Native Aggregates     | Variable          | ➤Arrays or structures are represented as contiguous memory regions (untyped). <br>➤Accessing elements requires manual offset calculations.   | N/A |

---

## Moving Data
- `movq Dest, Source` operand Types: Register(`R`), Immediate(`I`), Memory (`M`)

| **Operand Type**           | **Example**              | **C Analog**                              | **Description**                                                                 |
|----------------------------|------------------------------------------|-------------------------------------------|---------------------------------------------------------------------------------|
| **R ← R**   | `movq rax, rbx`                         | `long rax = rbx;`                         | Moves data between two registers.                                              |
| **R ← M**     | `movq rax, QWORD PTR [rbp+8]`           | `long rax = *(long*)(rbp + 8);`           | Loads a 64-bit value from memory into a register.                              |
| **M ← R**     | `movq QWORD PTR [rsp+16], rax`          | `*(long*)(rsp + 16) = rax;`               | Stores a 64-bit value from a register into memory.                             |
| **R ← I**  | `movq rax, 10`                          | `long rax = 10;`                          | Moves a constant value into a register.                                        |
| **M ← I**    | `movq QWORD PTR [rbp-8], 42`            | `*(long*)(rbp - 8) = 42;`                 | Stores a constant value directly into memory.                                  |
| **M ← M**       | N/A (Not Allowed)                      | N/A                                       | Direct memory-to-memory moves are not supported in x86-64 assembly.            |

---

## X86-64 Memory Mode Addressing
- Accesses the operand stored in a location in memory via an `address`
- This is referred to as `indirection or dereferencing`.

| **Addressing Mode**       | **Assembly Example**               | **C Example**                          | **Description**                                                                 |
|---------------------------|------------------------------------|----------------------------------------|---------------------------------------------------------------------------------|
| **Direct (Absolute)**     | `mov eax, [0x1000]`               | `int x = *((int*)0x1000);`             | Use a fixed memory address directly.                                           |
| **Register Indirect**     | `mov ebx, [rax]`                  | `int y = *ptr;`                        | ➤Use a memory address stored in a register. <br>➤`rax=ptx;` |
| **Base + Displacement**   | `mov eax, [rbp + 8]`              | `int x = arr[2];`                      | ➤Use a base register with a constant offset. <br>➤`rbp=arr;` |
| **Indexed**               | `mov ecx, [rax + rbx]`            | `int x = arr[i];`                      | ➤Use a base register and an index register.  <br>➤`rax=arr, rbx=i;` |
| **Scaled Indexed**        | `mov ecx, [rax + rbx*4]`          | `int x = arr[i];` (if `int` is 4 bytes)| ➤Use a base register, an index register, and a `scale factor` (or `array element size`:1, 2, 4, or 8). <br>➤`rax=arr, rbx=i;`  |
| **RIP-Relative**          | `mov eax, [rip + 0x2000]`         | `int x = global_var;`                  | Use an offset relative to the instruction pointer (common for global variables).|
| **Base + Index + Displacement** | `mov ecx, [rax + rbx*4 + 8]` | `int x = arr[i + 2];`                  | ➤Combine base, index, scale, and displacement. <br>➤`rax=arr, rbx=i;` |

---

## `lea` — Load Effective Address
| **Aspect**               | **Description**                                                                 |
|--------------------------|---------------------------------------------------------------------------------|
| **Purpose**              | `Computes the address` of a memory operand and stores it in a register `without accessing memory`. |
| **Syntax**               | **`lea destination, source`** <br>➤destination: a register like `rax`, `rbx`, etc.<br>➤source: a memory operand like `[base + index*scale + displacement]` |
| **Key Features**         | ➤ Performs efficient arithmetic like addition and multiplication.<br>➤ Supports all addressing modes. |
| **Common Uses**          | ➤ Pointer arithmetic like array indexing.<br>➤ RIP-relative addressing.<br>➤ Function prologues. |

- 🍎 Examples and Comparison with `mov`

| **Category**             | **Example**                                                                     | **Description**                                                                 |
|--------------------------|---------------------------------------------------------------------------------|---------------------------------------------------------------------------------|
| **Addressing Modes**     | `lea rax, [rbx + rcx*4 + 8]`                                                   | Computes `rbx + rcx*4 + 8` and stores in `rax`.                                |
| **RIP-Relative**         | `lea rax, [rip + global_var]`                                                  | Computes the address of `global_var` using RIP-relative addressing.            |
| **Function Prologue**    | `lea rbp, [rsp + 16]`                                                          | Sets up a new stack frame by computing `rsp + 16` and storing it in `rbp`.     |
| **Comparison with `mov`**| ➤`lea rax, [rbx + rcx*4]`  <br>➤ `mov rax, [rbx + rcx*4]`                          | ➤ `lea` computes the address; <br>➤ `mov` accesses memory to load/store data.          |

- 📝 Explore x86-64 [memory mode addressing](./code/mlrp/mam.c)
  - Investigate the `swap` function and array iteration

---

Here’s a summary of **x86-64 instructions** for **arithmetic**, **logical**, and **bitwise** operations, organized into a table for clarity:

---

## **x86-64 Arithmetic, Logical, and Bitwise Instructions**
- [Intel® 64 and IA-32 Architectures Software Developer’s Manual Combined Volumes](https://www.intel.com/content/www/us/en/content-details/782158/intel-64-and-ia-32-architectures-software-developer-s-manual-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html)

| **Category**   | **Instruction** | **Syntax**                     | **Description**                                                                 |
|----------------|-----------------|--------------------------------|---------------------------------------------------------------------------------|
| **Arithmetic** | `add`           | `add dest, src`                | Adds `src` to `dest` (e.g., `add eax, ebx`).                                   |
|                | `sub`           | `sub dest, src`                | Subtracts `src` from `dest` (e.g., `sub eax, 5`).                              |
|                | `mul`           | `mul src`                      | Multiplies `eax` by `src` (unsigned). Result in `edx:eax`.                     |
|                | `imul`          | `imul dest, src`               | Multiplies `dest` by `src` (signed). Result in `dest`.                         |
|                | `div`           | `div src`                      | Divides `edx:eax` by `src` (unsigned). Quotient in `eax`, remainder in `edx`.  |
|                | `idiv`          | `idiv src`                     | Divides `edx:eax` by `src` (signed). Quotient in `eax`, remainder in `edx`.    |
|                | `inc`           | `inc dest`                     | Increments `dest` by 1 (e.g., `inc eax`).                                      |
|                | `dec`           | `dec dest`                     | Decrements `dest` by 1 (e.g., `dec ebx`).                                      |
|                | `neg`           | `neg dest`                     | Negates `dest` (e.g., `neg eax`).                                              |
| **Logical**    | `and`           | `and dest, src`                | Bitwise AND of `dest` and `src` (e.g., `and eax, ebx`).                        |
|                | `or`            | `or dest, src`                 | Bitwise OR of `dest` and `src` (e.g., `or eax, 0xFF`).                         |
|                | `xor`           | `xor dest, src`                | Bitwise XOR of `dest` and `src` (e.g., `xor eax, eax` clears `eax`).           |
|                | `not`           | `not dest`                     | Bitwise NOT of `dest` (e.g., `not eax`).                                       |
|                | `test`          | `test dest, src`               | Bitwise AND of `dest` and `src`, sets flags but does not store result.         |
| **Bitwise**    | `shl`           | `shl dest, count`              | Shifts `dest` left by `count` bits (e.g., `shl eax, 2`).                       |
|                | `shr`           | `shr dest, count`              | Shifts `dest` right by `count` bits (logical shift, e.g., `shr eax, 3`).       |
|                | `sal`           | `sal dest, count`              | Arithmetic shift left (same as `shl`).                                         |
|                | `sar`           | `sar dest, count`              | Arithmetic shift right (preserves sign bit, e.g., `sar eax, 4`).               |
|                | `rol`           | `rol dest, count`              | Rotates `dest` left by `count` bits (e.g., `rol eax, 1`).                      |
|                | `ror`           | `ror dest, count`              | Rotates `dest` right by `count` bits (e.g., `ror eax, 2`).                     |
|                | `rcl`           | `rcl dest, count`              | Rotates `dest` left through carry flag by `count` bits.                        |
|                | `rcr`           | `rcr dest, count`              | Rotates `dest` right through carry flag by `count` bits.                       |
|                | `bts`           | `bts dest, bit`                | Sets the specified bit in `dest` (e.g., `bts eax, 3` sets bit 3 of `eax`).     |
|                | `btr`           | `btr dest, bit`                | Resets the specified bit in `dest` (e.g., `btr eax, 5` clears bit 5 of `eax`). |
|                | `btc`           | `btc dest, bit`                | Toggles the specified bit in `dest` (e.g., `btc eax, 7` flips bit 7 of `eax`). |

- 📝 Investigate x86-84 [basic instructions](./code/mlrp/balc.c).

---

## Why Manual Assembly Programming Is Rare Today

| **Generation**       | **Release Year** | **Total Instructions** | **Arithmetic/Logic** | **Control/Branch** | **SIMD/Multimedia** | **Cryptography** | **Other (System, etc.)** |
|-----------------------|------------------|-------------------------|-----------------------|---------------------|---------------------|------------------|--------------------------|
| 8086                 | 1978             | ~80                    | ~40                  | ~20                | N/A                 | N/A              | ~20                     |
| 80286                | 1982             | ~117                   | ~50                  | ~25                | N/A                 | N/A              | ~42                     |
| 80386                | 1985             | ~140                   | ~60                  | ~30                | N/A                 | N/A              | ~50                     |
| 80486                | 1989             | ~150                   | ~65                  | ~30                | N/A                 | N/A              | ~55                     |
| Pentium (P5)         | 1993             | ~200                   | ~80                  | ~35                | ~30                 | N/A              | ~55                     |
| Pentium II           | 1997             | ~220                   | ~85                  | ~40                | ~50                 | N/A              | ~45                     |
| Pentium III          | 1999             | ~250                   | ~90                  | ~45                | ~70                 | N/A              | ~45                     |
| Pentium 4            | 2000             | ~300                   | ~100                 | ~50                | ~100                | N/A              | ~50                     |
| Core 2               | 2006             | ~500                   | ~120                 | ~70                | ~200                | ~10              | ~100                    |
| Nehalem              | 2008             | ~700                   | ~150                 | ~100               | ~300                | ~20              | ~130                    |
| Sandy Bridge         | 2011             | ~1,000                 | ~180                 | ~120               | ~450                | ~50              | ~200                    |
| Haswell              | 2013             | ~1,400                 | ~200                 | ~140               | ~800                | ~80              | ~180                    |
| Skylake              | 2015             | ~1,700                 | ~220                 | ~160               | ~1,000              | ~120             | ~200                    |
| Ice Lake             | 2019             | ~2,000                 | ~250                 | ~180               | ~1,200              | ~200             | ~170                    |
| Alder Lake           | 2021             | ~2,500                 | ~300                 | ~200               | ~1,500              | ~250             | ~250                    |

- High-level languages and modern compilers `abstract` low-level details and produce highly `optimized` code, making development faster and more efficient.  
- Manual assembly is now limited to niche areas like embedded systems, `performance-critical` tasks, and `reverse engineering`.  

## References
- [RISC V Resources](https://github.com/suryakantamangaraj/AwesomeRISC-VResources)
- [ARM documentation](https://developer.arm.com/documentation)
- [RISC-V Instruction Set Manual](https://github.com/riscv/riscv-isa-manual)
