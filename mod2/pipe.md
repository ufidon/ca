# Processor architecture
CS:APP3e.ch04


# The Y86-64 ISA Pipeline Implementation
- SEQ → SEQ+ → PIPE- → PIPE

---

# General Principles of Pipelining

- Pipelined systems divide tasks into discrete stages, allowing multiple tasks to be processed simultaneously.
- Tasks progress through all stages in order, maintaining a consistent flow.
- Pipelining boosts throughput (tasks completed per time unit) but may slightly increase latency (time for one task to finish), 
  - as skipping stages isn't typically allowed.
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
  - slow doesn't affect flow.
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

- Starting with SEQ adaptation and pipeline registers.
- Fixing initial dependency issues to get an efficient Y86-64 pipelined processor.

---

## SEQ+: Rearranging the Computation Stages

- SEQ+ updates the PC at the start of the clock cycle for better pipelining. 
- Uses state registers to hold prior cycle signals for smooth execution. 
  - SEQ+ computes the PC from stored state, not a dedicated register. 
- Retains SEQ's hardware but shifts PC logic to the cycle's start. 
  - Enables pipelining and out-of-order execution without strict state encoding.
- Redistributes state elements without altering logic, balancing delays.  
  - Prepares for efficient pipelined instruction execution.

---

## Inserting Pipeline Registers

- PIPE-, a pipelined Y86-64 processor, `adds pipeline registers` between SEQ+ stages, tweaking signals for better flow.
- PIPE- keeps SEQ's hardware, using pipeline registers F, D, E, M, and W to separate fetch, decode, execute, memory, and write-back stages.

| Register | Purpose |  
|----------|---------|  
| **F** | Holds predicted PC value. |  
| **D** | Stores fetched instruction for decoding. |  
| **E** | Holds decoded instruction and register values for execution. |  
| **M** | Stores execution results and branch info for memory stage. |  
| **W** | Holds memory results for register write-back and PC updates. |

- Instructions move through stages across clock cycles, 
  - overlapping for efficiency with a bottom-to-top flow matching program listings.

---

## Rearranging and Relabeling Signals

- In SEQ and SEQ+, signals like `valC, srcA, and valE` have single values per instruction, 
  - but in the pipelined PIPE-, `multiple versions` exist for different instructions, requiring careful signal management.
- PIPE- naming scheme: 
  - `D_stat, E_stat`, etc. denote `status code fields` in pipeline registers
  - `f_stat, m_stat`, etc. denote `status signals` generated in fetch, memory, or other stages.
- Unlike SEQ+, where dstE and dstM directly connect to the register file, 
  - PIPE- carries these signals through the pipeline, reaching the write-back stage to ensure data and address inputs match the same instruction.
- A new `Select A` block in PIPE-'s decode stage merges valP and register file values into `valA`, 
  - reducing pipeline register state compared to SEQ+, eliminating the `Data block`.
- Pipeline registers in PIPE- include a `status code (stat)` per instruction,
  - computed in fetch and updated in memory, 
  - aiding systematic tracking of instruction progress and exceptions.

---

## Predicting Next PC

- PIPE- aims to `issue one instruction per clock cycle` by predicting the next PC after fetching, 
  - despite delays from `conditional branches` and `ret instructions`.
- For most instructions (except conditional jumps and ret), 
  - the next PC is reliably predicted as valC (for call/jump) or valP (for others) during fetch.
- `Conditional` jumps use `branch prediction`, 
  - assuming jumps are taken (PC = valC), with mispredictions handled later.
- `ret` instructions stall further processing until write-back provides the return address, avoiding prediction.
- PIPE-'s fetch stage predicts PC with `Predict PC` (valP or valC) stored in register F, 
  - while S`elect PC` chooses between predicted PC, M_valA (not-taken branch), or W_valM (ret).

---

## Pipeline Hazards

- Introducing `feedback` into PIPE leads to issues due to `dependencies between instructions`.
  - `data` dependencies: `results` used by following instructions 
  - `control` dependencies: `instruction location` determined by prior instructions.
- `Hazards` occur when dependencies risk incorrect pipeline computations
  - divided into `data` hazards and `control` hazards.
- 🛠️ [Prog1](./code/y86code/prog1.ys) shows correct execution with `three nop` instructions delaying data-dependent instructions, `avoiding hazards`.
- 🛠️ [Prog2](./code/y86code/prog2.ys), with `two nop` instructions, results in a `data hazard` as the addq instruction reads an outdated %rax value in cycle 6.
- 🛠️ [Prog3](./code/y86code/prog3.ys), with `one nop`, `fails` as addq reads incorrect values for both %rdx and %rax in cycle 5 due to pending writes.
- 🛠️ [Prog4](./code/y86code/prog4.ys), with `no nops`, `worsens` the hazard, with addq in cycle 4 reading wrong values as %rdx and %rax updates are still in memory and execute stages.
- `Data hazards` arise when an instruction’s operand is updated by any of the three prior instructions.
  - Hazards occur because operands are read in the decode stage, but results are written `three cycles later` in the write-back stage.
- Pipeline adjustments are needed to handle these hazards effectively.

---

## 


---


# References
- [Intel® 64 and IA-32 Architectures Software Developer's Manual Combined Volumes](https://www.intel.com/content/www/us/en/content-details/782158/intel-64-and-ia-32-architectures-software-developer-s-manual-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html)
  - [x86-64 Instructions Set](https://linasm.sourceforge.net/docs/instructions/index.php)
  - [x86 and amd64 instruction reference](https://www.felixcloutier.com/x86/)
- [Y86-64 simulator](https://github.com/gyunseo/sim)
- [RISC-V Instruction Set Manual](https://github.com/riscv/riscv-isa-manual)