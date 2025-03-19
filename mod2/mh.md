# The memory hierarchy
CS:APP3e.ch06

---

## Overview

- Early `CPU-memory model` used a `linear byte array` with `constant access time`, 
  - a good model for [MCUs](https://en.wikipedia.org/wiki/ARM_Cortex-M) with `flat` memories such as [ARM Cortex-R](https://en.wikipedia.org/wiki/ARM_Cortex-R)
- [Modern computer systems](https://en.wikipedia.org/wiki/ARM_Cortex-A) have `hierarchical memory` consisting of registers, cache, main memory, disks 
  - balancing speed, size, and cost
  - `access times` range from 0 cycles (registers) to millions (disk), impacting program efficiency.
- Programs with `good locality` access `data frequently or nearby`, 
  - optimizing hierarchy use for speed.
- **Key Focus**: 
  - storage tech, caches, locality optimization,
  - analysis, visualization, and application of access times based on locality.

---

# Storage Technologies
- RAM, ROM, disk

---

## Random access memory (RAM)

- Static RAM (SRAM) vs. Dynamic RAM (DRAM)

|       | Transistors per bit | Relative access time | Persistent? | Sensitive? | Relative cost | Applications |
|-------|---|----|-------------|------------|---------------|-------|
| SRAM  | 6   | 1x   | Yes | No | 1,000x| Cache memory    |
| DRAM  | 1   | 10x  | No  | Yes| 1x    | Main memory, frame buffers |

---

## Conventional DRAMs

- DRAM chips are divided into `d` supercells (words), each with `w` cells (bits) (`dw` total bits), organized as an `row x column` array (`r × c = d`), with each supercell at address `(i, j)`.
  - 🍎 A 16 x 8 DRAM (128 bits) has 16 supercells, 8 bits each, in a 4x4 array; 
  - data transfers via `8 data pins`, addresses via `2 addr pins`.
- `Memory Controller` transfers w bits at a time, 
  - using RAS (row address i) and CAS (column address j) requests to access supercell (i, j) in two steps.
  - 🍎 For supercell (2,1), the controller sends row 2 (RAS), loads row 2 into a buffer, then sends column 1 (CAS), retrieving 8 bits.
- **Design Trade-off**: 2D arrays reduce address pins (e.g., 2 instead of 4 for 16 supercells) but increase access time due to two-step addressing.
  - The number of `address pins = ⌈max(log₂r, log₂c)⌉` can be minimized by minimizing the difference of r and c.

---

## Enhanced DRAMs

- Variants of conventional DRAM cells are optimized for faster access to match rising processor speeds.
- **FPM (fast page mode) DRAM**: Improves speed by reusing row buffer data for consecutive accesses in the same row, reducing RAS/CAS requests to one RAS/CAS plus multiple CAS.
- **EDO (extended data out) DRAM**: Enhances FPM by allowing closer CAS signal timing, boosting access efficiency.
- **Synchronous DRAM (SDRAM)**: Synchronous design uses clock edges instead of explicit signals, enabling faster supercell output compared to asynchronous DRAMs.
- **Double Data-Rate(DDR) SDRAM**: DDR SDRAM doubles speed with both clock edges and prefetch buffers (2, 4, 8 bits for DDR, DDR2, DDR3); 
- **Video RAM (VRAM)** supports concurrent reads/writes for graphics frame buffers.

---

## Nonvolatile Memory

- Unlike volatile DRAMs/SRAMs, nonvolatile memories retain data without power,
  - varying by reprogramming capability and method.
- Programmable ROM `(PROM)` can be written once by blowing fuses in each cell using high current.
- EPROM is erasable (UV light) and reprogrammable ~1,000 times; 
  - EEPROM is electrically erasable, reprogrammable ~100,000 times in-circuit.
- **Flash Memory**: A widely used EEPROM-based nonvolatile memory, found in devices like cameras, phones, SSDs, offering fast, durable storage.
- **Firmware**: ROM-stored programs run on startup (e.g., BIOS) or handle I/O in devices like graphics cards and disk controllers.

---

## Accessing Main Memory

- `Data moves between CPU and DRAM main memory` via buses using `bus transactions`
  - read: memory to CPU; 
  - write: CPU to memory.
- Buses are `parallel wires` carrying address, data, and control signals, sometimes shared,
  - connecting multiple devices like CPU, memory, and I/O.
- CPU, I/O bridge (with memory controller), and DRAM modules are linked by a `system bus (CPU to I/O bridge)` and `memory bus (I/O bridge to memory)`.
- **Read Transaction**: For a load (e.g., `movq A,%rax`), 
  - CPU sends address A via system bus, 
  - I/O bridge forwards to memory bus, 
  - memory fetches data from DRAM, 
  - and CPU copies it to %rax.
- **Write Transaction**: For a store (e.g., `movq %rax,A`), 
  - CPU sends address A, then data from %rax via system bus; 
  - memory reads data from memory bus and stores it in DRAM.
- `I/O Bridge` translates signals between system bus and memory bus, 
  - also connecting to `I/O bus for devices` like disks and graphics cards.

---

## Disk Geometry and Capacity

- Disks store `vast` data (hundreds to thousands of GB), disk capacity is expressed in GB (10⁹ bytes) or TB (10¹² bytes)
  - but access is `slow` (milliseconds), 100,000x slower than DRAM, 1,000,000x slower than SRAM.
- **Disk Geometry**: 
  - Disks have `platters` with two magnetic `surfaces`, spinning at 5,400–15,000 RPM; 
    - each surface has `tracks`, divided into 512-byte `sectors` separated by gaps.
  - Multiple platters form a disk drive; `tracks equidistant` from the center across all surfaces form `cylinders` 
    - e.g., 3 platters = 6 surfaces = 6 tracks per cylinder.
  - Modern disks use `multiple zone` recording, 
    - grouping cylinders into zones with consistent sector counts per track, 
    - optimizing space as areal density increases.
- **disk Capacity**: 
  - Capacity depends on recording density (bits/inch), track density (tracks/inch), and areal density (bits/in² = recording × track density).
  - Capacity = (bytes/sector) × (avg sectors/track) × (tracks/surface) × (surfaces/platter) × (platters/disk); 
    - e.g., 5 platters, 512 bytes/sector, 300 sectors/track, 20,000 tracks/surface = 30.72 GB.

---

## Disk Operation

- Disks use a `read/write` head on an actuator arm to access data; the arm seeks tracks, 
  - and heads (one per surface) move together across cylinders.
  - Heads fly 0.1 microns above the surface at 2 cm/ms, requiring sealed packaging to prevent head crashes from dust.
- Disk `access time` includes seek time (arm movement), rotational latency (waiting for sector), and transfer time (reading/writing sector).
  - `Average seek time (Tavg seek)` is 3–9 ms, max 20 ms, 
    - depending on arm movement and prior head position.
  - Max latency (Tmax rotation) is (60/RPM) seconds; 
    - `average (Tavg rotation)` is half that, e.g., 4.2 ms at 7,200 RPM.
  - `Average transfer time (Tavg transfer)` is (60/RPM ÷ average sectors/track) seconds, 
    - e.g., 0.021 ms for 400 sectors/track at 7,200 RPM.
- 📝 For a 7,200 RPM disk (Tavg seek = 9 ms, 400 sectors/track), access time is 13.22 ms (9 + 4.2 + 0.021), 
  - dominated by `seek and latency`, 
  - ~40,000x slower than SRAM, ~2,500x slower than DRAM.

---

## Logical Disk Blocks

- Modern disks abstract their complex geometry (multiple surfaces, zones) into `a linear sequence of B logical blocks (0 to B-1)` for the operating system.
- The disk controller maps `logical block numbers` to `physical (surface, track, sector) locations`, performing I/O by moving heads, reading sectors, and transferring data to memory.

---

## Connecting I/O Devices

- `I/O devices` connect to the CPU and memory via an I/O bus, 
  - which is slower but CPU-independent.
  - Common I/O bus devices include `USB controllers` (for keyboards, mice, etc., with USB 3.0 at 625 MB/s, USB 3.1 at 1,250 MB/s), `graphics cards`, and `host bus adapters` (SCSI/SATA for disks).
- The `I/O bus` links CPU, main memory, and devices, differing from CPU-specific system/memory buses.
  - Additional devices like network adapters can connect via `motherboard expansion slots`, directly linking to the I/O bus.

---

## Accessing Disks

CPU reads disk data via a multi-step process involving `memory-mapped I/O, DMA, and interrupts`:
- CPU sends `commands` to disk via I/O ports (e.g., port 0xa0), 
  - using `store instructions` to specify read command, logical block number, and memory destination.
- After issuing the request, the CPU performs `other tasks` during the ~16 ms disk read, avoiding wasteful idle time.
- Disk controller translates the block number to a sector, reads it, and transfers data directly to memory via `DMA`, bypassing CPU involvement.
- `Post-transfer`, the disk controller sends an `interrupt` to the CPU, which pauses, handles the completion via an OS routine, and resumes.

---

## Solid State Disks

`Solid State Disks (SSDs)` use flash memory, connect via USB/SATA, act like traditional disks, with a `flash translation layer` mapping logical blocks to physical flash:
- Flash memory has B blocks, each with P pages (512 bytes–4 KB); 
  - pages are read/written directly, 
  - but writing requires erasing the entire block (setting bits to 1).
- SSDs offer `faster reads than writes` due to slow block erasing (~1 ms) and data copying. e.g., 
  - read: 550 MB/s sequential, 89,000 IOPS random
  - write: 470 MB/s sequential, 74,000 IOPS random
- `SSDs outperform rotating disks` with faster access, lower power use, and greater durability (no moving parts),
  - but cost ~30x more per byte and have smaller capacities.
- **Challenges & Trends**: 
  - Flash blocks wear out after ~100,000 writes, mitigated by wear-leveling; 
  - SSDs are replacing disks in portable devices, laptops, and servers as prices drop.

---

## Storage Technology Trends

- SRAM is faster but costlier than DRAM; DRAM is faster than disks; SSDs balance DRAM and disk in price/performance.
  - Since 1985, SRAM cost and access times dropped ~100x; DRAM cost fell 44,000x but access time only 10x; disk cost dropped 3,000,000x, access time 25x.
- `Increasing storage density` (lowering cost) is easier than `reducing access time` across SRAM, DRAM, and disks.
- CPU cycle times improved 500x (2,000x with multi-core) from 1985–2010, 
  - outpacing DRAM/disk performance, widening the processor-memory gap.
  - Pre-2003, the gap was latency-driven; post-2003, multi-core CPUs increased throughput demands, further straining DRAM/disk performance.
  - SRAM performance improves but lags CPUs, roughly keeping pace compared to DRAM and disks.
- **Caching Solution**: Modern systems use SRAM-based caches to bridge the processor-memory gap, leveraging `program locality`.

---

# Locality

- **Locality Principle**: Well-written programs exhibit `locality`, 
  - referencing `nearby` or `recently` used data, 
  - impacting hardware and software design/performance.
- **Types of Locality**: 
  - `Temporal` locality: `reusing` data soon after access
  - `spatial` locality: accessing `nearby` data.
- Programs with good locality run faster; 
  - systems exploit this at hardware (caches), OS (memory/disk caching), and application levels (e.g., Web caching).
- `Caches` store recently used and nearby instructions/data, 
  - speeding up main memory access based on locality.
- 🍎 The `sumvec` function below shows good spatial locality, accessing vector elements sequentially as stored in memory.

```c
// the vector elements are accessed in the same order that they are stored in memory.
int sumvec(int v[N]) {
    int i, sum = 0;
    for (i = 0; i < N; i++) {
        sum += v[i];
    }
    return sum;
}
```

---

## Locality of References to Program Data

- The `sumvec` function above has 
  - good `temporal` locality for `sum` (frequently referenced) and good `spatial` locality for vector `v` (sequential access), 
  - but poor temporal locality for `v` (each element accessed once).
- `sumvec` uses a `stride-1 (sequential)` reference pattern for `v`, maximizing spatial locality; 
  - larger strides (e.g., stride-k) reduce spatial locality.
- Interchanging loops (row-wise to column-wise) in 2D array access significantly degrades spatial locality due to mismatched memory layout and access pattern.
  - 📝 [Sum an array](./code/mh/sumarr.c) row-wisely and column-wisely

---

## Locality of Instruction Fetches

- Programs exhibit `good locality` as instructions are rarely modified at runtime.
  - `good spatial locality in instruction fetches` (e.g., sequential loop execution) 
  - `good temporal locality` (repeated loop execution), 
- `Repeatedly` referencing the same variables have good `temporal` locality
- `Smaller strides` in reference patterns (e.g., stride-1) yield `better spatial` locality; 
  - larger strides reduce it, impacting memory access efficiency.
- `Loops` offer strong temporal and spatial locality for instruction fetches, 
  - with `smaller bodies and more iterations` improving locality.
- Understanding locality (via cache hits/misses later) helps predict performance; 
  - mastering high-level locality assessment from source code is a key programming skill.

---

## The Memory Hierarchy

- Various `storage technologies` differ in access times, 
  - with faster ones being more expensive per byte and offering less capacity, 
  - while the speed gap between CPU and main memory continues to widen.
- `Well-designed programs` typically demonstrate `good locality`, 
  - enhancing performance in memory systems.
- The complementary properties of hardware and software support the `memory hierarchy` approach, 
  - organizing storage from fast, small CPU registers to slower, larger remote disks.
- Storage devices in the hierarchy decrease in speed and cost while increasing in size, 
  - from CPU registers and SRAM-based caches to DRAM-based main memory, local disks, and remote network-accessible disks like those in distributed file systems or on the Web.

![memory hierarchy](../mod0/imgs/memhier.png)

---

## Caching in the Memory Hierarchy

- A `cache` is a small, fast storage device that temporarily `holds data` from a larger, slower device, a process called `caching`.
- In a memory hierarchy, each `level k (faster, smaller) caches data for level k + 1 (slower, larger)`, from CPU registers down to remote disks.
  - Data at level k + 1 is split into `blocks` (fixed or variable size), with level k caching a subset of these blocks.
  - Data moves between levels in `block-size` units, with block sizes varying across hierarchy pairs—smaller near the CPU, larger lower down.
  - Lower hierarchy levels have longer access times, using larger blocks to offset this delay.

---

## Cache Hits and Misses

- When a program `finds needed data in level k’s cache`, it’s a `fast cache hit`.
  - If data isn’t in level k, a `miss` occurs, prompting a fetch from level k + 1,
    - possibly `evicting or replacing` a block.
  - **Replacement Policy**: Evicted blocks (`victims`) are chosen by policies like `random` or `least recently used (LRU)`.
  - **Cold Misses**: Misses in an `empty (cold) cache` are `compulsory`, often `transient` until the cache warms up.
- **Placement Policy**: Hardware caches `restrict block placement` to balance speed and cost.
  - **Conflict Misses**: Restrictive placement causes misses when `data maps to the same block`, despite cache size.
- **Capacity Misses**: Occur when a `working set` exceeds cache size, overwhelming it during phases like loops.

---

## Cache Management

- Each memory hierarchy level caches the next, managed by `hardware, software, or both`.
  - 🍎 Compilers handle CPU registers, hardware manages L1-L3 caches, OS and CPU hardware manage DRAM, and [memcached](https://memcached.org/) manages memory objects across computers.
  - Caches are `ubiquitous`, integral to CPU chips, OS, distributed file systems, and the web, using varied hardware/software combos.
  - Caches typically operate `automatically`, requiring no explicit program action.
- **Locality Benefits**: 
  - `Temporal locality` enables fast hits after an initial miss; 
  - `Spatial locality` amortizes block fetch costs across multiple data objects.
- **Caching principle**: Caching works because slower storage is cheaper, and locality boosts performance.
- 🔭 The ubiquity of [caching](https://en.wikipedia.org/wiki/Cache_hierarchy) in modern computer systems

| **Type**| **What Cached**    | **Where Cached**    | **Latency (cycles)** | **Managed By**    |
|---|---------|----------|------|--------|
| CPU registers| 4-byte or 8-byte words  | On-chip CPU registers    | 0| Compiler    |
| TLB| Address translations    | On-chip TLB    | 0| Hardware MMU|
| L1 cache| 64-byte blocks| On-chip L1 cache    | 4| Hardware    |
| L2 cache| 64-byte blocks| On-chip L2 cache    | 10    | Hardware    |
| L3 cache| 64-byte blocks| On-chip L3 cache    | 50    | Hardware    |
| Virtual memory    | 4-KB pages    | Main memory    | 200   | Hardware + OS    |
| Buffer cache | Parts of files| Main memory    | 200   | OS|
| Disk cache   | Disk sectors  | Disk controller| 100,000    | Disk controller firmware   |
| Network cache| Parts of files| Local disk| 10,000,000 | NFS client  |
| Browser cache| Web pages| Local disk| 10,000,000 | Web browser |
| Web cache    | Web pages| Remote server disks | 1,000,000,000   | Web proxy server |

---

## Generic Cache Memory Organization

- Use $`S=2^s`$ `cache sets` to cache $`M=2^m`$ memory units (bytes by default)
- Each `cache set` consists of $`E`$ `cache lines`
- Each `cache line` = a `valid` bit ‖ $`t=m-(s+b)`$ `tag` bits ‖ a `data block` of $`B=2^b`$ bytes
- then, a cache's organization is represented by the tuple $`(S,E,B,m)`$
  - with `capacity` $`C=S×E×B`$ bytes and `overhead` $`S×(1+t)`$ bits
  - $`t=m-(s+b) → m=t+s+b`$: the `m` bits memory address is partitioned into `t-bits tag ‖ s-bits set index ‖ b-bits block offset`

---

## Direct-mapped Caches

- A direct-mapped caches has exactly `one line per set`, i.e. $`E=1`$
- **Cache Access Process: CPU ⇄ L1 Cache ⇄ Main memory**
  - When the CPU requests a `memory` word at address `A`, the L1 cache checks if it's stored (`hit`) or must fetch it from main memory (`miss`), storing it for future accesses.  
- **Set Selection:** 
  - The `set index bits from the address` determine `which set` in the cache should be accessed.  
- **Line Matching:** 
  - The cache checks if the selected set contains the requested word by comparing the `tag` bits and verifying the `valid` bit.  
- **Word Selection:** 
  - If there's a cache `hit`, the `block offset bits` identify the `starting` position of the requested word within the block.  
- **Line Replacement:** 
  - On a cache `miss`, the `new block replaces the existing one` in the direct-mapped cache, as each set has only one line.  

---

## `Conflict Misses` in Direct-Mapped Caches

- Occur when `arrays map to the same cache set`, as in a dot product function with vectors x and y.

  ```c
  float dotprod(float x[8], float y[8])
  {
      float sum = 0.0;
      int i;
      for (i = 0; i < 8; i++)
          sum += x[i] * y[i];
      return sum;
  }
  ```
- With x and y (4-byte floats) in contiguous memory, a 32-byte cache with two sets maps x[i] and y[i] to the same set, causing repeated misses and `thrashing`.
  - That a cache `repeatedly loads and evicts` the same sets of cache blocks in a short period is called `thrashing`.
  - Thrashing leads to constant block evictions, slowing execution by a factor of 2 or 3 despite good spatial locality.
- **Solution with Padding**: Adding padding (e.g., extending x from 8 to 12 elements) shifts y’s addresses, mapping x[i] and y[i] to different sets, eliminating conflict misses.

---

## Set Associative Caches
 
- Unlike direct-mapped caches (E = 1), `set associative caches` (1 < E < C/B) allow each set to hold multiple lines, reducing conflict misses.
  - often called `E-way` set associative cache.
- **Set Selection**: 
  - Identical to direct-mapped caches, using `set index bits` to identify the target set.
- **Line Matching and Word Selection**: 
  - Involves `checking tags and valid bits` across multiple lines in a set, 
    - treating the set as an `associative memory` to find a matching block, 
    - then using `block offset` for word selection.
- **Line Replacement on Misses**: 
  - the cache fetches the block and replaces a line
    - preferably an `empty` one
    - or uses policies like `random`, `least frequently used (LFU)`, or `least recently used (LRU)` to minimize future misses.

---

## Fully Associative Caches

- Consist of `one set (E = C / B)` holding all cache lines.
- **Set Selection**: 
  - Trivial since there’s only one set; 
  - addresses `lack set index bits`, containing just a `tag and block offset`.
- **Line Matching and Word Selection**: 
  - searches all lines in the single set for a matching `tag`, 
  - then uses `block offset` to select the word.
- **Limitations and Use**: 
  - Expensive and complex due to parallel tag searches, 
  - making fully associative caches suitable only for small, fast caches like `TLBs` in virtual memory systems.

---

## Issues with Writes

- **Write Hits**: 
  - `Write-through` updates the next level immediately, causing bus traffic;
  - `write-back` defers updates until eviction, 
    - reducing traffic but adding complexity with a dirty bit.
- **Write Misses**: 
  - `Write-allocate` fetches the block into the cache before updating; 
    - typically used by `write-back`
  - `no-write-allocate` writes directly to the next level, 
    - typically used by `write-through`
- **Write Optimization Complexity**: 
  - Write strategies vary across systems, often proprietary; 
  - `lower-level caches favor write-back` due to larger transfer times,
    - a trend increasing with modern systems.
- **Programmer Guidance**: 
  - Assume `write-back, write-allocate caches` for cache-friendly coding, 
  - as they exploit locality symmetrically to reads, aligning with current trends.

---

## Anatomy of a Real Cache Hierarchy

- Modern processors use separate `i-caches` (instructions only) and `d-caches` (data only), 
  - alongside `unified` caches (both instructions and data).
- Separate i-caches and d-caches allow `simultaneous` instruction and data reads,
  - reduce conflict misses, and enable tailored optimizations, 
    - though capacity misses may increase.
- **Core i7 Hierarchy**: 
  - Each Core i7 CPU chip has four cores, 
    - each with private L1 i-cache, L1 d-cache, and L2 unified cache, 
    - plus a shared on-chip L3 unified cache, all using SRAM.
  - ⚒️ Explore the CPU cache of your laptop with [CPU-Z](https://www.cpuid.com/softwares/cpu-z.html)

---

## Evaluating Cache Performance

- **Miss Rate**: Fraction of memory references that miss, calculated as `#misses/#references`.
  - **Miss Penalty**: Additional time due to a miss, 
    - e.g., ~10 cycles from L2, ~50 cycles from L3, and ~200 cycles from main memory.
- **Hit Rate**: Fraction of memory references that hit, computed as `1 - miss rate`.
  - **Hit Time**: Time to deliver a cached word to the CPU, 
    - including set selection, line identification, and word selection, 
    - typically several clock cycles for L1 caches.
- **Performance Trade-offs**: 
  - Optimizing cache performance involves `complex cost-benefit analysis`, 
  - typically assessed through `simulations on benchmark codes`.

---

## Performance Impact of Cache Parameters

- **Cache Size**: Larger caches improve hit rates but increase hit times, so L1 < L2 < L3 in size.
- **Block Size**: Larger blocks boost hit rates via spatial locality but may hurt temporal locality and raise miss penalties.
  - e.g., 64 bytes in Core i7
- **Associativity**: Higher associativity cuts conflict misses but raises complexity, hit time, and miss penalty.
  - e.g., 8-way for L1/L2, 16-way for L3 in Core i7
- **Write Strategy**: 
  - Write-through lowers read miss costs but increases traffic; 
  - write-back reduces transfers, suiting lower hierarchy levels.

---

## Writing Cache-Friendly Code

- **Optimize Inner Loops:** 
  - Focus on optimizing the `inner loops of frequently used` functions, 
  - as reducing cache misses in these loops significantly improves performance.  
- **Leverage Temporal Locality:** 
  - `Repeatedly accessed local variables` are cache-friendly because they can be stored in registers or higher cache levels.  
- **Utilize Spatial Locality:** 
  - Accessing memory in a **stride-1** pattern (sequential access) improves cache efficiency since caches store data in `contiguous` blocks.  
- **Beware of Column-Major Access:** 
  - Scanning a 2D array **column-wise** instead of **row-wise** can drastically increase cache misses, leading to poor performance.

---

## The Memory Mountain

- A `visualization` of a system’s memory performance of varying throughput based on cache hierarchy and access patterns, 
  - with `peaks` at cache-`efficient` regions and `valleys` at `inefficient` ones.  
- ⚒️ Generate the [memory mountain of your computer](./code/mh/mountain/)
- ⚒️ [Rearranging loops](./code/mh/matmult/) to increase spatial locality

---

# References
- *Cache simulators*
  - [Fish and MIPS' Cache Simulator](https://dtv96calibre.github.io/cacheSim/)
  - [ParaCache](https://www3.ntu.edu.sg/home/smitha/ParaCache/Paracache/dmc.html)
  - [351 Cache Simulator](https://courses.cs.washington.edu/courses/cse351/cachesim/)
  - [370 simulator](https://vhosts.eecs.umich.edu/370simulators/cache/simulator.html)
  - [cs351 simulator](https://rivoire.cs.sonoma.edu/cs351/cachesim/)
- [RISC-V](https://riscv.org/)