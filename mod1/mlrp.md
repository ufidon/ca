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


## Manual Assembly Programming Is Rare Today But Essential

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

- High-level languages and modern compilers `abstract` low-level details and produce highly `optimized` code, 
  - making development faster and more efficient.  
- Manual assembly is now limited to niche areas like 
  - `embedded` systems, `performance-critical` tasks, and `reverse engineering`.  

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

## Examples and Types of ISA
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

- 💡 Explore [x86-64 integer registers](./code/mlrp/mam.c) 

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

## [x86-64 Data Movement Instructions](https://linasm.sourceforge.net/docs/instructions/cpu.php#data)

| **Instruction** | **Syntax**                     | **Description**                                                                 |
|------------------|--------------------------------|---------------------------------------------------------------------------------|
| **`mov`**        | `mov dest, src`                | Moves data from `src` to `dest`.                                               |
| **`movzx`**      | `movzx dest, src`              | Moves `src` to `dest` with zero extension (for unsigned values).               |
| **`movsx`**      | `movsx dest, src`              | Moves `src` to `dest` with sign extension (for signed values).                 |
| **`lea`**        | `lea dest, [src]`              | Loads the effective address of `src` into `dest`.                              |
| **`xchg`**       | `xchg dest, src`               | Exchanges the contents of `dest` and `src`.                                    |
| **`cmovcc`**     | `cmovcc dest, src`             | Conditionally moves `src` to `dest` based on flags (e.g., `cmove`, `cmovne`).  |
| **`movaps`**     | `movaps dest, src`             | Moves aligned packed single-precision floating-point values.                   |
| **`movups`**     | `movups dest, src`             | Moves unaligned packed single-precision floating-point values.                 |
| **`movdqa`**     | `movdqa dest, src`             | Moves aligned packed integer values (128-bit).                                 |
| **`movdqu`**     | `movdqu dest, src`             | Moves unaligned packed integer values (128-bit).                               |
| **`movq`**       | `movq dest, src`               | Moves 64-bit data between registers or memory.                                 |
| **`movd`**       | `movd dest, src`               | Moves 32-bit data between registers or memory.                                 |
| **`movnti`**     | `movnti dest, src`             | Moves data to memory without caching (non-temporal move).                      |
| **`push`**       | `push src`                     | Pushes `src` onto the stack.                                                   |
| **`pop`**        | `pop dest`                     | Pops data from the stack into `dest`.                                          |
| **`pusha`**      | `pusha`                        | Pushes all general-purpose registers onto the stack.                           |
| **`popa`**       | `popa`                         | Pops all general-purpose registers from the stack.                             |
| **`pushf`**      | `pushf`                        | Pushes the EFLAGS register onto the stack.                                     |
| **`popf`**       | `popf`                         | Pops the EFLAGS register from the stack.                                       |
| **`lds`**        | `lds dest, src`                | Loads `dest` and the DS segment register from `src`.                           |
| **`les`**        | `les dest, src`                | Loads `dest` and the ES segment register from `src`.                           |
| **`lfs`**        | `lfs dest, src`                | Loads `dest` and the FS segment register from `src`.                           |
| **`lgs`**        | `lgs dest, src`                | Loads `dest` and the GS segment register from `src`.                           |
| **`lss`**        | `lss dest, src`                | Loads `dest` and the SS segment register from `src`.                           |
| **`xlat`**       | `xlat`                         | Translates a byte in `al` using a table pointed to by `bx` or `ebx`.           |

---

## `mov` — Moving Data
- `mov Dest, Source` operand Types: Register(`R`), Immediate(`I`), Memory (`M`)

| **Operand Type**           | **Example**              | **C Analog**                              | **Description**                                                                 |
|----------------------------|------------------------------------------|-------------------------------------------|---------------------------------------------------------------------------------|
| **R ← R**   | `mov rax, rbx`                         | `long rax = rbx;`                         | Moves data between two registers.                                              |
| **R ← M**     | `mov rax, QWORD PTR [rbp+8]`           | `long rax = *(long*)(rbp + 8);`           | Loads a 64-bit value from memory into a register.                              |
| **M ← R**     | `mov QWORD PTR [rsp+16], rax`          | `*(long*)(rsp + 16) = rax;`               | Stores a 64-bit value from a register into memory.                             |
| **R ← I**  | `mov rax, 10`                          | `long rax = 10;`                          | Moves a constant value into a register.                                        |
| **M ← I**    | `mov QWORD PTR [rbp-8], 42`            | `*(long*)(rbp - 8) = 42;`                 | Stores a constant value directly into memory.                                  |
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
| **Scaled Indexed**        | `mov ecx, [rax + rbx*4]`          | `int x = arr[i];` (if `int` is 4 bytes)| ➤Use a base register, an index register, and a `scale factor` (1, 2, 4, or 8). <br>➤`rax=arr, rbx=i;`  |
| **RIP-Relative**          | `mov eax, [rip + 0x2000]`         | `int x = global_var;`                  | Use an offset relative to the instruction pointer (common for global variables).|
| **Base + Index + Displacement** | `mov ecx, [rax + rbx*4 + 8]` | `int x = arr[i + 2];`                  | ➤Combine base, index, scale, and displacement. <br>➤`rax=arr, rbx=i;` |

---

## 📝 Find the values of I,R, and M operands
- Given the following values stored at the indicated memory addresses and registers:

| Address | Value | Register | Value |
|---------|-------|----------|-------|
| 0x100   | 0xFF  |  rax     | 0x100 |
| 0x104   | 0xAB  |  rcx     | 0x1   |
| 0x108   | 0x13  |  rdx     | 0x3   |
| 0x10C   | 0x11  |          |       |

- Fill in the following table showing the values for the indicated `operands`:

| `Operand` <br> Intel Syntax | Value  | `Operand` <br> AT&T Syntax  |
|-------------------------|--------|------------------|
| rax                     | 0x100  | %rax             |
| [0x104]                 | 0xAB   | 0x104            |
| 0x108                   | 0x108  | $0x108           |
| [rax]                   | 0xFF   | (%rax)           |
| [rax + 4]               | 0xAB   | 4(%rax)          |
| [rax + rdx + 9]         | 0x11   | 9(%rax,%rdx)     |
| [rcx + rdx + 260]       | 0x13   | 260(%rcx,%rdx)   |
| [rcx*4 + 0xFC]          | 0xFF   | 0xFC(,%rcx,4)    |
| [rax + rdx*4]           | 0x11   | (%rax,%rdx,4)    |
| [rax + rcx*4 + 8]       | 0x11   | 8(%rax,%rcx,4)   |

---

## `lea` — Load Effective Address
| **Aspect**               | **Description**                                                                 |
|--------------------------|---------------------------------------------------------------------------------|
| **Purpose**              | ➤ `Computes the address` of a memory operand and stores it in a register <br>➤ `without accessing memory`. |
| **Syntax**               | **`lea destination, source`** <br>➤destination: a register like `rax`, `rbx`, etc.<br>➤source: a memory operand like `[base + index*scale + displacement]` |
| **Key Features**         | ➤ Performs efficient arithmetic like addition and multiplication.<br>➤ Supports all addressing modes. |
| **Common Uses**          | ➤ Pointer arithmetic like array indexing.<br>➤ RIP-relative addressing.<br>➤ Function prologues. |

- 🍎 Examples and Comparison with `mov`

| **Category**             | **Example**                                                                     | **Description**                                                                 |
|--------------------------|---------------------------------------------------------------------------------|---------------------------------------------------------------------------------|
| **Addressing Modes**     | `lea rax, [rbx + rcx*4 + 8]`                                                   | Computes `rbx + rcx*4 + 8` and stores in `rax`.                                |
| **RIP-Relative**         | `lea rax, [rip + global_var]`                                                  | Computes the address of `global_var` using RIP-relative addressing.            |
| **Function Prologue**    | `lea rbp, [rsp + 16]`                                                          | Sets up a new stack frame by computing `rsp + 16` and storing it in `rbp`.     |
| **Comparison with `mov`**| ➤`lea rax, [rbx + rcx*4]`  <br>➤ `mov rax, [rbx + rcx*4]`                          | ➤ `lea` computes the address; <br>➤ `mov` accesses memory to load/store data.        |

- 📝 [Exploit `leaq` for simple arithmetic](./code/mlrp/lea.c)

---

## 📝 Explore 
- x86-64 [memory mode addressing](./code/mlrp/mam.c)
  - Investigate the `swap` function and array iteration
- ☠️ Use [memory addressing modes in assembly](./code/mlrp/addr.s)
  ```bash
  # assemble
  yasm -f elf64 addr.s -o addr.o

  # link
  ld addr.o -o addr -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
  # or
  gcc -nostartfiles -no-pie  -o addr addr.o
  ```

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

## `MOV` data `without extension` 
| Intel Syntax | AT&T Syntax | Effect       | Description               | Intel Syntax Example       | AT&T Syntax Example        |
|--------------|-------------|--------------|---------------------------|----------------------------|----------------------------|
| MOV          | movb        | D ← S        | Move byte                 | `MOV al, bl`               | `movb %bl, %al`            |
| MOV          | movw        | D ← S        | Move word                 | `MOV ax, bx`               | `movw %bx, %ax`            |
| MOV          | movl        | D ← S        | Move double word          | `MOV eax, ebx`             | `movl %ebx, %eax`          |
| MOV          | movq        | D ← S        | Move quad word            | `MOV rax, rbx`             | `movq %rbx, %rax`          |
| MOV          | movabsq     | R ← I        | Move absolute quad word   | `MOV rax, 0x123456789ABCD` | `movabsq $0x123456789ABCD, %rax` |

- 💡 Move data without extension

| Intel Syntax               | AT&T Syntax                  | Description                     |
|----------------------------|------------------------------|---------------------------------|
| `MOV eax, 0x4050`          | `movl $0x4050, %eax`         | Immediate → Register, 4 bytes   |
| `MOV sp, bp`               | `movw %bp, %sp`              | Register → Register, 2 bytes    |
| `MOV al, [rdi + rcx]`      | `movb (%rdi,%rcx), %al`      | Memory → Register, 1 byte       |
| `MOV BYTE PTR [esp], -17`  | `movb $-17, (%esp)`          | Immediate → Memory, 1 byte      |
| `MOV [rbp - 12], rax`      | `movq %rax, -12(%rbp)`       | Register → Memory, 8 bytes      |

---

## 🍎 Move data without extension

| Intel Syntax                          | AT&T Syntax                          | Value of `rax` After Execution | Description                                   |
|---------------------------------------|--------------------------------------|--------------------------------|-----------------------------------------------|
| `MOV rax, 0x0011223344556677`         | `movabsq $0x0011223344556677, %rax`  | `0x0011223344556677`           | Move 64-bit immediate value into `rax`       |
| `MOV al, -1`                          | `movb $-1, %al`                      | `0x00112233445566FF`           | Move 8-bit immediate value into `AL`         |
| `MOV ax, -1`                          | `movw $-1, %ax`                      | `0x001122334455FFFF`           | Move 16-bit immediate value into `AX`        |
| `MOV eax, -1`                         | `movl $-1, %eax`                     | `0x00000000FFFFFFFF`           | Move 32-bit immediate value into `EAX`       |
| `MOV rax, -1`                         | `movq $-1, %rax`                     | `0xFFFFFFFFFFFFFFFF`           | Move 64-bit immediate value into `RAX`       |

- **8-bit and 16-bit operations** only modify the lower bits of `rax`, leaving the upper bits unchanged.
- **⚠️32-bit operations** zero out the upper 32 bits of `rax` due to x86-64 behavior.
- **64-bit operations** modify the entire `rax` register.

---

## Move data with `zero and sign extension`
| Instruction<br>Intel Syntax          | Instruction<br>AT&T Syntax | Effect                          | Description                                   |
|-----------------------|-------------|---------------------------------|-----------------------------------------------|
| **MOVZX**             | **MOVZ**        | **R ← ZeroExtend(S)**               | **Move with zero extension**                    |
| MOVZX r16, r/m8       | movzbw      | R16 ← ZeroExtend(S8)            | Move zero-extended byte → word              |
| MOVZX r32, r/m8       | movzbl      | R32 ← ZeroExtend(S8)            | Move zero-extended byte → double word       |
| MOVZX r32, r/m16      | movzwl      | R32 ← ZeroExtend(S16)           | Move zero-extended word → double word       |
| MOVZX r64, r/m8       | movzbq      | R64 ← ZeroExtend(S8)            | Move zero-extended byte → quad word         |
| MOVZX r64, r/m16      | movzwq      | R64 ← ZeroExtend(S16)           | Move zero-extended word → quad word         |
| **MOVSX**             | **MOVS**        | **R ← SignExtend(S)**               | **Move with sign extension**                     |
| MOVSX r16, r/m8       | movsbw      | R16 ← SignExtend(S8)            | Move sign-extended byte → word              |
| MOVSX r32, r/m8       | movsbl      | R32 ← SignExtend(S8)            | Move sign-extended byte → double word       |
| MOVSX r32, r/m16      | movswl      | R32 ← SignExtend(S16)           | Move sign-extended word → double word       |
| MOVSX r64, r/m8       | movsbq      | R64 ← SignExtend(S8)            | Move sign-extended byte → quad word         |
| MOVSX r64, r/m16      | movswq      | R64 ← SignExtend(S16)           | Move sign-extended word → quad word         |
| *MOVSX r64, r/m32*      | *movslq*      | *R64 ← SignExtend(S32)*           | *Move sign-extended double word → quad word*  |
| CDQE                  | cltq        | rax ← SignExtend(eax)         | Sign-extend eax → rax                     |

- ⚠️ `movzlq` does NOT exist.

---

## MOV vs. MOVZX vs. MOVSX
| Instruction | Source Operand          | Destination Operand | Size Constraints                                                                 |
|-------------|-------------------------|---------------------|----------------------------------------------------------------------------------|
| **MOV**     | Register, Memory, Immediate | Register, Memory    | ➤ Source and destination must be the same size.                                    |
| **MOVZX**   | Register, Memory (8-bit or 16-bit) | Register (16-bit, 32-bit, or 64-bit) | ➤Source must be smaller than destination. <br>➤ Zero-extends the value.                 |
| **MOVSX**   | Register, Memory (8-bit, 16-bit, or 32-bit) | Register (16-bit, 32-bit, or 64-bit) | ➤Source must be smaller than destination. <br>➤ Sign-extends the value.                 |

---

## 🍎 Move data around
| Intel Syntax                          | AT&T Syntax                          | Value of Register <br> After Execution | Description                                   |
|---------------------------------------|--------------------------------------|-----------------------------------|-----------------------------------------------|
| `MOV rax, 0x0011223344556677`         | `movabsq $0x0011223344556677, %rax`  | `rax = 0x0011223344556677`        | Move 64-bit immediate value into `rax`       |
| `MOV dl, 0xAA`                        | `movb $0xAA, %dl`                    | `dl = 0xAA`                       | Move 8-bit immediate value into `dl`         |
| `MOV al, dl`                          | `movb %dl, %al`                      | `rax = 0x00112233445566AA`        | Move 8-bit value from `dl` to `al`           |
| `MOVSX rax, dl`                       | `movsbq %dl, %rax`                   | `rax = 0xFFFFFFFFFFFFFFAA`        | Sign-extend 8-bit value in `dl` to 64-bit `rax` |
| `MOVZX rax, dl`                       | `movzbq %dl, %rax`                   | `rax = 0x00000000000000AA`        | Zero-extend 8-bit value in `dl` to 64-bit `rax` |

- 📝 Explore [data movement instructions](./code/mlrp/mov.c) in Visual Studio
- 📝 Data movement in [assembly](./code/mlrp/mov.s)

---

## `push` and `pop` stack data

- The stack in x86-64 is a **last-in, first-out (LIFO)** data structure 
  - grows `downward lower address` in memory, 
  - managed via the **RSP** register, which points to the `top` of the stack.

| **Instruction <br> Intel Syntax** | **Instruction <br> AT&T Syntax** | **Effect**                                   | **Description**    |
|-------------------|-----------------|---------------------------------------------|--------------------|
| `PUSH S`          | `pushq S`       | ➤ `RSP ← RSP - 8;` <br>➤ `[RSP] ← S`                  | Push quad word     |
| `POP D`           | `popq D`        | ➤ `D ← [RSP];` <br>➤ `RSP ← RSP + 8`                  | Pop quad word      |

- **PUSH**: Decreases the stack pointer (`RSP`) and saves a value onto the stack
  - allowing temporary storage of data such as function parameters, return addresses, or local variables.  
- **POP**: Retrieves a value from the stack by loading it into a register or variable
  - and increases the stack pointer (`RSP`), effectively removing the value.

- 📝 Practice [pushing and poping stack data](./code/mlrp/stack.s)

---

## 🍎 Advanced examples

- 📝 Assemble instructions with [rz-asm](https://rizin.re/)
  ```bash
  # AT&T syntax specifed by -s att
  rz-asm -a x86 -b 64 -s att 'movq $1, %rax'

  # The default syntax is Intel, -s intel can be omitted
  rz-asm -a x86 -b 64 'mov rax, 1'
  ```
- 📝 Assemble [assembly code](./code/mlrp/hello.s) in AT&T syntax with [as](https://sourceware.org/binutils/docs/as/)
  ```bash
  # assemble
  as -o hello.o hello.s

  # disassemble
  objdump -d hello.o

  # link
  ld -o hello hello.o

  # using gcc/clang built-in assembler
  gcc -o hello hello.s -nostdlib
  ```
- 📝 Assemble [assembly code](./code/mlrp/intel.s) in Intel syntax with `as`
  ```bash
  # assemble
  as -o intel.o intel.s

  # link
  ld -o intel intel.o
  # or
  gcc -o intel intel.o -nostartfiles
  # or
  gcc -o intel intel.o -nostdlib
  ```
- 📝 Different assembler has different syntax.
  - Assemble [hwi.s](./code/mlrp/hwi.s) with `yasm`
  ```bash
  yasm -f elf64 -o hwi.o  hwi.s
  ld -o hwi hwi.o
  ```
- 📝 Assembly on win64 [hello.asm](./code/mlrp/hello.asm)
  ```bash
  # assemble
  yasm -f win64 hello.asm -o hello.obj

  # link
  link /subsystem:windows /entry:Start /LARGEADDRESSAWARE:NO hello.obj kernel32.lib user32.lib
  # or
  cl /nologo /Fe:hello.exe hello.obj kernel32.lib user32.lib /link /entry:Start /subsystem:windows  /LARGEADDRESSAWARE:NO
  ```

---

## 💡 Generate assembly code in AT&T and Intel formats
- Generate assembly code from [C](./code/mlrp/mam.c)
  ```bash
  # 1. AT&T
  gcc -S -o mam.s mam.c # in AT&T syntax by default.

  # 2. Intel
  gcc -S -masm=intel -o mam.si mam.c

  # 3. Assemble and Run 
  gcc -o mam mam.s
  ```
- 📝 Find the assembly code for
  - [A C file contains functions only, usually used as library](./code/mlrp/student.c)
  - [The C file calls functions](./code/mlrp/aveweight.c)
  ```bash
  # 1. put student.h, student.c and aveweight.c in the same folder
  # 2. compile only, i.e. generate object files
  gcc -c -o student.o  student.c
  gcc -c -o aveweight.o aveweight.c

  # 3. investigate the machine code of the object files
  objdump -d student.o
  objdump -d aveweight.o

  # 4. link object files
  gcc -o aveweight aveweight.o student.o

  # 5. investigate the machine code of the executable file
  objdump -d aveweight
  ```
---

## **x86-64 Arithmetic, Logical, and Bitwise Instructions**
- Most operations have `size variants` for bytes, words, double words, and quad words.  
- Operations are grouped into load effective address, `unary, binary, and shifts`.

|Instruction <br> (Intel Syntax)| Effect             | Description                     |
|----------------------------|-----------------------|---------------------------------|
| `LEA D, S`                 | `D ← &S`              | Load effective address          |
| `INC D`                    | `D ← D + 1`           | Increment                       |
| `DEC D`                    | `D ← D - 1`           | Decrement                       |
| `NEG D`                    | `D ← -D`              | Negate                          |
| `NOT D`                    | `D ← ~D`              | Complement                      |
| `ADD D, S`                 | `D ← D + S`           | Add                             |
| `SUB D, S`                 | `D ← D - S`           | Subtract                        |
| `IMUL D, S`                | `D ← D * S`           | Multiply                        |
| `XOR D, S`                 | `D ← D ^ S`           | Exclusive-or                    |
| `OR D, S`                  | `D ← D \| S`          | Or                              |
| `AND D, S`                 | `D ← D & S`           | And                             |
| `SAL D, k`                 | `D ← D ≪ k`          | Left shift                      |
| `SHL D, k`                 | `D ← D ≪ k`          | Left shift (same as SAL)        |
| `SAR D, k`                 | $`D ← D ≫_A k`$      | Arithmetic right shift          |
| `SHR D, k`                 | $`D ← D ≫_L k`$      | Logical right shift             |


- 📝 Investigate x86-84 [basic instructions](./code/mlrp/balc.c).
- 📝  Inline assembly in C for gcc [emgcc.c](./code/mlrp/emgcc.c)
  - Visual C++ supports [32-bit inline assembly](./code/mlrp/vc32.c) but NOT 64-bit.

---

## Unary and binary operations

- **Unary Operations**: `OP D`
  - Single operand acts as source and destination (e.g., `inc`).  
  - Resembles C/C++ `++` and `--` operators.  
- **Binary Operations**: `OP L, R`
  - Left operand is source and destination (e.g., `sub`).  
  - **Operand Rules**: `not` both memory
    - Right operand: immediate/register/memory; 
    - Left: register/memory.

- 📝 Given

| Address | Value | Register | Value |
|---------|-------|----------|-------|
| 0x100   | 0xFF  |  rax     | 0x100 |
| 0x108   | 0xAB  |  rcx     | 0x1   |
| 0x110   | 0x13  |  rdx     | 0x3   |
| 0x118   | 0x11  |          |       |

- Find the results

| Instruction (Intel Syntax)       | Instruction (AT&T Syntax)        | Destination       | Value         |
|----------------------------------|----------------------------------|-------------------|---------------|
| `add [rax], rcx`                 | `addq %rcx, (%rax)`              | Memory at `0x100` |  0x100        |
| `sub [rax + 8], rdx`             | `subq %rdx, 8(%rax)`             | Memory at `0x108` |               |
|`imul qword ptr [rax + rdx*8], 16`| `imulq $16, (%rax,%rdx,8)`       | Memory at `0x118` |               |
| `inc qword ptr [rax + 16]`       | `incq 16(%rax)`                  | Memory at `0x110` |               |
| `dec rcx`                        | `decq %rcx`                      | `rcx`             |               |
| `sub rax, rdx`                   | `subq %rdx, %rax`                | `rax`             |               |


- ⚠️ [imul](https://www.felixcloutier.com/x86/imul) instruction cannot directly multiply a memory location by an immediate value
  - For practice purpose only here
- Verify your solution in [assembly](./code/mlrp/ubops.s)

---

## Shift operations
- **Shift Operations**: `SH D, k`
  - `Operand D` can be register or memory
  - `Shift amount k` can be immediate or low-order bits of `cl`
    - `cl` higher bits are ignored: e.g., `cl = 0xFF` shifts 7 for `salb`, 63 for `salq`
- **Left Shifts**: `SAL`/`SHL(≪)` fill with zeros.  
- **Right Shifts**: `SAR`$`(≫_A)`$ fills with sign bit; `SHR`$`(≫_L)`$ fills with zeros.
- 📝 Explore shift operations in 
  - [C](./code/mlrp/shift.c)
  - [assembly](./code/mlrp/shift.s)
  - [inline assembly](./code/mlrp/inshift.c)
- 📝 Explore more operations in [C](./code/mlrp/arith2.c) with Visual Studio
  - more in [assembly](./code/mlrp/arith2.s)

---

## Special arithmetic operations

- `Multiplying two 64-bit` integers (signed or unsigned) can produce a `128-bit result`
  - stored in `rdx`:`rax`
  - referred to as an `oct word (16 bytes)` in x86-64 architecture.  
- **Two `imul` Variants**: distinguished by the assembler based on `operand count`
  - one for $`*_{64}^u`$ and $`*_{64}^t`$ with `64-bit` results from `two 64-bit operands` 
  - the other here for full `128-bit` result from `one-operand S`

| Intel Syntax | AT&T Syntax | Effect (Intel Syntax)                  | Description            |
|--------------|-------------|----------------------------------------|------------------------|
| `IMUL RAX, S`| `imulq S`   | `RDX:RAX ← S * RAX`                    | Signed full multiply   |
| `MUL RAX, S` | `mulq S`    | `RDX:RAX ← S * RAX`                    | Unsigned full multiply |
| `CQO`        | `cqto`      | `RDX:RAX ← SignExtend(RAX)`            | Convert to oct word    |
| `IDIV S`     | `idivq S`   | ➤ `RDX ← RDX:RAX % S` <br>➤ `RAX ← RDX:RAX / S` | Signed divide          |
| `DIV S`      | `divq S`    | ➤ `RDX ← RDX:RAX % S` <br>➤ `RAX ← RDX:RAX / S` | Unsigned divide        |

- 📝 Explore [128-bit arithmetc in C](./code/mlrp/octc.c)
  - in [assembly](./code/mlrp/octa.s)
- **64-bit Division Setup**: 
  - the `dividend` is stored in `rax`, 
  - `rdx` is set to `all zeros (unsigned)` or `sign-extended` from `%rax` (signed) using the `cqto` instruction.  
- 📝 Expore 64-bit division in C
  - [div64.c](./code/mlrp/div64.c) and [udiv64.c](./code/mlrp/udiv64.c)

---

## Signed vs. unsigned arithmetic

| **Aspect**            | **Signed Arithmetic**                                                                 | **Unsigned Arithmetic**                                                              |
|------------------------|--------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------|
| **CPU Flags**          | ➤ **Sign Flag (SF)** for result sign <br>➤  **Overflow Flag (OF)** for signed overflow. | ➤ **Carry Flag (CF)** for unsigned overflow <br>➤  **Zero Flag (ZF)** for zero result. |
| **Instructions**       | `imul`, `idiv`, and `cqto`.   | `mul` and `div`                          |
| **Bit Interpretation** | (MSB) represents the sign (two's complement).                   | All bits represent magnitude (no sign bit).                                          |
| **Overflow Detection** |  **Overflow Flag (OF)**                    | **Carry Flag (CF)**                     | 


---

## References
- [The MASM32 SDK	](https://masm32.com/)
- [flat assembler](https://flatassembler.net/)
- [The Go tools for Windows + Assembler](http://www.godevtool.com/)
- [Intel® 64 and IA-32 Architectures Software Developer’s Manual Combined Volumes](https://www.intel.com/content/www/us/en/content-details/782158/intel-64-and-ia-32-architectures-software-developer-s-manual-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html)
  - [x86-64 Instructions Set](https://linasm.sourceforge.net/docs/instructions/index.php)
  - [x86 and amd64 instruction reference](https://www.felixcloutier.com/x86/)
- [RISC V Resources](https://github.com/suryakantamangaraj/AwesomeRISC-VResources)
- [ARM documentation](https://developer.arm.com/documentation)
- [RISC-V Instruction Set Manual](https://github.com/riscv/riscv-isa-manual)
