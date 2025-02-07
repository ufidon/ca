# **Machine Code Implementation of Control Structures in C/C++**
### **Objective:**
- Understand and implement fundamental control structures in C.
- Rewrite control structures using `goto` to simulate their machine-level implementation.
- Analyze compiled binaries using `objdump` to examine control flow.

## **Part 1: Implementing `goto`-Equivalent Control Structures**

Given code

```c
#include <stdio.h>

// Standard control structures
void ex_if_else(int x)
{
  if (x > 0)
    printf("x is positive\n");
  else
    printf("x is not positive\n");
}

void ex_conditional(int x)
{
  printf("x is %s\n", (x > 0) ? "positive" : "not positive");
}

void ex_switch(int x)
{
  switch (x)
  {
  case 1:
    printf("x is 1\n");
    break;
  case 2:
    printf("x is 2\n");
    break;
  default:
    printf("x is something else\n");
  }
}

void ex_do_while(int x)
{
  int i = 0;
  do
  {
    printf("i = %d\n", i);
    i++;
  } while (i < x);
}

void ex_while(int x)
{
  int i = 0;
  while (i < x)
  {
    printf("i = %d\n", i);
    i++;
  }
}

void ex_for(int x)
{
  for (int i = 0; i < x; i++)
  {
    printf("i = %d\n", i);
  }
}

int main()
{
  printf("=== C/C++ control structures ===\n");
  printf("--- 1. if...else ---\n");
  ex_if_else(1);

  printf("\n--- 2. conditional ---\n");
  ex_conditional(-1);

  printf("\n--- 3. switch ---\n");
  ex_switch(2);

  printf("\n--- 4. do...while  ---\n");
  ex_do_while(3);

  printf("\n--- 5. while ---\n");
  ex_while(3);

  printf("\n--- 6. for ---\n");
  ex_for(3);

  return 0;
}

```

### **Task 1: Convert the following functions into `goto`-based equivalents:**
1. `ex_if_else(int x)`
2. `ex_conditional(int x)`
3. `ex_switch(int x)`
4. `ex_do_while(int x)`
5. `ex_while(int x)`
6. `ex_for(int x)`

### **Instructions:**
- Modify each function to replace standard control structures with `goto`.
- Ensure functional equivalence with the original implementations.
- Compile and execute your implementation to verify its equivalence to the standard structures.

---

## **Part 2: Disassembling and Analyzing the Executable**
### **Task 2: Use `objdump` to analyze control flow in the compiled executable**
### **Instructions:**
1. **Compile the Program:**
   ```sh
   gcc -o lab04 lab04.c -g
   ```
2. **Disassemble the Executable:**
   ```sh
   objdump -d lab04 > disassembly.txt
   ```
3. **Analyze Key Instructions:**
   - Identify how control flow is managed using:
     - `jmp` (unconditional jump)
     - `jmpcc` (conditional jumps like `je`, `jne`, `jg`, `jl`, etc.)
     - `cmov` (conditional move instructions)
   - Compare the assembly output of standard control structures vs. their `goto` equivalents.

---

## **Deliverables:**
1. A modified version of `lab04.c` implementing `goto`-based control flow.
2. A lab report with 
   1. screenshots of the program output 
   2. `disassembly` with comments in `C` identifying key instructions used for control structures.