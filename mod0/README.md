# Computer Architecture
CS:APP3e.ch01

![displaywrite](./imgs/layers.png)
---

## Overview
- Course theme: Balancing abstraction with real-world understanding
- Key realities of computer systems
- Role of the course in the CS curriculum

---

## Course Theme: Abstraction Is Good, But Reality Matters
![abstraction](./imgs/abstractions-os.png)

- CS courses emphasize abstraction e.g., 
  - abstract data types, 
  - asymptotic analysis of algorithms
- Abstraction has limits, especially when debugging or optimizing
- Understanding implementation details improves:
  - Programming effectiveness
  - Bug detection and elimination
  - Performance tuning
- Prepares you for advanced systems courses e.g., 
  - OS, Compilers, Networks, Embedded Systems

---

## Great Reality ❶: Ints Are Not Integers, Floats Are Not Reals
- **Example 1:** Is x² ≥ 0?
  - Floats: Yes
  - Integers:
    - 40000 * 40000 → 1600000000
    - 50000 * 50000 → Overflow
- **Example 2:** Is (x + y) + z = x + (y + z)?
  - Integers: Yes
  - Floats:
    - (1e20 + -1e20) + 3.14 → 3.14
    - 1e20 + (-1e20 + 3.14) → ?
- 📝 Practice: try various value limits in [ov.c](./code/ov.c)

---

## Computer Arithmetic
- Arithmetic operations are predictable but not always intuitive
- Mathematical properties don't fully apply due to finite representation:
  - **Integers**: Commutative, associative, distributive
  - **Floats**: Monotonic but subject to rounding errors
- Key takeaway: Understand context to avoid errors in programming and compiling

---

## Great Reality ❷: You Need to Understand Assembly
![compilation](./imgs/compilation.png)

- You may not write assembly, but understanding it is essential for:
  - Debugging
  - Understanding compiler optimizations and inefficiencies
  - Performance tuning
  - Writing system software (OS, compilers)
  - Security (malware analysis, reverse engineering)
- Assembly is critical for low-level programming and systems understanding
- 📝 Go through the compilation procedure
  ```bash
  # ⓐ By gcc only
  # 1. Preprocessing: ov.c → ov.i
  gcc -E ov.c -o ov.i # or cpp 
  # 2. Compilation: ov.i → ov.s
  gcc -S ov.i -o ov.s # or gcc -S ov.c -o ov.s
  # 3. Assembly: ov.s → ov.o
  gcc -c ov.s -o ov.o # or gcc -c ov.c -o ov.o
  # 4. Linking: ov.o → ov
  gcc ov.o -o ov      # or gcc ov.c -o ov
  # 5. gcc automates all these procedures
  gcc ov.c -o ov

  # ⓑ Extra work is needed for separate tools
  # 1. Preprocessing: ov.c -> ov.i
  cpp ov.c > ov.i
  # 2. Compilation: ov.i -> ov.s
  gcc -S -o ov.s ov.i 
  # 3. Assembly: ov.s -> ov.o
  as -o ov.o ov.s
  # 4. Linking: ov.o -> ov
  # you can find the dynamic linker by: ldd /bin/ls
  ld -o ov ov.o -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
  ```
- You need to manually add the following code to ov.s for ⓑ 3
  ```assembly
  .section .text
  .globl _start
  _start:
      call main
      movl $0, %edi  # Return 0 (exit code)
      call exit
  ```

---

## Great Reality ❸: Memory Matters
![memory](./imgs/memhier.png)

- **Memory Is Limited and Needs Management**
  - Applications often constrained by memory
- **Bugs Are Difficult to Trace**
  - Memory bugs can manifest far from the source
- **Performance Is Affected by Memory Access**
  - Cache and virtual memory significantly impact speed
  - Optimizing for memory architecture boosts performance

---

## Memory Bug Example
```c
typedef struct {
    int a[2];
    double d;
} struct_t;

double fun(int i) {
    volatile struct_t s;
    s.d = 3.14;
    s.a[i] = 1073741824;  // Potential out-of-bounds access
    return s.d;
}
```
- Different results depending on system and compiler:
  - fun(0) → 3.14
  - fun(2) → 3.139...
  - fun(6) → Segmentation fault
- 📝 Practice: trigger segmentation fault from [fun.c](./code/fun.c)
  - run the code multiple times with parameters 0-7, do you get the same result every time?

---

## Memory Referencing Errors and Solutions

![runtime image](./imgs/rtimage.png)

- **Common Issues**
  - Out-of-bounds access, invalid pointers, malloc/free misuse
- **Consequences**
  - Unpredictable bugs, delayed effects, corrupted data
- **Solutions**
  - Use safe languages (Java, Python, Rust) or detection tools (Valgrind)
  - Understand and anticipate memory interactions

---

## Great Reality ❹: Performance Involves More than Asymptotic Complexity
- Constant factors and implementation details matter
- Performance varies significantly (10x differences) based on code structure
- Optimization requires:
  - Algorithmic improvements
  - Efficient data handling
  - Careful loop and procedure design
- System knowledge is essential for effective optimization

---

## Memory System Performance Example
```c
void copyji(int src[2048][2048], int dst[2048][2048]) {
    for (int j = 0; j < 2048; j++)
        for (int i = 0; i < 2048; i++)
            dst[i][j] = src[i][j];
}

void copyij(int src[2048][2048], int dst[2048][2048]) {
    for (int i = 0; i < 2048; i++)
        for (int j = 0; j < 2048; j++)
            dst[i][j] = src[i][j];
}
```
- copyij: 4.3ms | copyji: 81.8ms (Intel i7)
- Cache efficiency explains the performance gap
  - ![i7cache](./imgs/corei7caches.png)
- 📝 Practice: find the code performance of [perf.c](./code/perf.c) specific to your system

---

## Great Reality ❺: I/O and Networking Matter
![io](./imgs/nethost.png)

- Performance and reliability depend on data movement
- Systems must handle:
  - I/O bottlenecks
  - Network reliability and concurrency
  - Platform differences and performance tuning

---

## Course Role in [CS Curriculum](https://catalog.floridapoly.edu/preview_program.php?catoid=35&poid=1567)
- Foundation for systems courses (OS, Networking, Compilers)
- Clarifies core principles underlying computer systems
- Prepares students for building real-world software

---

## Textbooks
- [Computer Systems: A Programmer's Perspective, 3e](http://csapp.cs.cmu.edu/)
- [The C Programming Language, 2e](https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/books/C_Book_2nd.pdf)
- [x86-64 Assembly Language Programming with Ubuntu](https://open.umn.edu/opentextbooks/textbooks/733)

---

## Computer Architecture Components
- Programs and Data
  - Bit operations, assembly, data representation
- Memory Hierarchy
  - Caching, memory technology, locality
- Exceptional Control Flow
  - Processes, signals, Unix control flow
- Virtual Memory
  - Address translation, memory allocation
- Networking and Concurrency
  - Threads, synchronization, web proxy development

---

## Speedup
- A task can be divided into several subtasks running in sequence.
  - ![context switch](./imgs/switch.png)
  - Improving one subtask boosts overall performance based on how critical that subtask is and how much it improves.
- **Amdahl's Law** explains the improvement:   
  - If a fraction $a$ of the task's time is improved by a factor $k$, the new execution time is:  
    $\displaystyle T_{\text{new}} = (1 - a) T_{\text{old}} + \frac{a T_{\text{old}}}{k}$  
  - The overall speedup $S$ is calculated by:  
    $\displaystyle S = \frac{T_{\text{old}}}{T_{\text{new}}} = \frac{1}{(1-a) + \frac{a}{k}}$  
  - In the extreme case where $k = \infty$ (part of the system is infinitely fast), the maximum speedup is:  
    $\displaystyle S_{\infty} = \frac{1}{1-a}$  

---

## 📝 Exercises
1. A computer system spends 70% of its execution time on a specific task. You plan to improve this task by a factor of 5.
  - ➀ Calculate the overall speedup of the system using Amdahl’s Law. 
  - ➁ If the task is improved by a factor of 10 instead of 5, calculate the new overall speedup.
  - ➂ If the improvement factor can be extremely large (i.e. k→∞), calculate the maximum possible speedup for the system.
2. A system experiences an overall speedup of $S = 2.5$ after optimizing 50% of its runtime. 
  - Calculate the improvement factor $k$ for the optimized portion of the system using Amdahl’s Law.

---

## Concurrency and Parallelism for Speedup
- **Concurrency** refers to systems with multiple simultaneous activities
  - **parallelism** uses concurrency to enhance system speed.  
- **Thread-level concurrency** allows multiple programs or threads to execute at the same time,
  - supporting multitasking within a single processor or across multiprocessor systems.  
- **Multi-core processors** integrate multiple CPU cores on one chip, 
  - enabling parallel execution and shared memory access,
  - ![multiprocessor](./imgs/processors.png)
  - while **hyperthreading** lets a single core handle multiple threads by switching at each clock cycle.  
  - **Multiprocessing** improves performance by running tasks concurrently 
    - accelerating single programs if they are designed with multiple threads.  
- **Instruction-level parallelism** lets modern processors execute multiple instructions per clock cycle, 
  - using `pipelining` and `superscalar` designs to enhance efficiency.  
  - **Superscalar processors** sustain execution rates faster than one instruction per cycle by `processing numerous instructions concurrently` through clever hardware designs.  
  - **Single-instruction, multiple-data (SIMD) parallelism** allows `one instruction to perform operations on multiple data points` simultaneously, 
    - boosting performance in applications like image and video processing.

---

## 📝 Investigate Your Computer
- with [cpu-z](https://www.cpuid.com/softwares/cpu-z.html)