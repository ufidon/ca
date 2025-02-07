# Machine Code Representation and Access of C Aggregate Types

## Objective
- Understand the memory layout of C aggregate types
- manually compute element addresses
- verify calculations via a C program
- analyze the generated assembly code to identify the instructions used to access the members of c aggregate types

---

## Part I: Manual Address Calculation
Calculate memory addresses of elements/fields given a base address.

### Task 1: One-Dimensional Fixed-Size Array
```c
int arr[5] = {10, 20, 30, 40, 50};
```
- If `arr` starts at `0x1000`, compute the address of `arr[2]`, `arr[4]`.

### Task 2: Two-Dimensional Fixed-Size Array
```c
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};
```
- Given `matrix` starts at `0x2000`, compute the address of `matrix[2][1]`, `matrix[0][3]`.

### Task 3: Two-Level Jagged Array
```c
int* jagged[3];
int row1[] = {1, 2};        jagged[0] = row1;
int row2[] = {3, 4, 5};     jagged[1] = row2;
int row3[] = {6, 7, 8, 9};  jagged[2] = row3;
```
- Assuming `row2` starts at `0x3000`, compute the address of `jagged[1][2]`.

### Task 4: Structure with Mixed Field Sizes and Alignment Impact
```c
struct Data {
    char a[3];
    int b;
    short c;
    double d;
};
```
1. Given `struct Data data;` starts at `0x4000`, compute 
   - the addresses of:
     - `data.a[0]`, `data.a[1]`, `data.a[2]`
     - `data.b`
     - `data.c`
     - `data.d`
   - the size of the structure data

2. Field Reordering Experiment:
   - Find the `two` orderings of the fields in `struct Data`
     - ascending order of primitive data type sizes
     - descending order of primitive data type sizes
   - Compute the structure size for each ordering
   - Are the sizes of all structures with other field orderings in the range formed the ordered two? 
3. Draw the `memory layout` of the original structure, the ascending layout, and the descending layout.
   - label each field and the paddings


### Task 5: Array of Structures
```c
struct Data dataset[3] = {
    {{'A', 'B', 'C'}, 10, 20, 40.0},
    {{'D', 'E', 'F'}, 50, 60, 80.0},
    {{'G', 'H', 'I'}, 90, 100, 120.0}
};
```
- Given `dataset` starts at `0x5000`, compute the address of:
  - `dataset[1].b`
  - `dataset[2].c`
  - `dataset[0].d`

---

## Part II: Verification via C Program
Write a C program to 
- Print and verify computed addresses in Part I.
- Print real base addresses and real element/field addresses listed in Part I.

---

## (Extra credits) Part III: Assembly Code Analysis
Disassemble the compiled program of Part II and highlight instructions related to real address calculations.

### Steps
1. Compile with Debug Symbols:
   ```sh
   gcc -g -fno-stack-protector -fcf-protection=none  -o lab05 lab05.c 
   ```
2. Disassemble the Executable:
   ```sh
   objdump -d  lab05 > disassembly.txt
   ```
3. Analyze Assembly Code:
   - Identify memory access instructions (`mov`, `lea`, `add`, `imul`, etc.).
   - Highlight instructions computing offsets in:
     - One-dimensional arrays (`arr[i]`)
     - Two-dimensional arrays (`matrix[i][j]`)
     - Jagged arrays (`jagged[i][j]`)
     - Structures and arrays of structures (`dataset[i].a[j]`, `dataset[i].b`).

### Expected Findings
- Arrays: `lea` for address calculation, `mov` for memory access.
- Structures: Alignment may introduce padding.
- Jagged arrays: Indirect addressing via pointers.
