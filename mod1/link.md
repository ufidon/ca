# Building the Executable
CS:APP3e.ch07

---

## Overview

- **Linking** combines code and data into an executable, done at compile, load, or runtime, automated by linkers in modern systems.
- **Key Points**:
  - Enables **separate compilation** for large programs.
  - Resolves **linker errors** and avoids **programming errors**.
  - Clarifies **variable scoping** and system concepts like memory management.
  - Facilitates **dynamic linking** for efficient shared libraries and runtime updates.
- **Types of Linking**: Static (at compile time) and Dynamic (at load or runtime).
- 📝 compile and link [funs.c](./code/link/funs.c) and [main.c](./code/link/main.c)
  ```bash
  # 1️⃣ all in one step
  gcc -Og -o main main.c funs.c

  # 2️⃣ in separate steps
  # 1. compile
  gcc -c -o main.o main.c
  gcc -c -o funs.o funs.c
  # 2. link
  gcc -o main main.o funs.o
  ⚠️ ld -o main -e main -lc  -dynamic-linker /lib64/ld-linux-x86-64.so.2  funs.o main.o
  # 3. view linked libraries
  ldd main
  ```

---

## Tools for Manipulating Object Files 

| **Tool** | **Description**|
|------|-----|
| **ar**   | Creates static libraries and inserts, deletes, lists, and extracts members.|
| **strings**   | Lists all printable strings contained in an object file.    |
| **strip**| Deletes symbol table information from an object file. |
| **nm**   | Lists symbols defined in the symbol table of an object file.    |
| **size** | Lists names and sizes of the sections in an object file.   |
| **readelf**    | Displays the complete structure of an object file, including ELF header info.  |
| **objdump**   | Displays all information in an object file, including disassembling binary instructions in `.text`. |
| **ldd**   | Lists shared libraries that an executable needs at run time.    |

---

## Static linking

- **Static Linkers** generate executable files from relocatable object files.
- **Linker Tasks:**
  - **Symbol Resolution**: Associates references to symbols (functions, variables) with definitions.
  - **Relocation**: Modifies code and data sections to assign memory locations and update references.
- **Object Files** contain code, data, and structures to guide the linker.
- **Linker** concatenates blocks, assigns memory, and updates references, relying on the work done by compilers and assemblers.

- 📝 static link
  ```bash
  gcc -o main -static funs.o main.o
  ldd main
  ```

--- 

## Object files

- **Object file types**: 
  - **Relocatable**: Binary code/data for combination at compile time.
  - **Executable**: Ready for execution.
  - **Shared**: Dynamically linked at load or run time.
- **Generation**: 
  - Compilers/assemblers create relocatable/shared files; 
  - linkers create executable files.
- **File formats**: 
  - **a.out** (Unix), **PE** (Windows), **Mach-O** (Mac), **ELF** (Linux/Unix).
- **ELF structure**: 
  - Sections include `.text`, `.data`, `.bss`, `.symtab`, `.rel.text`, `.debug`, etc.

---

## Relocatable Object Files

- **ELF Header**: Describes word size, byte ordering, file type, machine type, and section header table info.
- **Code-related Sections**:
  - **.text**: Compiled machine code.
  - **.rodata**: Read-only data (e.g., format strings, jump tables).
- **Data-related Sections**:
  - **.data**: Initialized global and static variables.
  - **.bss**: Uninitialized global/static variables (placeholder, no disk space).
- **Relocation Sections**:
  - **.rel.text**: Relocation info for external function/global variable references in `.text`.
  - **.rel.data**: Relocation info for references to global variables in `.data`.
- **Symbol and Debugging Sections**:
  - **.symtab**: Symbol table for functions and global variables.
  - **.debug**: Debugging symbol table (includes local variables and original C source).
  - **.line**: Line number mapping between C source and machine code (with `-g`).
- **String Sections**:
  - **.strtab**: String table for symbols and section names.
- 📝 Investigate [elf format]((https://0xax.gitbooks.io/linux-insides/content/Theory/linux-theory-2.html))
  ```bash
  readelf -a  main
  ```

---

## Symbols and Symbol Tables

- **Symbol Table Types**:
  - **Global symbols**: Defined by the module and can be referenced by other modules.
  - **External symbols**: Referenced by the module but defined by other modules.
  - **Local symbols**: Defined and referenced within the module (e.g., static C functions/variables).
- **Symbol Table Entries**:
  - **Name**: Points to the symbol's name in the string table.
  - **Value**: The symbol's address (or offset for relocatable modules).
  - **Size**: The size of the object in bytes.
  - **Type**: Either data or function.
  - **Binding**: Local or global symbol.
  - **Section**: The section to which the symbol belongs, indexed in the section header table.
  - **Pseudosections**: 
    - Special sections like ABS (non-relocatable), UNDEF (undefined symbols), and COMMON (uninitialized global variables).
    - exist only in relocatable object files not executable object files

---

## Symbol Resolution

- **Symbol Resolution**: The linker matches references to definitions in object files.  
- **Local Symbols**: Always unique within a module.  
- **Global Symbols**: Assumed to exist elsewhere; linker errors if not found.  
- **Multiple Definitions**: Linker must resolve conflicts or report errors.  
- **Name Mangling**: C++ & Java encode function names to distinguish overloads.
  - `Foo::bar(int, long)` is encoded as `_Foo_bar_il`

---

## Resolve Duplicate Symbol Names

- **Symbol Types**: Global symbols can be **strong** (functions, initialized globals) or **weak** (uninitialized globals).  
- **Rule 1**: Multiple **strong** symbols with the same name are not allowed.  
- **Rule 2**: If both **strong** and **weak** exist, the **strong** symbol is used.  
- **Rule 3**: If only **weak** symbols exist, the linker can choose any.
- 🍎 Rule 1: strong-strong
  ```c
  // foo1.c
  // Rule 1: Multiple strong symbols with the same name are not allowed.
  int x = 11111; ➊
  int main() {   ➋
      return 0;
  }

  // bar1.c
  // Rule 1: This conflicts with foo1.c because both define a strong symbol 'main'.
  int x = 11111; ➊
  int main() {   ➋
      return 0;
  }
  ```
- 🍎 Rule 2: strong-weak
  ```c
  // foo3.c
  #include <stdio.h>

  void f(void);

  // Rule 2: 'x' and `y` are strong symbols because they are initialized.
  int y = 15212; ➊
  int x = 15213; ➋

  int main() {
      printf("x = %d\n", x);
      return 0;
  }

  // bar3.c
  // Rule 2: 'x' and `y` are weak symbols because they are uninitialized.
  // The linker will resolve to the strong symbol in foo3.c. 
  double y; ➊
  int x; ➋

  void f() {
      x = 15212;
  }
  ```
- 🍎 Rule 3: weak-weak
  ```c
  // foo4.c
  #include <stdio.h>

  void f(void);

  // Rule 3: 'x' is a weak symbol (uninitialized global).
  int x;

  int main() {
      x = 15213;
      f();
      printf("x = %d\n", x);
      return 0;
  }

  // bar4.c
  // Rule 3: 'x' is also a weak symbol.
  // The linker will pick one of the weak symbols.
  int x;

  void f() {
      x = 15212;
  }
  ```

---

## Linking with Static Libraries 

- **Static libraries** package related object modules into a single file
  - allow the linker to copy only the needed modules  
  - simplify program linking
  - e.g.: libc.a (C standard functions) and libm.a (math functions) are provided as static libraries.  
- **Creating a static library** of [vector](./code/link/vector.h) [addition](./code/link/addvec.c) and [multiplication](./code/link/multvec.c)
  ```bash
  gcc -c addvec.c multvec.c  #  Compile object files
  ar rcs libvector.a addvec.o multvec.o # Archive them
  ```
- **Using a static library** in [main](./code/link/vecmain.c)
  ```bash
  gcc -c vecmain.c  # Compile main file: 
  gcc -static -o prog2 vecmain.o ./libvector.a # Link with library: 
  gcc -o prog2 vecmain.o -L. -lvector # Or use shorthand
  ```
- **Linking process:** The linker copies only referenced object files into the final executable.  
- **Static vs. dynamic linking:** 
  - Static linking embeds library code into executables at compile time
  - dynamic linking loads shared libraries at runtime.

---

## Resolve References Using Static Libraries

- The linker scans object files and archives **left to right** as they appear on the command line maintaining three sets: 
  - **E** (object files to merge), **U** (unresolved symbols), and **D** (defined symbols).  
  - Each object file is added to **E**, and symbols are updated.  
  - Each archive resolves **U** with symbols from its members. 
    - Unused members are discarded.  
  - The linker throws an error if **U** is not empty after scanning all files  
- **Library order matters**
  - linking will fail if a library appears before an object file that needs it  
- General rule: **Place libraries at the end** of the command line.  
  - If libraries depend on each other, order them so that referenced symbols appear after they are used.  
  - If necessary, **repeat libraries** on the command line
    - e.g., `gcc foo.c libx.a liby.a libx.a`  
- Alternatively, **combine dependent libraries** into a single archive.

---

# Relocation
- **Symbol resolution** associates each symbol `reference` with a symbol `definition`.  
- **Relocation** involves two main steps:  
  1. **Relocating sections and symbol definitions**:  
     - Merges sections of the same type (e.g., `.data`) from input modules into a single section.  
     - Assigns run-time memory addresses to all sections and symbols.  
  2. **Relocating symbol references within sections**:  
     - Modifies symbol references to point to correct run-time addresses.  
     - The linker uses **relocation entries** in object modules to perform this modification.

---

## Relocation Entries

- The assembler generates `relocation entries` when it encounters `references with unknown locations`
  - such as external functions or global variables.  
- **Relocation entries** are placed in `.rel.text` (for code) or `.rel.data` (for data).  
- Each **relocation entry** has an offset, symbol, type, and addend to specify how a reference should be relocated.  
  - **R_X86_64_PC32**: Relocates a `32-bit PC-relative address`, using an offset from the program counter.  
  - **R_X86_64_32**: Relocates a `32-bit absolute address`, using the value directly.  
  - These types are used in the **x86-64 small code model**, assuming the code and data are under 2GB.
    - Programs larger than 2 GB can be compiled using
      - `-mcmodel=medium` for medium code model
      - `-mcmodel=large` for large code model

---

## Relocating Symbol References

- **Relocation process** involves `updating references` in the code to `reflect their run-time memory addresses`.  
- **Relocation steps**:  
  1. **Relocating sections and symbol definitions**: Merging sections and assigning memory addresses.  
  2. **Relocating symbol references**: Modifying references in code and data sections to point to correct addresses using relocation entries.  
     - **PC-relative relocation**: Modifies references to a function by calculating an offset from the current instruction.  
     - **Absolute relocation**: Directly modifies references to global variables using absolute memory addresses.  
- **Relocation output**: The linker generates relocated code and data sections that are ready for execution.

---

## Executable Object Files

- **ELF executable structure**: Merges object files into a single binary for execution.
- **ELF header**: Describes the file format, including the entry point and section details.
- **Sections**: `.text`, `.rodata`, `.data`, `.bss`, `.symtab`, `.debug`, `.line`, `.strtab`.
  - **Code and data sections**: Relocated to memory addresses.
  - **Symbol and debug sections**: Not loaded into memory.
- **Program header table**: Describes memory segments with information like offset, virtual and physical addresses, size, and permissions.
  - **Code segment**: Read/execute permissions, starting at `0x400000`.
  - **Data segment**: Read/write permissions, starting at `0x600df8`.
- **Segment alignment**: Ensures efficient memory mapping by aligning sections in the object file with memory segments.
- **Initialization**: The `.init` section defines initialization code (e.g., `_init` function).

---

## Loading Executable Object Files

- **Running an executable** invokes the loader to 
  - copy the program's code and data from disk into memory 
  - jump to the entry point
- **[Run-time memory layout](https://gist.github.com/CMCDragonkai/10ab53654b2aa6ce55c11cfc5b2432a4)**:
  - **Code segment**: Starts at `0x400000`.
  - **Data segment**: Follows the code segment.
  - **User stack**: Grows downward from the highest user address.
  - **Heap**: Grows upward with `malloc`.
  - **Shared modules**: Reserved for dynamic libraries.
  - **Kernel memory**: Occupies the region above the stack.
- **Address-space layout randomization (ASLR)**: Randomizes addresses of stack, heap, and shared libraries at runtime.
- **Memory image**: The loader creates a memory image based on the program header table.
- **Startup**: The loader calls `_start` (from `crt1.o`), which then calls `__libc_start_main` to set up the environment and execute `main`.

---

## Dynamic Linking with Shared Libraries

- **Static library issues**: Static libraries require explicit relinking to update and can waste memory by duplicating code in each process.
- **Shared libraries**: Loaded at run time or load time, shared libraries use dynamic linking, which is managed by a dynamic linker.
- **Shared library advantages**:
  - Single `.so` file for a library shared by multiple programs.
  - The code and data of a shared library are loaded into memory once and shared across processes.
- **Dynamic linking process**:
  1. **Create shared library**: Use flags like `-shared` and `-fpie` to generate a shared object (`.so`).
  2. **Link with shared library**: Link the executable with `.so` at run time, not embedding the library into the executable.
  3. **Loader and dynamic linker**: Loader invokes the dynamic linker, which resolves symbol references to libraries at runtime.
- **Result**: Dynamic linker loads libraries, relocates sections, and resolves references, ensuring shared libraries are available to the program without duplicating them in memory.

---

## Loading and Linking Shared Libraries from Applications

- **Dynamic Linking** allows applications to load and link shared libraries at runtime, enabling software updates without relinking.
- **Benefits**:
  - Reduces memory usage by sharing a single copy of the library's code across processes.
  - Allows for updates to libraries without needing to recompile the application.
  - Used in scenarios like Web servers generating dynamic content and distributing software updates.
- **Linux Interface**: 
  - `dlopen()`: Loads a shared library at runtime.
  - `dlsym()`: Resolves a symbol (function) from a loaded library.
  - `dlclose()`: Unloads a shared library when no longer needed.
  - `dlerror()`: Returns the last error message from dynamic linking operations.
- **Compilation**: Use `-rdynamic` to enable symbol exporting and `-ldl` to link with the dynamic loading library.
- 📝 link `libvector.so` dynamically for [dlvec.c](./code/link/dlvec.c)
  ```bash
  # 1. create shared library `libvector.so`
  gcc -shared -fpic -o libvector.so addvec.c multvec.c

  # 2. link the program with libdl for dynamic linking
  gcc -rdynamic -o prog3 dlvec.c -ldl
  ```

---

## Position-Independent Code (PIC)

- **PIC** allows a single copy of a shared library’s code to be loaded anywhere in memory without modifications
  - generated using the `-fpic` flag in GCC.
  - **PIC Data References**: Uses the `Global Offset Table (GOT)` to store addresses of global variables.
  - **PIC Function Calls**: Functions in shared libraries are resolved at runtime using a technique called lazy binding.
- **Global Offset Table (GOT)**:  
  - Stores addresses of globally referenced objects (functions/variables).
  - Resolved by the dynamic linker at runtime.
- **Procedure Linkage Table (PLT)**:  
  - An array of code entries that helps in resolving function addresses at runtime.
  - First calls resolve the address of functions, subsequent calls directly jump to the resolved address.
- **Lazy Binding**:  
  - Function addresses are resolved when the function is first called, reducing unnecessary relocations.
  - Uses a combination of GOT and PLT to defer resolution until required.

---

# Library lnterpositioning (hooking)

- Allows `intercepting calls` to shared library functions and replacing or modifying their behavior.
- Can trace function calls, validate inputs/outputs, or replace implementations.
- **Types of hooking**:  
  1. **Compile-Time hooking**:  
     - Achieved via the C preprocessor.  
     - Wrapper functions replace target function calls, `adding custom logic` before invoking the original function.
  2. **Link-Time hooking**:  
     - Achieved by using the `--wrap` flag during linking.  
     - The linker resolves references to a function to its wrapper (e.g., `--wrap,malloc`).
  3. **Run-Time hooking**:  
     - Uses the `LD_PRELOAD` environment variable to `load custom shared libraries` before others at run time.  
     - Interposes on library functions (like `malloc` and `free`) in any executable.
- 📝 library [hooking](./code/link/)
  ```bash
  # 1️⃣ compile-time hooking
  gcc -DCOMPILETIME -o mysleep mysleep.c mylib.c
  ./mysleep

  # 2️⃣ link-time hooking
  gcc -DLINKTIME -c mylib.c mysleep.c
  gcc -Wl,--wrap,sleep -o mysleep2 mysleep.o mylib.o
  ./mysleep

  # 3️⃣ run-time hooking
  gcc -Wall -DRUNTIME -shared -fpic -o mylib.so mylib.c -ldl
  gcc -o mysleep mysleep.c
  LD_PRELOAD="./mylib.so" ./mysleep  
  ```

---

# Reference
- [Linux Foundation: Referenced Specifications](https://refspecs.linuxfoundation.org/)
- [Linux inside](https://0xax.gitbooks.io/linux-insides/content/)
  - [中文版](https://github.com/hust-open-atom-club/linux-insides-zh)
- [ELF64 hello world](https://tuket.github.io/notes/asm/elf64_hello_world/)
- [SEED labs](https://www.handsonsecurity.net)