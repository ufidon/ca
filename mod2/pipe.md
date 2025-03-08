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
- Nonpipelined throughput is $`\dfrac{1}{ℓ}`$ GIPS (Giga instructions per second), latency $`ℓ=T_c+T_r=ℂ`$, completing one instruction at a time.
- Pipelining divides computation into $m$ $`\dfrac{T_c}{m}`$ stages ($s_1,s_2,⋯,s_m$) each with registers $T_r$, overlapping instructions.
- Pipelined throughput rises to $`\dfrac{1}{\dfrac{T_c}{m}+T_r}`$ GIPS ($`\dfrac{T_c}{m}+T_r=ℂ^p`$ per cycle), with all stages active in `steady` state.
- Latency increases to  $`ℓ^p =T_c+mT_r`$, a $`\dfrac{ℓ^p -ℓ}{ℓ}=\dfrac{(m-1)T_r}{T_c+T_r}`$ rise due to register overhead.
- Throughput improves $`\dfrac{ℂ}{ℂ^p}=\dfrac{T_c+T_r}{\dfrac{T_c}{m}+T_r}`$ times with `added hardware`, trading off `slight latency increase`.

---

## Pipeline Operation

- $m$-stage pipeline ($s_1,s_2,⋯,s_m$) moves instructions every $ℂ^p$ via `clock` signal.
- From $(m-1)ℂ^p→mℂ^p$, $I_1, I_2, ⋯ I_m$ shift through $s_m,s_{m-1},⋯,s_1$ as clock triggers register updates.
- Clock `rise loads` values; 
  - signals propagate through logic to next stage by $`ℓ^p`$.
- Too fast a clock risks invalid inputs; 
  - slow doesn't affect flow.
- Clocked registers between logic ensure `smooth, interference-free` instruction progression.

---

## Limitations of Pipelining

- Ideal pipelining splits computation `evenly`, but real systems face limitations reducing effectiveness.
- In `nonuniform partitioning` of pipeline, the `clock rate` is limited by the delay of the `slowest` stage.
- Balancing stages is challenging as units like `ALUs or memories resist subdivision`, complicating uniform timing in hardware design.
- `Diminishing returns` of deepening pipeline due to register delays.:
  - Throughput improvement has limit $`𝕀(m)=\dfrac{ℂ}{ℂ^p}=\dfrac{T_c+T_r}{\dfrac{T_c}{m}+T_r} \stackrel{m→∞}{→} \dfrac{T_c+T_r}{T_r}`$
  - The improvement diminishes: $`\dfrac{∂𝕀(m)}{∂m}=\dfrac{(T_c+T_r)T_c}{(T_c+T_rm)^2} \stackrel{m→∞}{→} 0`$
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
- `Data hazards` arise when an instruction's operand is updated by any of the three prior instructions.
  - Hazards occur because operands are read in the decode stage, but results are written `three cycles later` in the write-back stage.
- Pipeline adjustments are needed to handle these hazards effectively.

---

## Avoiding Data Hazards by Stalling

- Stalling prevents data hazards by delaying instructions in the processor pipeline until the hazard clears.
- Instructions are held in the decode stage until source operands are written back by prior instructions.
- Pipeline control logic enhancements detect hazards and manage stalls.
- For prog2-4, a one to three-cycle stall occurs respectively, all resolving by cycle 7.
- Stalling injects `bubbles (dynamic nop instructions)` into the execute stage to maintain pipeline flow.
- The halt instruction is also stalled by fixing the program counter during the delay.
- Stalling mimics adding nop instructions, but frequent stalls (up to three cycles) reduce performance significantly.

---

## Classes of Data Hazards

- **Program Registers**: Hazards occur due to reading in one stage and writing in another, causing unintended interactions between instructions.
- **Program Counter**: Control hazards arise from mispredicted branches or ret instructions, requiring special handling.
- *Memory*: No hazards between data memory reads and writes in the memory stage, but self-modifying code could interfere with instruction fetch; assumed not to occur here.
- *Condition Code Register*: Written in the execute stage and read by conditional moves/jumps later, avoiding hazards as prior operations complete first.
- **Status Register**: Managed by associating status codes with pipeline instructions, ensuring orderly exception handling.
- **Key Focus**: Only register data hazards, control hazards, and proper exception handling need addressing in this design.

---

## Avoiding Data Hazards by Forwarding

- **Data forwarding** bypasses stalls by `passing pending register values` directly from later pipeline stages (e.g., write-back) to earlier ones (e.g., decode).
  - also simply called `forwarding, or bypassing`.
  - requires additional data connections and control logic
- `prog2`: In cycle 6, decode logic uses a pending write-back value (W_valE) for %rax as valB, avoiding a stall.
- `prog3`: In cycle 5, decode uses write-back (W_valE) for %rdx and memory stage (M_valE) for %rax, skipping stalls.
- `prog4`: In cycle 4, decode forwards memory stage (M_valE) for %rdx and ALU output (e_valE) for %rax, preventing delays.
- **Forwarding sources and destinations**: 
  - Five sources: ALU output (e_valE), memory read (m_valM), memory stage (M_valE), and write-back (W_valM, W_valE).
  - Two destinations: valA and valB.
- **Logic Design in PIPE**: Decode compares source IDs (srcA, srcB) with destination IDs, prioritizing among multiple matches to select forwarded values.
  - enables forwarding the results from the three preceding instructions. 

---

## Load/Use Data Hazards

- `Load/Use hazard` occurs when an instruction (e.g., addq) needs a register value before a prior memory read (e.g., mrmovq) provides it as in [prog5](./code/y86code/prog5.ys).
  - i.e. `use before load`
- **Timing Issue**: In cycle 7, addq needs %rax, but mrmovq updates it in cycle 8—too late for pure forwarding.
- **Forwarding Limitation**: Forwarding can't send memory read values backward in time, unlike register hazards (e.g., %rbx in prog5).
- **Solution—Stalling + Forwarding**: Stall the addq in decode for one cycle, injecting a bubble into execute.
  - This stall, called a `load interlock`, combined with forwarding, resolves all data hazards, minimizing throughput loss.
- **Execution Flow**: In cycle 8, memory stage forwards %rax (m_valM) to decode, while %rbx is forwarded from write-back (W_valE).

---

## Avoiding Control Hazards

- `Control Hazards` occur when the `next instruction address` can't be reliably determined in the fetch stage, 
  - mainly with `ret` and `jump` instructions.
  - Pipeline control logic uses `stalling and bubble injection` to dynamically manage control hazards.
- **Ret Instruction**: For [prog](./code/y86code/prog6.ys), `ret` stalls the pipeline in decode, execute, and memory stages, injecting three bubbles until the return address is set in write-back.
- **Mispredicted Jump**: In [prog7](./code/y86code/prog7.ys), a `jne` predicted taken fetches target instructions, but a `misprediction` is detected in cycle 4.
  - Pipeline `cancels` two misfetched instructions in cycle 5 by `injecting bubbles` into decode and execute, fetching the correct fall-through instruction.
    - Cancel is sometimes called instruction squashing
  - No state changes occur from misfetched instructions (pre-execute), but two cycles are wasted.

---

## Exception Handling

- `Exception` breaks the normal chain of program execution: 
  - Three internal exceptions in Y86-64: halt instruction, invalid instruction code, and invalid address access; 
  - External exceptions (e.g., network signals) not covered here.
- **Goal**: Halt processor on exception, set status code, complete prior instructions, and prevent subsequent ones from altering visible state.
- `Multiple Exceptions`: Prioritize the exception from the instruction furthest in the pipeline ,e.g., memory stage over fetch stage.
- [Mispredicted Branch Issue](./code/y86code/prog9.yo): Cancel fetched instructions, e.g., invalid code at Ox016, from mispredicted branches to avoid false exceptions.
- [State Update Conflict](./code/y86code/prog10.ys): Disable updates (e.g., condition codes) by later instructions (e.g., addq) when an earlier one (e.g., pushq) causes an exception.
- **Pipeline Integration handling exception**: Track exception status in pipeline registers (`stat field`), propagate to write-back, halt execution, and block state changes by later instructions.

---

# [PIPE Stage Implementations](./y86sim/hcl.pdf)

- The Pipelined Y86-64 processor with forwarding is built on SEQ/SEQ+ hardware,
  - adding pipeline registers, reconfigured logic, and control logic.
- Most PIPE logic blocks are identical to SEQ/SEQ+, but `signals` are sourced from pipeline registers or stage computations
  - Uppercase prefixes (e.g., D_) denote pipeline register sources; 
  - lowercase prefixes (e.g., d_) denote stage-generated values.
- 🍎 SEQ uses icode and rA directly; 
  - PIPE uses D_icode and D_rA from decode register D, differing only in prefixes.

---

## PC Selection and Fetch Stage

- PIPE's fetch stage predicts the next PC and fetches instructions within one cycle,
  - using SEQ's memory read and field extraction units.
- The `PC selection logic` chooses from three PC sources: 
  - M_valA (mispredicted branch in memory stage), 
  - W_valM (ret in write-back), 
  - F_predPC (default predicted PC).
- The `PC prediction logic` selects valC for call/jump instructions, otherwise uses valP for the next PC.
- **Instruction status split**: 
  - Fetch stage checks for instruction memory errors, illegal instructions, or halt;
  - Memory stage detects data address errors.

---

## Decode and Write-Back Stages

- The `decode and write-back` logic in PIPE involves `forwarding logic` and `merging signals` like `valA` and `valP` to reduce pipeline register state.  
- Write-back stage signals (`W_dstE`, `W_dstM`) specify `register write locations` instead of decode stage signals, 
  - ensuring writes align with the instruction in the write-back stage.  
- The `Sel+Fwd A` block merges `valP` into `valA` for call/jump instructions and implements forwarding for source operand `valA`. 
  - The `Fwd B` block handles forwarding for source operand `valB`.  
- There are `five forwarding sources` (e.g., `e_valE`, `m_valM`, `W_valE`) provide data and destination register IDs, 
  - with priority given to the earliest pipeline stage to reflect the most recent instruction.  
- Forwarding logic `prioritizes` execute stage sources over memory and write-back stages to ensure correct program behavior, 
  - defaulting to register file values if no forwarding applies
  - mimicking sequential execution.    
- The overall `processor status (Stat)` is determined by the status in the write-back stage (`W_stat`), 
  - with `AOK` indicating `normal operation or bubbles` in the pipeline.  
- 🍎 [prog8](./code/y86code/prog8.ys) demonstrates forwarding priority, 
  - where the execute stage value for `%rdx` is chosen over the memory stage value to reflect the most recent update.

---

## Execute Stage

- The `execute stage logic` mirrors SEQ with forwarding signals (`e_valE`, `e_dstE`)
  - add `Set CC` logic to update condition codes, suppressed by `m_stat` and `W_stat` during exceptions.  
- `Exception handling` prevents condition code updates if exceptions are detected in memory or write-back stages.

---

## Memory Stage

- The `memory stage logic` is similar to SEQ, but excludes the `Mem.data` block, 
  - as data selection (e.g., `valP` or `valA`) is handled by the decode stage's `Sel+Fwd` logic.  
- Signals from `pipeline registers M and W` are passed to earlier stages for write-back results, instruction addresses, and forwarding.

---

# Pipeline Control Logic

- **Load/Use Hazards**: Stall pipeline one cycle between a memory read and its use.
- **Processing ret**: Stall until ret reaches write-back stage.
- **Mispredicted branches**: Cancel target instructions and fetch from the correct next instruction.
- **Exceptions**: Disable state updates by later instructions and halt at write-back.

---

## Desired Handling of Special Control Cases

- **Load/Use Hazard**: Stall decode stage one cycle for mrmovq/popq, inject bubble into execute, then forward data.
  - Check execute stage for mrmovq/popq and decode for dependent instruction, freeze F and D registers.
- [Ret Processing](./code/y86code/prog6.yo): Stall fetch three cycles, fetch next instruction repeatedly, replace with bubbles in decode until `ret` hits write-back.
  - Predict PC as valP (often wrong), stall fetch, insert bubbles in decode for three cycles.
- **Mispredicted Branch**: Detect in execute, inject bubbles into decode and execute, fetch correct instruction next cycle.
  - Cancel two misfetched instructions with bubbles, redirect fetch to fall-through instruction.
- **Exception Handling**: Track status (stat) in pipeline registers, halt at write-back, disable state updates by later instructions.
  - Detect in fetch/memory, update stat, disable condition codes/memory writes as exception progresses.
- 🍎 [pushq](./code/y86code/prog10.yo) in memory (cycle 6) triggers error, disables addq's condition code update in execute.
- **Pipeline Control**: Use stat signals, set_cc disable, and bubble/stall combo to ensure prior instructions complete, subsequent ones don't affect state.

---

## Detecting Special Control Conditions

-  Detection conditions for pipeline control logic

| **Condition** | **Trigger**     |
|---------------|-----------------|
| Processing `ret` | IRET ∈ {D_icode, E_icode, M_icode}   |
| Load/use hazard | E_icode ∈ {IMRMOVQ, IPOPQ} && E_dstM ∈ {d_srcA, d_srcB}  |
| Mispredicted branch | E_icode = IJXX && !e_Cnd  |
| Exception  | m_stat ∈ {SADR, SINS, SHLT} ‖ W_stat ∈ {SADR, SINS, SHLT} |

- **Ret Detection**: Check D_icode, E_icode, M_icode for IRET to identify ret in decode, execute, or memory stages.
- **Load/Use Hazard**: Detect IMRMOVQ or IPOPQ in execute (E_icode) with E_dstM matching d_srcA or d_srcB in decode.
- **Mispredicted Branch**: Identify IJXX in execute (E_icode) with e_Cnd false, signaling a misprediction.
- **Exception Detection**: Monitor m_stat (memory stage) and W_stat (write-back) for SADR, SINS, or SHLT status codes.

---

## Pipeline Control Mechanisms

- `Pipeline registers` use two signals `stall (hold state)` and `bubble (reset to nop)` to manage special cases, extending basic clocked register design.
- `Normal (load input), stall (keep state), or bubble (set to nop)` operations are triggered by stall and bubble inputs, with specific reset configurations per register.

| Condition            | F     | D     | E     | M     | W     |  
|----------------------|-------|-------|-------|-------|-------|  
| **Processing ret**   | stall | bubble | normal | normal | normal |  
| **Load/use hazard**  | stall | stall  | bubble | normal | normal |  
| **Mispredicted branch** | normal | bubble | bubble | normal | normal |  

---

## Combinations of Control Conditions

- Most conditions (e.g., load/use hazard and mispredicted branch) can’t coexist due to differing execute stage requirements, but two following two combinations can.
- `Mispredicted branch (execute) with ret (decode)` cancels ret, stalling fetch and bubbling decode/execute, handled correctly.
 

| Condition             | F      | D      | E      | M      | W      |  
|----------------------|-------|-------|-------|-------|-------|  
| **Processing ret**   | stall | bubble | normal | normal | normal |  
| **Mispredicted branch** | normal | bubble | bubble | normal | normal |  
| **Combination**      | stall | bubble | bubble | normal | normal |  

- `Load/use hazard (execute) with ret (decode)` conflicts—logic tries to stall and bubble decode simultaneously.
  - **Issue**: Without priority, both stall and bubble signals for D register activate, violating design (bubble + stall = error).
  - **Resolution**: Prioritize load/use hazard actions (stall F/D, bubble E), delay ret actions by one cycle for correct ISA behavior.

| Condition             | F      | D            | E      | M      | W      |  
|----------------------|-------|-------------|-------|-------|-------|  
| **Processing ret**   | stall | bubble      | normal | normal | normal |  
| **Load/use hazard**  | stall | stall       | bubble | normal | normal |  
| **Combination**      | stall | `bubble+stall` | bubble | normal | normal |  
| **Desired**         | stall | stall       | bubble | normal | normal |  

- **Design Insight**: `Systematic analysis` revealed a subtle bug in PIPE’s original control logic, missed by simulations.

---

## Control Logic Implementation

- **Control Logic Structure**: PIPE’s pipeline control logic generates stall/bubble signals and controls condition code updates based on pipeline register/stage signals.
- **F Stall Conditions**: Stalls for load/use hazards (E_icode in {IMRMOVQ, IPOPQ} and E_dstM in {d_srcA, d_srcB}) or ret (IRET in {D_icode, E_icode, M_icode}).
- **D Bubble Conditions**: Bubbles for mispredicted branches (E_icode == IJXX && !e_Cnd) or ret, but avoids bubbling if a load/use hazard is present with ret.
- **Implementation**: Combines detection and actions into HCL, with other control signals defaulting to zero in the full design.

---

## Performance analysis

- **Pipeline Inefficiency**: 
  - `Special control conditions` (ret, load/use hazard, mispredicted branch) prevent PIPE from issuing one instruction per cycle, injecting bubbles.
  - `ret` injects 3 bubbles, `load/use hazard` 1, `mispredicted branch` 2, reducing throughput.
- `Cycles per instruction (CPI)` measures efficiency as 
  - $`\dfrac{C_i + C_b}{C_i}=1.0+\dfrac{C_b}{C_i}=1.0+lp+mp+rp`$, 
  - where C_i is instructions executed and C_b is bubbles.
- The penalty term $`\dfrac{C_b}{C_i}`$ is broken into three components, each reflecting average bubble frequency per inject-bubble instruction type: 
  - `load/use` penalty (lp), 
  - `mispredicted branch` penalty (mp), 
  - `return` penalty (rp).
- 🛠️ Find the penalties and CPI:

| **Cause** |  **Name** | **Instruction<br> Frequency** | **Condition<br> Frequency** | **Bubbles** | **Product** |
|---|---|----|----|------|------|
| Load/use | Ip | 0.25    | 0.20  | 1     | 0.05  |
| Mispredict  | mp | 0.20    | 0.40  | 2     | 0.16  |
| Return | rp | 0.02    | 1.00  | 3     | 0.06  |
| **Total penalty** |    |   | | | **0.27**    |

- **Resulting CPI**: CPI = 1.0 + 0.27 = 1.27, close to but above the ideal 1.0.
- **Optimization Focus**: Mispredicted branches (0.16 of 0.27 penalty) are the primary CPI limiter due to frequency, prediction failure, and dual cancellations.

---

## Further Features Desired - Multicycle Instructions

- **Simple Instructions**: Y86-64 instructions (e.g., addition) execute in one cycle in PIPE’s execute stage.
- **Complex Instructions**: Full instruction sets include `multicycle operations` needing extra hardware and coordination
  - e.g., 3-4 cycles for floating-point add, up to 64 for integer division
- **Basic Approach**: Expand execute stage with arithmetic units, 
  - stalling fetch/decode during multicycle execution
  - simple but low performance.
- **Improved Design**: Use independent, pipelined `functional units` 
  - e.g., for integer multiplication/division, floating-point, issuing instructions from decode, 
  - with synchronization via stalling and forwarding.

---

## Further Features Desired - Interfacing with the Memory System

- **Memory Assumptions in PIPE**: 
  - single-cycle instruction fetch and data memory access, 
  - ignoring self-modifying code and virtual-to-physical address translation.
- **Memory Hierarchy**: 
  - Uses `caches` (instruction and data) and `TLBs` (translation look-aside buffer) for fast access, backed by slower main memory and disk, 
  - enabling near single-cycle performance most times.
- **Cache Miss Handling**: 
  - Stalls pipeline (fetch or memory stage) for 3-20 cycles to retrieve data from higher caches or main memory, 
  - managed by hardware via added stall conditions.
- **Page Faults**: 
  - Disk access triggers a page fault exception, handled by the OS (millions of cycles), 
  - which reloads data and restarts the instruction, potentially causing a `cache miss`.
- **Performance Strategy**: 
  - Combines `short-term stalling` for cache misses and `OS exception handling` for page faults to manage memory access variability.

---

# References
- [Intel® 64 and IA-32 Architectures Software Developer's Manual Combined Volumes](https://www.intel.com/content/www/us/en/content-details/782158/intel-64-and-ia-32-architectures-software-developer-s-manual-combined-volumes-1-2a-2b-2c-2d-3a-3b-3c-3d-and-4.html)
  - [x86-64 Instructions Set](https://linasm.sourceforge.net/docs/instructions/index.php)
  - [x86 and amd64 instruction reference](https://www.felixcloutier.com/x86/)
- [Y86-64 simulator](https://github.com/gyunseo/sim)
- [RISC-V Instruction Set Manual](https://github.com/riscv/riscv-isa-manual)