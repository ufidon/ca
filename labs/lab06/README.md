# Implementing Bubble Sort in Y86-64 Assembly

## Objective
The goal of this lab is to gain hands-on experience writing and testing assembly code by implementing the Bubble Sort algorithm in Y86-64. You will first implement and analyze Bubble Sort in C using both array indexing and pointer-based approaches before translating the logic into Y86-64 assembly.

This lab will strengthen your understanding of assembly programming, memory manipulation, and performance optimization.

⚠️ **Warning:** The size of C `long` is 8 bytes on Linux 64 but 4 bytes on Windows 64, so please use `long long` in your C program since its size is 8 bytes on both OSes.

👉 **Hint:** You may refer to this `selection sort` [pointer version](./ref/sel.c) and its [Y86-64 assembly](./ref/sel.ys).

---

## **Tasks**

### **Task A: Implement Bubble Sort (Pointer Referencing) in C**
1. Write a C function `bubble_a` that sorts an array using pointer referencing.
   - 💡 Convert the array indexing version below into pointer referencing.
2. Test the function with different inputs.
3. Verify the array's content in memory before and after sorting.

**Array Indexing Implementation:**
```c
// A simple bubble sort function using array indexing
void bubble_a(long long array[], long long size) {
    long long i, last,t;
    for (last = size - 1; last > 0; last--) {
        for (i = 0; i < last; i++) {
            if (array[i + 1] < array[i]) {
                // Swap adjacent elements
                t = array[i + 1];
                array[i + 1] = array[i];
                array[i] = t;
            }
        }
    }
}
```

### **Task B: Implement and Test `bubble_a` in Y86-64 Assembly**
1. Convert the C pointer implementation of `bubble_a` to Y86-64 assembly.
   - 💡 Write Y86-64 code with reference to the x86-64 assembly output of compiling the C version.
   - `gcc -g -fno-stack-protector -fcf-protection=none  -o lab06 lab06.c`
   - `objdump -d lab06`
2. Use a Y86-64 simulator to test the implementation.
3. Check the array content in memory before and after sorting.


---

### **Task C: Optimize Bubble Sort (`bubble_b`)**
1. Improve `bubble_a` to stop sorting early when the array is already sorted.
2. Implement `bubble_b` using pointer referencing based on array indexing below.
3. Test the function and verify sorting correctness.
4. Check the array content in memory before and after sorting.

**Array Indexing Implementation:**
```c
void bubble_b(long long array[], long long size) {
    long long needNextPass = 1;  // 1 for true, 0 for false
    long long i,k,temp;
    for (k = 1; k < size && needNextPass; k++) {
        needNextPass = 0;
        for (i = 0; i < size - k; i++) {
            if (array[i] > array[i + 1]) {
                // Swap adjacent elements
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                needNextPass = 1;
            }
        }
    }
}
```

### **Task D: Implement and Test `bubble_b` in Y86-64 Assembly**
1. Convert `bubble_b` to Y86-64 assembly.
2. Test the program using the Y86-64 simulator.
3. Check the array content in memory before and after sorting.

---

### **Task E: Analyze Function Size and Performance**
1. Measure the function sizes of `bubble_a` and `bubble_b` in Y86-64.
2. Discuss the trade-offs between code size and performance for both versions.
3. Analyze how the early stopping optimization affects performance.

---

## **Deliverables**
- C implementations of `bubble_a` and `bubble_b` using pointer referencing.
- Y86-64 implementations of `bubble_a` and `bubble_b`.
- Observations on function size and performance differences.
- `Screenshots or logs` showing array contents before and after sorting in Y86-64 simulation.

---

## **Assessment Criteria**
| Criteria | Description |
|----------|-------------|
| **Correctness** | Sorting functions must correctly sort input arrays. |
| **Assembly Implementation** | Properly converted Y86-64 assembly with correct logic. |
| **Performance Analysis** | Function sizes are measured, and performance trade-offs are discussed. |
| **Testing** | Demonstrated testing and validation using memory inspections with `screenshots`. |