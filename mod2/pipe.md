# Processor architecture
CS:APP3e.ch04


# The Y86-64 ISA Pipeline Implementation

---

# General Principles of Pipelining

- Pipelined systems divide tasks into discrete stages, allowing multiple tasks to be processed simultaneously.
- Tasks progress through all stages in order, maintaining a consistent flow.
- Pipelining boosts throughput (tasks completed per time unit) but may slightly increase latency (time for one task to finish), 
  - as skipping stages isn’t typically allowed.
- A nonpipelined system might serve a single need faster, 
  - pipelining optimizes overall efficiency for multiple tasks.

---

## Computational Pipelines

- Computational pipelines process instructions in stages, unlike nonpipelined systems with one computing block $T_c$ and register $T_r$.
- Nonpipelined throughput is $`\dfrac{1}{𝓁}`$ GIPS (Giga instructions per second), latency $`𝓁=T_c+T_r=𝒞`$, completing one instruction at a time.
- Pipelining divides computation into $m$ $`\dfrac{T_c}{m}`$ stages ($s_1,s_2,⋯,s_m$) each with registers $T_r$, overlapping instructions.
- Pipelined throughput rises to $`\dfrac{1}{\dfrac{T_c}{m}+T_r}`$ GIPS ($`\dfrac{T_c}{m}+T_r=𝒞'`$ per cycle), with all stages active in `steady` state.
- Latency increases to  $`𝓁'=T_c+mT_r`$, a $`\dfrac{𝓁'-𝓁}{𝓁}=\dfrac{(m-1)T_r}{T_c+T_r}`$ rise due to register overhead.
- Throughput improves $`\dfrac{𝒞}{𝒞'}=\dfrac{T_c+T_r}{\dfrac{T_c}{m}+T_r}`$ times with `added hardware`, trading off `slight latency increase`.

---

## Pipeline Operation

- $m$-stage pipeline ($s_1,s_2,⋯,s_m$) moves instructions every $𝒞'$ via `clock` signal.
- From $(m-1)𝒞'→m𝒞'$, $I_1, I_2, ⋯ I_m$ shift through $s_m,s_{m-1},⋯,s_1$ as clock triggers register updates.
- Clock `rise loads` values; 
  - signals propagate through logic to next stage by $𝓁'$.
- Too fast a clock risks invalid inputs; 
  - slow doesn’t affect flow.
- Clocked registers between logic ensure `smooth, interference-free` instruction progression.

---

## Limitations of Pipelining

- Ideal pipelining splits computation `evenly`, but real systems face limitations reducing effectiveness.
- In `nonuniform partitioning` of pipeline, the `clock rate` is limited by the delay of the `slowest` stage.
- Balancing stages is challenging as units like `ALUs or memories resist subdivision`, complicating uniform timing in hardware design.
- `Diminishing returns` of deepening pipeline due to register delays.:
  - Throughput improvement has limit $`𝒮(m)=\dfrac{𝒞}{𝒞'}=\dfrac{T_c+T_r}{\dfrac{T_c}{m}+T_r} \stackrel{m→∞}{→} \dfrac{T_c+T_r}{T_r}`$
  - The improvement diminishes: $`𝒮'(m)=\dfrac{(T_c+T_r)T_c}{(T_c+T_rm)^2}→0`$
- `Deep` pipelines (15+ stages) aim for high clock rates, 
  - requiring simple steps, minimal register delays, and precise clock synchronization across the chip.

---

## Pipelining a System with Feedback

- Y86-64 pipelining faces dependencies: 
  - `data` dependencies: e.g., sharing registers between instructions 
    - Instructions like irmovq → addq → mrmovq chain results (%rax, %rbx), needing sequential flow.
  - `control` dependencies: e.g., call, ret, and jump instructions.
    - Control flow (e.g., jne in loops) relies on feedback in SEQ to update registers/PC.
- Pipelining with `feedback` (e.g., $m$-stage) shifts behavior, linking $I_1$ to $I_m$, not $I_2$.
- Pipelined Y86-64 must handle dependencies to match ISA behavior.

---

# Pipelined Y86-64 Implementations

---


# References
- [Intel® 64 and IA-32 Architectures Software Developer's Manual Combined Volumes](https://www.intel.com/content/www/us/en/content-details/782158/intel-64-and-ia-32-architectures-software-developer-s-manual-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html)
  - [x86-64 Instructions Set](https://linasm.sourceforge.net/docs/instructions/index.php)
  - [x86 and amd64 instruction reference](https://www.felixcloutier.com/x86/)
- [Y86-64 simulator](https://github.com/gyunseo/sim)
- [RISC-V Instruction Set Manual](https://github.com/riscv/riscv-isa-manual)