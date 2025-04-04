# Optimizing program performance
CS:APP3e.ch05


---

# Overview

- **Correctness & Clarity First**  
   - A program must work correctly; speed is irrelevant if results are wrong.  
   - Write clear, maintainable code for readability and collaboration.  
- **Performance Optimization When Needed**  
   - Speed is critical for real-time tasks (e.g., video processing) or long computations.  
   - Balance efficiency with maintainability—optimize only where necessary.  
- **Compiler-Aware Coding & Algorithm Selection**  
   - Choose efficient algorithms and data structures.  
   - Write compiler-friendly code to maximize optimization (avoid blockers like pointer arithmetic).  
- **Hardware Understanding & Low-Level Tuning**  
   - Know processor behavior (parallelism, timing) to guide optimizations.  
   - Eliminate redundant operations (calls, memory accesses) and leverage instruction-level parallelism.  
- **Iterative Optimization & Tool Use**  
   - Use profilers to identify bottlenecks and focus efforts.  
   - Experiment with changes, review assembly code, and refine for efficiency without sacrificing portability.

---

# Capabilities and Limitations of Optimizing Compilers

- **Compiler Optimization Levels and Trade-offs**
   - Offers multiple optimization levels (`-Og` for debugging, `-O1`/`-O2`/`-O3` for increasing performance)
   - Higher optimizations improve speed but may reduce debuggability and increase code size
   - GCC takes conservative approach, requiring programmer assistance for best results
- **Memory Aliasing Limitations**
   - Compilers must assume `pointers may alias (reference same memory)`
   - Prevents optimizations like combining operations
   - Forces conservative memory access patterns with redundant loads/stores
- **Function Call Constraints**
   - Compilers preserve all function calls due to potential side effects
   - Prevents optimizations like call merging (e.g., keeping 4 separate `f()` calls instead of `4*f()`)
   - Functions modifying global state (like counters) demonstrate why this is necessary
- **Fundamental Optimization Blockers**
   - Two primary blockers: `memory aliasing` and f`unction side effects`
   - Compilers must generate safe code that works for all possible cases
   - These limitations explain why handwritten optimized code often outperforms compiler output
- **Programmer's Role in Optimization**
   - Must write code that minimizes aliasing and side effects
   - Should structure code to make optimization opportunities obvious to compiler
   - Need to understand compiler limitations to guide optimization efforts effectively

---

# Expressing Program Performance

- **CPE Measures Loop Efficiency**
  - Tracks `clock cycles per element (cpe)` for repetitive operations
  - Reveals true scaling performance better than time or iterations
- **Performance = Overhead + (CPE × n)**
  - For large n, CPE dominates runtime
- **Optimize CPE First**
  - Techniques like loop unrolling reduce CPE
  - Matters most for large datasets
- **Cycle Counting is better than Time Measurement**
  - Architecture-neutral performance analysis
  - Directly comparable across implementations
- ⚒️ Optimizing [vector processing](../bookcode/opt/)

---

#  Eliminating Loop Inefficiencies

- **Loop-Invariant Code Motion**  
   - Move repeated computations outside loops when results are constant.  
- **Hidden Quadratic Traps**  
   - Nested inefficiencies turn O(n) into O(n²).  
- **Compiler Limitations**  
   - Compilers rarely hoist function calls due to side-effect risks, even for "safe" functions like `strlen`.  
   - Requires **manual intervention** for optimal performance.
- **Testing Blind Spots**  
   - Small datasets hide asymptotic inefficiencies; scalability testing is critical.  
   - A "trivial" lowercase function can become a bottleneck at scale.
- **Proactive Optimization Rule**  
   - Audit loops for:  
     - Redundant function calls  
     - Invariant computations  
   - Prioritize fixes that change **time complexity** (e.g., O(n²)→O(n)).
- ⚒️ Investigate and optimize the [code](./code/op/loops.c)

---

# Reducing Procedure Calls

- **Procedure Call Trade-offs**  
   - Eliminating function calls reduces bounds-checking overhead but risks breaking modularity.  
- **Incremental Optimization Strategy**  
   - Some changes (like call reduction) are preparatory steps for future optimizations rather than immediate fixes.  
   - Always verify impact via profiling—what seems like a bottleneck may not be the limiting factor.  

---

# Eliminating Unneeded Memory References

- **Redundant Memory Operations**
  - Assembly reveals inefficient pointer tracking and repeated memory accesses
- **Register Accumulation Fix**
  - Uses a temporary register variable to eliminate redundant memory ops
- **Aliasing Trade-off**
  - Compilers can't auto-optimize due to potential memory aliasing
- **Performance vs Abstraction**
  - Manual optimization breaks modularity but achieves speedup
  - Demonstrates necessity of profiling and targeted memory optimization

---

# Understanding Modern Processors

- **Hardware Performance Characteristics**  
   - Functional units have **latency** (3-30 cycles), **issue time** (1 for pipelined ops), and **capacity** (1-4 units)  
   - Critical ops (add/multiply) are fully pipelined; division is slow/non-pipelined  
- **Performance Bounds**  
   - **Latency bound**: Minimum CPE = operation latency (sequential dependency)  
   - **Throughput bound**: CPE ≥ 1/(max ops/cycle) due to unit/memory constraints  
- **Data-Flow Analysis**  
   - Loop performance depends on **critical paths** (longest dependency chains)   
- **Optimization Insights**  
   - Pipelining enables 1 op/cycle but requires independent operations  
   - Memory bandwidth (2 loads/cycle) can bottleneck faster ALU ops  
- **Next-Step Strategy**  
   - Break sequential dependencies to approach throughput bound (CPE ~1.0)  
   - Requires restructuring for parallel execution across functional units  

---

# Loop Unrolling

- **Technique & Purpose**  
   - Loop unrolling processes *k* elements per iteration (vs. 1) to reduce loop overhead (indexing/branching) and expose optimization opportunities.
     - cleanup loop processes residuals (0 to *k−1* ops) in the last iteration
- **Performance Impact**  
   - Helps fast ops by reducing overhead.
     - e.g., integer add hits latency bound: CPE=1.00
   - Fails to improve latency-bound ops due to unchanged critical path length.
     - e.g., FP multiply: CPE=5
- **Limitation**  
   - *n×1* unrolling cannot break sequential dependencies.  
     - Assembly still serializes operations 
   - Unrolling alone is **not enough**—must combine with parallelism to hide latency
   - Overhead reduction ≠ dependency elimination. 
- ⚒️ Unroll the [loop in combine5](./code/op/loops.c)

---

# Enhancing Parallelism

- **Breaking Latency Limits**  
   - Single-accumulator loops hit latency bounds (CPE ≥ ℓ).  
   - Solution: Use 𝓀 parallel accumulators for independent operations.
  - 🍎 [2×2 Unrolling + Parallelism for `combine6`](./code/op/loops.c)
     - Processes 2 elements/iteration with 2 accumulators (even/odd indices).  
       - Halves `critical path ℓ` (CPE ≈ ℓ/2); 
- **Generalized 𝓀×𝓀 Unrolling**  
   - Unroll by 𝓀 and use 𝓀 accumulators to approach throughput bounds (CPE ≈ 1/ℂ).  
   - Required 𝓀 scales with op latency (ℓ) and unit capacity (ℂ): 𝓀 ≥ ℂ·ℓ.
- **Performance vs. Precision**  
   - **Integer**: Always safe (associative); compilers may auto-optimize.  
   - **Floating-point**: Not associative (rounding risks), but gains outweigh edge cases.
     - Manual optimization needed for FP (compilers avoid precision risks).

---

# Reassociation Transformation

- **Transformation Core**
  - Reorders operations via parentheses shift
    - e.g., `(acc OP x) OP y` → `acc OP (x OP y)`
  - Breaks sequential dependencies while maintaining mathematical equivalence (for integers)
- **Performance Gains**
  - Matches parallel accumulator results: 2× speedup for FP add/multiply (CPE ≈ L/2)
  - Achieves throughput bounds at higher unroll factors
- **Mechanism**
  - ⚒️ Creates independent operation chains in [combine7](./code/op/loops.c):
    - Chain 1: Combines new elements (x OP y)
    - Chain 2: Merges result with accumulator (acc OP result)
  - Enables pipelined execution of both chains
- **Practical Trade-offs**
  - More reliable than compiler optimizations (GCC avoids FP reassociation)
  - Simpler code than parallel accumulators but same performance ceiling
  - FP precision impact negligible in practice despite theoretical non-associativity

---

# Understanding Memory Performance

- Prefer arrays over pointer chasing
- Minimize address aliasing
- Favor sequential memory access patterns
- Batch independent loads/stores
- Let store buffer absorb write bursts

---

# Performance Improvement Techniques

- **Algorithmic Efficiency**  
   - Prioritize `high-performance algorithms/data structures` to avoid asymptotic bottlenecks.
- **Coding Best Practices**  
   - Minimize function calls in loops and unnecessary memory writes.  
   - Use temporary variables for intermediate results.
- **Hardware-Centric Optimizations**  
   - Unroll loops to reduce overhead and enable parallelism.  
   - Employ multiple accumulators or reassociation to break dependency chains.
- **Branch Optimization**  
   - Replace conditionals with conditional moves (`cmov`) where possible to avoid mispredictions.
- **Validation Strategy**  
   - Use rigorous testing to ensure optimizations don’t introduce bugs, especially for edge cases
     - e.g., partial loop iterations.  

---

# Identifying and Eliminating Performance Bottlenecks

- **Profiling-Driven Optimization**  
   - Use tools like GPROF to identify bottlenecks  
   - Focus on high-impact areas first 
     - Amdahl's Law: optimize largest time consumers
- **Validation Mindset**  
   - Test all optimizations empirically
     - e.g., iterative list scan worsened performance
   - Profile with representative *and* edge-case data to expose hidden bottlenecks
- **Algorithmic Efficiency**  
   - Use better algorithms
   - Avoid hidden traps 
- **Data Structure Tuning**  
   - Use more efficient data structure 
- **Micro-Optimizations**  
   - Prefer linear over nested loops
   - Minimize redundant operations
  