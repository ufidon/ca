# Machine-Level Representation of Programs
CS:APP3e.ch03

Data and Beyond
---

# Array Allocation and Access

- C arrays aggregate scalar data into larger types with simple implementation
  - making machine code translation straightforward.
- Pointers to array elements can be generated and used with arithmetic
  - which translates into address computations in machine code.
- Declaring an array `A[N]` allocates `L * N` bytes of memory
  - where `L` is the size of the data type, 
  - introduces a pointer to the start of the array.
- Array indexing is optimized by compilers
  - the x86-64 architecture simplifies array access with scaling factors for common data types (1, 2, 4, 8).

- 📝 Investigate [array](./code/ds/array.c)

---

## Pointer Arithmetic
- C allows `arithmetic on pointers`, scaling by the size of the referenced data type, e.g., given `T *p;`, `p + i` computes `pVal + L * i`, 
  - pVal is the value of p, L is the size of type T.
- **Pointer Operators**: 
  - The `&` operator generates a pointer (address of an object), 
  - the `*` operator dereferences a pointer (accesses value at the address).
- Array subscripting (`A[i]`) is equivalent to pointer arithmetic (`*(A + i)`).
- Array operations and pointer arithmetic result in different types e.g., 
  - `int` for values with 4-byte operations 
  - `int*` for pointers with 8-byte operations, 
  - pointers can be `subtracted to compute differences` in terms of data type sizes.

- 📝 Investigate [pointer](./code/ds/pointer.c)

---

## Nested arrays

- Multidimensional Array Core Concepts:
  - 2D array `int A[5][3]` = 5 rows of 3-integer arrays
  - Total size: 4 bytes * 5 * 3 = 60 bytes
  - Elements stored in row-major order
  - Memory layout follows nested declaration structure

- Element Access Mechanics:
  - Address calculation: `T D[R][C]; &D[i][j] = Dval + L(C * i + j)`
  - Compiler uses efficient scaling and offset computation
  - x86-64 address arithmetic enables direct memory access

- 📝 Investigate [nested array](./code/ds/ma.c)

---

## Fixed-Size Array Optimization
- Maximize performance through static array size information during compilation
- Eliminate runtime index checks
- Enable direct memory access
- Simplify pointer arithmetic
- Optimize register usage
 
- 📝 Investigate [fixed-size array](./code/ds/opt.c)

---

## Variable-Size Arrays
- Introduced in `C99`, computed at `runtime` based on expressions.
- **Array Addressing**: Variable-size arrays `use multiplication to scale indices`
- Compilers optimize multidimensional array access in loops to improve performance by using `scaling and pointer arithmetic`.

- 📝 Investigate [var-size array](./code/ds/var.c)

---

# Heterogeneous Data Structures

---

## Structures

- **C structs** group `different types into a single object` 
  - fields are accessed by name.
  - Fields are stored contiguously, and the pointer is the address of the first byte.
- The compiler calculates field offsets and generates code to reference them.
- Machine code handles field access at compile time.

- 📝 Investigate [structure](./code/ds/rect.c)

---

## Unions

- **Unions** allow a single object to be referenced by multiple types, with all fields sharing the same memory space.
- The union's size equals the largest field size.
- **Use Case**: Unions save memory when fields are mutually exclusive but can lead to bugs due to the lack of type safety.

- 📝 Investigate [union](./code/ds/union.c)

---

## Data Alignment

- **Alignment Restrictions**: Data must be aligned to multiples of `1, 2, 4, or 8` for efficiency.
- **x86-64 Flexibility**: Hardware works without strict alignment, but Intel recommends it for better performance.
- **Alignment Rule**: Primitive objects of `K` bytes must have addresses that are multiples of `K`.
  - This applies to types like `char`, `short`, `int`, `float`, `long`, `double`, and `char *`.
- **Padding**: Compilers `add gaps` in structures and arrays to meet alignment requirements, sometimes wasting memory.
  - Structure size is `rounded up to the largest` field's alignment requirement.

- 📝 Investigate [data alignment](./code/ds/align.c)
  - kill [gaps](./code/ds/pack.c)

---

# Combining Control and Data in Machine-Level Programs

---

## Understanding Pointers

- `Pointers` reference data structures with an associated type (e.g., `int *ip`).
- A pointer stores the `address` of an object, with `NULL` indicating no reference.
- The `&` operator creates pointers, often using `lea` for address computation.
- Use `*` to access the value at a pointer's address.
- Array indexing is equivalent to pointer arithmetic.
- Casting changes pointer type but not its value
  - affecting scaling in pointer arithmetic.
- Pointers can reference `functions`, allowing dynamic calls and flexible program design.

- 📝 Investigate [pointers](./code/adv/pts.c)

---

## [Buffer overflow](https://seedsecuritylabs.org/Labs_20.04/Software/Buffer_Overflow_Setuid/)

- C lacks array bounds checking, causing potential stack corruption with `out-of-bounds` writes.
- **Buffer Overflow** happens when a string exceeds allocated buffer space, overwriting critical stack data like return addresses.
- Buffer overflows can lead to program crashes or security exploits, allowing attackers to execute malicious code.
- Functions like `gets`, `strcpy`, and `sprintf` are prone to buffer overflows, exposing systems to attacks.

- 📝 Investigate [buffer overflow](./code/adv/bf.c)

---

## Protection from buffer overflow

- **Buffer Overflow Protection**: Modern systems use various mechanisms to mitigate the risks of buffer overflow attacks, including stack randomization, stack corruption detection, and limiting executable code regions.
- **Stack Randomization (ASLR)**: Allocates random space on the stack to vary addresses between program executions, making it harder for attackers to predict memory locations. However, attackers can still exploit this with techniques like "NOP sleds."
- **Stack Corruption Detection**: A "canary" value is placed in the stack between the buffer and the stack state. If the canary is modified (indicating buffer overflow), the program aborts. This prevents state corruption caused by buffer overflows.
- **Limiting Executable Code Regions**: Restricts parts of memory (like the stack) from being executable to prevent attackers from injecting and executing malicious code. The NX (No-Execute) bit in modern processors helps enforce this protection efficiently.
- **Combining Techniques**: Randomization, stack protection, and limiting executable regions work together to significantly reduce vulnerability to buffer overflow attacks, though they cannot provide complete protection.

---

## Variable-size stack frames

- **Variable-Sized Stack Frames**: Functions with dynamic local storage (e.g., `alloca` or variable-sized arrays) require stack space allocation at runtime.
- **Frame Pointer**: The `%rbp` register helps manage stack frames by providing offsets for local variables and dynamic arrays.
- **Memory Allocation**: Space is allocated for variable arrays, ensuring the stack frame fits all variables.
- **Stack Setup/Cleanup**: The frame pointer is saved at function entry and restored at exit using `leave`.
- **Efficient Usage**: The frame pointer is used only for variable-sized stack frames, optimizing performance for fixed-size frames.

- 📝 Investigate [variable-size stack frame](./code/adv/vf.c)

---

# Floating-Point Code

- **Floating-Point Architecture**: Defines how floating-point values are stored, accessed, and manipulated using registers and instructions.
- **SIMD Extensions**: Intel/AMD processors use SIMD (MMX, SSE, AVX) for parallel processing of multiple data values.
- **Register Sizes**: MMX (64-bit), SSE (XMM, 128-bit), and AVX (YMM, 256-bit) registers hold integer or floating-point data.
- **Scalar Operations**: SSE2 and later support scalar floating-point operations using the lower bits of XMM/YMM registers.
- **AVX2**: Extends floating-point operations with 256-bit YMM registers, accessible via corresponding XMM registers.

---

## Floating-Point Movement and Conversion Operations  

- **Data Transfer**: `vmovss`, `vmovsd`, `vmovaps`, and `vmovapd` move floating-point values between memory and XMM registers.  
- **Scalar vs. Packed**: Scalar (`vmovss`, `vmovsd`) moves single values, while packed (`vmovaps`, `vmovapd`) moves full registers.  
- **Conversions**: `vcvttss2si`, `vcvttsd2si` truncate floats to integers; `vcvtsi2ss`, `vcvtsi2sd` convert integers to floats.  
- **Redundant Conversions**: GCC may use extra instructions (`vunpcklps`, `vcvtps2pd`) for float-double conversion instead of a single operation.  
- **Function Calls**: Floating-point return values use `%xmm0`; arguments in general-purpose registers require explicit conversion.

- 📝 Investigate [floating-point conversion](./code/adv/fcvt.c)

---

## Floating-Point Code in Procedures

- **Floating-Point Argument Passing**: Up to 8 floating-point arguments use `%xmm0-%xmm7`; extra ones go on the stack.  
- **Return Values**: Floating-point return values are stored in `%xmm0`.  
- **Register Saving**: All XMM registers are caller-saved; the callee may overwrite them.  
- **Mixed-Type Arguments**: Integers and pointers use general-purpose registers, while floating-point values use XMM registers.  
- **Example Mappings**:  
  - `double f1(int x, double y, long z);` → `%edi (x), %xmm0 (y), %rsi (z)`  
  - `double f2(double y, int x, long z);` → Same as `f1`  
  - `double f3(float x, double *y, long *z);` → `%xmm0 (x), %rdi (y), %rsi (z)`

---

## Floating-Point Arithmetic Instructions
- AVX2 provides scalar operations for single (`ss`) and double (`sd`) precision.  
- **Operands**:  
  - `S1` → XMM register or memory  
  - `S2, D` → XMM registers  
- **Common Operations**:  

| Instruction  | Operation            |
|-------------|-----------------------|
| `vaddss/vaddsd`  | `D = S2 + S1`    |
| `vsubss/vsubsd`  | `D = S2 - S1`    |
| `vmulss/vmulsd`  | `D = S2 * S1`    |
| `vdivss/vdivsd`  | `D = S2 / S1`    |
| `vmaxss/vmaxsd`  | `D = max(S2, S1)`|
| `vminss/vminsd`  | `D = min(S2, S1)`|
| `vsqrtss/vsqrtsd`| `D = √(S1)`   |

- **Usage**: Operates on **scalar** (single-value) floating-point data, not packed vectors.
- Cannot use immediate values as operands. 
  - Compiler must allocate and initialize storage for constants.

- 📝 Investigate [floating-point operations](./code/adv/fop.c)
  - [packed vector](./code/adv/pvec.c)

---

## Bitwise operations on XMM registers

- Used for manipulating floating-point values.
- **Operations**: 
  - `vxorps/xorpd` – Bitwise EXCLUSIVE-OR.
  - `vandps/andpd` – Bitwise AND.
- **Effect**: Affects all data in the XMM register, 
  - but for scalar values, only the low-order bytes are modified.

---

## Floating-Point Comparison Operations

- AVX2 provides two instructions for comparing floating-point values based on `S2-S1`:
  - `ucomiss S1, S2`: Compare single precision.
  - `ucomisd S1, S2`: Compare double precision.
  - `S2` must be in an XMM register, while `S1` can be in an XMM register or memory.
- **Operation Details**: 
  - Compares operands `S1` and `S2`, setting condition codes (`CF, ZF, PF`) to indicate the result.
  - Parity flag (`PF`) is set when `NaN` is involved.
- **Condition Codes**:
  - Unordered (NaN): CF=1, ZF=1, PF=1.
  - `S2 < S1`: CF=1, ZF=0, PF=0.
  - `S2 = S1`: CF=0, ZF=1, PF=0.
  - `S2 > S1`: CF=0, ZF=0, PF=0.

- 📝 Investigate [floating-point comparison](./code/adv/ftype.c)

---

## Floating-point operation vs. integer operation

- AVX2 floating-point operations use registers for values and argument passing, similar to integers.
- AVX2 involves more instructions due to handling mixed data types.
- It enables parallel operations on packed data for improved performance.
- Manual vector manipulation in C is currently the most reliable way to achieve parallelism.

---

# Debugging in Action

---

## [GDB commands](https://ftp.gnu.org/old-gnu/Manuals/gdb/html_chapter/gdb_toc.html)
- set assembly syntax flavor
  ```bash
  set disassembly-flavor at # at&t
  set disassembly-flavor intel #intel
  ```

| **Command**   | **Effect**  |
|------|-----|
| **Starting and stopping**   |     |
| `quit` | Exit GDB   |
| `run`  | Run your program (with command-line arguments)|
| `kill` | Stop your program |
| **Breakpoints**      |     |
| `break mul tstore`   | Set breakpoint at entry to function `multstore`      |
| `break 0x400540`     | Set breakpoint at address `0x400540`   |
| `delete 1`    | Delete breakpoint 1      |
| `delete`      | Delete all breakpoints   |
| **Execution**  |     |
| `stepi`| Execute one instruction  |
| `stepi 4`     | Execute four instructions|
| `nexti`| Like `stepi`, but proceed through function calls     |
| `continue`    | Resume execution  |
| `finish`      | Run until current function returns     |
| **Examining code**   |     |
| `disas`| Disassemble current function    |
| `disas mul tstore`   | Disassemble function `multstore`|
| `disas 0x400544`     | Disassemble function around address `0x400544`|
| `disas 0x400540, 0x40054d`  | Disassemble code within specified address range      |
| `print /x $rip`      | Print program counter in hex   |
| **Examining data**   |     |
| `print $rax`  | Print contents of `%rax` in decimal   |
| `print /x $rax`      | Print contents of `%rax` in hex|
| `print /t $rax`      | Print contents of `%rax` in binary    |
| `print 0x100` | Print decimal representation of `0x100`      |
| `print /x 555`| Print hex representation of `555`     |
| `print /x ($rsp+8)`  | Print contents of `%rsp` plus 8 in hex |
| `print *(long*)0x7fffffffe818`     | Print long integer at address `0x7fffffffe818`      |
| `print *(long*)($rsp+8)`    | Print long integer at address `%rsp + 8`     |
| `x/2g 0x7fffffffe818`| Examine two (8-byte) words starting at address `0x7fffffffe818`   |
| `x/20b multstore`    | Examine first 20 bytes of function `multstore`|
| **Useful information**      |     |
| `info frame`  | Information about current stack frame  |
| `info registers`     | Values of all the registers     |
| `help` | Get information about GDB|

---

## [WinDBG commands](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/getting-started-with-windows-debugging)

| **Command**       | **Effect** |
|---------|-----------|
| **Starting**      | |
| `.open <file>`    | Open a specified crash dump or executable|
| `!process`        | Display the current process information  |
| **Running and Stopping**    | |
| `q`     | Quit WinDbg|
| `g`     | Go (resume program execution) |
| `p`     | Step over one instruction      |
| `t`     | Trace one instruction (step into)        |
| `Ctrl+Break`      | Interrupt the program|
| **Breakpoints**   | |
| `bp <address>`    | Set a breakpoint at the specified address|
| `ba <size> <address>`       | Set a breakpoint at the address with specified size (e.g., byte, word) |
| `bl`    | List breakpoints     |
| `bd <breakpoint_number>`    | Disable a breakpoint by number |
| `be <breakpoint_number>`    | Enable a breakpoint by number  |
| `bc <breakpoint_number>`    | Clear a specific breakpoint    |
| `bc *`  | Clear all breakpoints|
| **Execution**     | |
| `step`  | Step through code (equivalent to `p` in GDB)       |
| `run`   | Run the program from the beginning or after a breakpoint     |
| `t`     | Trace into a function or instruction (step into)   |
| `s`     | Step over a function or instruction (step over)    |
| `c`     | Continue execution until the next breakpoint       |
| **Examining Code**| |
| `u <address>`     | Unassemble code at the given address     |
| `u <symbol>`      | Unassemble code starting at the symbol's address   |
| `r`     | Show the current register values|
| `l <address>`     | List memory content around the specified address    |
| **Examining Data**| |
| `? <expression>`  | Evaluate an expression (can be used to examine memory values)|
| `dd <address>`    | Dump data at the specified address in double words (4 bytes each)      |
| `db <address>`    | Dump data in bytes at the specified address        |
| `dc <address>`    | Dump data in characters at the specified address   |
| `dv <address>`    | Display values as a double-word at the specified address     |
| `ed <address> <value>`      | Edit memory at the given address with the specified value    |
| `d <address>`     | Dump memory starting at the given address|
| **Examining the Stack**     | |
| `k`     | Display the current stack trace |
| `!stack`| Display detailed stack information       |
| `~`     | List threads in the process and their call stacks  |
| `!analyze -v`     | Perform a verbose analysis of the current crash dump         |
| **Memory Management**       | |
| `!heap` | Display the heap information   |
| `!memory`         | Display memory regions and their attributes         |
| `!address`        | Display address space of a process       |
| **Useful Information**      | |
| `!list` | List loaded modules in the current process         |
| `!sym`  | Load or list symbols |
| `!process`        | Show process information (like threads, memory, etc.)        |
| `!dll`  | Display loaded DLLs for the process       |
| `!version`        | Display the version of WinDbg and the target platform        |
| `!load` | Load a specific extension DLL   |
| **Searching**     | |
| `find <address> <value>`    | Search memory for a specific value        |
| `findsym <symbol>`| Find the address of a symbol  |
| `!search`         | Search for specific memory patterns or symbols     |
| **Stack Analysis**| |
| `!thread`         | Show detailed information for a specific thread   |
| `!stack`| Display detailed call stack for the current thread |
| **Help and Debugging**      | |
| `!help` | Display help on a command or extension     |
| `.hh <command>`   | Get help on a specific command  |
| `.logopen`        | Start logging WinDbg output to a file    |
| `.logclose`       | Close the log file   |

## References
- [WinDbg](http://www.windbg.org/)
- [Intel® 64 and IA-32 Architectures Software Developer's Manual Combined Volumes](https://www.intel.com/content/www/us/en/content-details/782158/intel-64-and-ia-32-architectures-software-developer-s-manual-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html)
  - [x86-64 Instructions Set](https://linasm.sourceforge.net/docs/instructions/index.php)
  - [x86 and amd64 instruction reference](https://www.felixcloutier.com/x86/)
- *Memory alignment*
  - [Visual c++](https://learn.microsoft.com/en-us/cpp/cpp/alignment-cpp-declarations?view=msvc-170)