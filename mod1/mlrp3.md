# Machine-Level Representation of Programs
CS:APP3e.ch03

Procedures
---


## What happen when one function call another?
- caller calls callee
  - pass control and data
  - allocate and free memory

---

## Investigate memory layout

| **Segment** | **Windows**    | **Windows Tools**  | **Linux**| **Linux Tools**|
|---|------------|--|-------------|-------------|
| **Code (Text)**  | `.text` in EXE | VMMap, Process Explorer, WinDbg | `.text` in ELF | `/proc/<PID>/maps`, `pmap`, `gdb` |
| **Heap**  | Managed by `VirtualAlloc`  | VMMap, Process Explorer, WinDbg | Managed by `brk` & `mmap`  | `/proc/<PID>/maps`, `pmap`, `gdb` |
| **Stack** | Grows downward | VMMap, Process Explorer, WinDbg | Grows downward | `/proc/<PID>/maps`, `pmap`, `gdb` |
| **Shared Libs** | `.dll` files in user space | VMMap, Process Explorer, WinDbg | `.so` files in `/lib`| `/proc/<PID>/maps`, `ldd`, `gdb` |
| **System-Wide Memory** | `Task Manager`, `GetProcessMemoryInfo()` | Task Manager, PerfMon, VMMap | `/proc/meminfo` | `vmstat`, `top`, `htop` |
| **Process Memory Query** | `VirtualQueryEx()` API | WinDbg (`!address`), Process Explorer, VMMap | `/proc/<PID>/maps` | `pmap`, `gdb` (`info proc mappings`) |

---

## Runtime stack
- x86-64 procedures allocate only necessary stack frame portions, often omitting them when arguments fit in registers.  
- Functions without local stack variables or function calls (leaf procedures) may not use a stack frame at all.
- Live Stack Viewing in WinDbg & GDB

| **Action** | **Windows (WinDbg)**        | **Linux (GDB)**|
|------|-------|----|
| **Attach to Process**  | `windbg -p <PID>`        | `gdb -p <PID>`|
| **View Call Stack**  | `k, kp, kf, kn`      | `bt, bt full` |
| **View Stack Memory**  | `dps rsp L10`    | `x/10gx $rsp` |
| **Break at Function** | `bp factorial`  | `break factorial`      |
| **Continue Execution** | `g`   | `continue`    |
| **Step Into Function** | `t` (trace)    | `stepi` (step instruction)      |
| **View All Threads** | `~* k`  | `info threads`|

- 📝 Investigate [sum.c](./code/proc/sum.c)

---

## Control transfer
- Calling function Q `saves the return address` on the stack using `call Q`.  
- The return address is the instruction after the `call` in function P.  
- The `ret` instruction `restores the saved address`, resuming execution in P.

| **Instruction** | **Description** |
|---------------|-------------|
| `call Label`  | Direct procedure call  |
| `call *Operand` | Indirect procedure call   |
| `ret`        | Return from call  |

---

## Data transfer
- x86-64 passes up to six arguments via registers, based on data size.
  - Smaller arguments use parts of 64-bit registers (e.g., `%edi` for 32-bit).
- Arguments beyond six are passed on the stack, allocated in the caller's stack frame.
  - Stack arguments are rounded to multiples of eight, and called functions access them via registers or stack.

| **size(bits)\argument#** | **1**| **2** | **3**| **4**| **5** | **6**|
|---------|------|-------|------|------|------|------|
| **64**  | %rdi | %rsi  | %rdx | %rcx | %r8  | %r9  |
| **32**  | %edi | %esi  | %edx | %ecx | %r8d | %r9d |
| **16**  | %di  | %si   | %dx  | %ex  | %r8w | %r9w |
| **8**   | %dil | %sil  | %dl  | %cl  | %r8b | %r9b |

- 📝 Investigate [pa.c](./code/proc/pa.c)

---

## Local Storage on the Stack
- Local data is stored in memory when there are not enough registers or when using the address operator `&`.
- Arrays and structures also require memory allocation for correct access.
- Space for local variables is allocated by decrementing the stack pointer.

- 📝 Investigate [local.c](./code/proc/local.c)

---

## Local Storage in Registers

- **Program registers** are `shared` by all procedures, 
  - the caller must ensure that registers used by the callee are `preserved`.
- **Callee-saved registers**: `%rbx`, `%rbp`, and `%r12-%r15` must be preserved by the callee; 
  - they are saved by either not modifying or pushing their values onto the stack.
- **Caller-saved registers**: All other registers (except `%rsp`) can be modified by the callee
  - the caller must save their values if needed.

- 📝 Investigate [reg.c](./code/proc/reg.c)

---

## System V AMD64 ABI vs. Windows x64 calling convention

| Feature| System V AMD64 ABI  | Windows x64 Calling Convention|
|------|------|---------------|
| **Argument Passing** | First six integer or pointer arguments in registers (`rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`).  Remaining arguments on the stack.  Floating-point arguments in XMM registers (`xmm0`-`xmm7`). | First four integer or pointer arguments in registers (`rcx`, `rdx`, `r8`, `r9`). Remaining arguments on the stack. Floating-point arguments in XMM registers (`xmm0`-`xmm3`). |
| **Stack Cleanup**   | Caller cleans up the stack.| Caller cleans up the stack.|
| **Return Value**| Integer/pointer: `rax`. Floating-point: `xmm0`.| Integer/pointer: `rax`. Floating-point: `xmm0`.|
| **Register Preservation** | Callee-saved registers: `rbp`, `rbx`, `r12`-`r15`. Caller-saved registers: others. | Callee-saved registers: `rbp`, `rdi`, `rsi`, `rsp`, `rbx`, `r10`-`r15`. Caller-saved registers: others. |
| **Red Zone**| 128 bytes below `rsp` are a red zone (not to be used by the function). | No red zone specified. However, stack probes are used for large stack allocations. |
| **Shadow Space**| 32 bytes of shadow space on the stack below the return address for storing register arguments if needed. | 32 bytes of shadow space on the stack below the return address for storing register arguments if needed. |
| **Frame Pointer (RBP)** | Usage is optional (often omitted for optimization).  If used, it follows standard conventions. | Usage is optional (often omitted for optimization). If used, it follows standard conventions. |
| **Name Mangling**   | Name mangling is implementation-defined but typically follows a standard scheme (e.g., for C++). | Name mangling is used, especially for C++ (decorated names). |
| **Exception Handling** | Defined by the Itanium C++ ABI.   | Structured Exception Handling (SEH).|
| **Calling Convention Name** | Often referred to as the System V ABI or just the x64 ABI. | Sometimes called the Microsoft x64 calling convention.|

---


## References
- [Applied Reverse Engineering: The Stack](https://revers.engineering/applied-re-the-stack/)
- [Searchable Linux Syscall Table](https://filippo.io/linux-syscall-table/)
- [x64 calling convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170)
- [Windows memory management](https://learn.microsoft.com/en-us/windows/win32/memory/about-memory-management)