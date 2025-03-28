# Virtual memory
CS:APP3e.ch09

---

## Overview of virtual memory

- **Challenges of Shared Memory**: 
  - Sharing CPU and main memory among processes can lead to slowdowns or failures if memory demand exceeds availability, 
  - memory corruption can occur if processes overwrite each other's data.  
- **Virtual Memory (VM) Benefits**: 
  - VM abstracts main memory, providing efficiency (caching active data), simplicity (uniform address space), and protection (isolation between processes).  
- **VM's Automated Efficiency**: 
  - VM works silently, dynamically transferring data between disk and memory,
  - optimizing resource use without programmer intervention.  
- **Importance of Understanding VM**: 
  - VM is central to system design (hardware, files, processes), 
  - powerful (enables memory mapping, file manipulation, and sharing), 
  - and dangerous (misuse leads to bugs like crashes or silent errors). 
- **Memory-Related Risks**: 
  - Improper memory handling (e.g., bad pointers) can cause crashes, subtle bugs, or incorrect results, 
  - underscoring the need to grasp VM and tools like `malloc`.

---

# Physical and Virtual Addressing

- **Physical memory**: Contiguous byte array accessed via direct physical addresses (PA).  
- **Virtual memory**: CPUs use virtual addresses (VA), translated to PAs for access.  
- **MMU**: Hardware (Memory Management Unit) converts VAs to PAs via OS-managed tables.  
- **Advantage**: Virtual memory enables isolation, protection, and flexible memory management.

---

## Address Spaces

- `Address space` is an ordered set of consecutive integer addresses
  - e.g., {0, 1, 2, ...}
  - Virtual memory uses an *n*-bit virtual address space with size *N* = 2ⁿ.  
- `Address space size` is determined by bits needed for the `largest` address
  - e.g., 32-bit or 64-bit virtual address spaces in modern systems.  
- `Physical` address space corresponds to `actual` memory with size $`M=2^m`$ 
  - while virtual address space provides an abstraction for processes.   
- `Virtual` memory enables multiple addresses (virtual & physical) for data objects,
    - separating data from addressing for flexibility and protection.

---

## VM as a Tool for Caching

- `Virtual Memory` is organized as an array of *N* contiguous `byte-sized cells` on disk, 
  - each addressable by a `unique` virtual address.  
- VM acts as a `cache`, 
  - with `disk blocks (virtual pages)` loaded into `physical memory (physical pages)` as needed.  
- Virtual pages (VPs) and physical pages (PPs) are `fixed-size blocks (*P* bytes)`. VPs are divided into:  
  - *Unallocated*: Not yet created (no disk space used).  
  - *Cached*: Allocated and currently in physical memory.  
  - *Uncached*: Allocated but not in physical memory (stored on disk).  
- VM Enables efficient memory use by only caching active pages, 
  - while unused or less-frequent pages remain on disk.

---

### DRAM Cache Organization

- **Cache Terminology**:  
  - *SRAM cache*: Refers to L1, L2, L3 CPU caches (fast, backed by DRAM).  
  - *DRAM cache*: Virtual memory’s cache in main memory (slow, backed by disk).  
- **DRAM Cache Challenges**:  
  - Misses are extremely costly (disk access ≈100,000× slower than DRAM).  
  - First-byte disk access is disproportionately slow, favoring large virtual pages (4KB–2MB).  
- **Fully Associative Design**:  
  - Any virtual page can map to any physical page to minimize misses.  
- **Sophisticated Replacement Policies**:  
  - OS uses advanced algorithms (e.g., LRU approximations) due to high miss penalties.  
- **Write-Back Strategy**:  
  - Always used (vs. write-through) to avoid frequent, costly disk writes.

---

### Page Tables

- `Page tables ` maps virtual pages to physical pages in DRAM, 
  - tracking cached/uncached pages via `PTEs (Page Table Entries)` with valid bits and address fields.  
- `MMU` hardware uses the page table to convert virtual addresses to physical addresses, 
  - with OS managing table updates and page transfers between disk/DRAM.  
- Each PTE contains `a valid bit (cached/uncached)` and `an address field` (DRAM location or disk storage), with null addresses for unallocated pages.  
- **Fully Associative Cache**: Any virtual page can reside in any physical page.

---

### Page Caching
- `Page hit` occurs when CPU accesses a cached virtual page, 
  - the MMU uses its PTE to construct the physical address from the valid bit and stored DRAM location.  
- `Page fault` occurs when accessing an uncached virtual page. 
  - The MMU triggers an `exception`, invoking the OS handler to fetch the page from disk.  
  - **Fault Handling**: 
    - The OS selects a `victim` page, writes it back to disk if modified, 
    - loads `VP n` into DRAM, updates `PTE n`, and restarts the faulting instruction.  
- **Terminology**:  
   - *Pages*: Virtual memory blocks (vs. cache "lines").  
   - *Swapping/Paging*: Moving pages between disk and DRAM.  
   - *Demand Paging*: Loading pages only on fault (standard in modern systems).  
- **Page Allocation**: 
  - New virtual pages, via `malloc`, are allocated on disk, 
  - with PTEs updated to point to their disk locations.  
- **Locality Saves Efficiency**: 
  - Programs’ `*working sets* (active pages)` tend to be small due to temporal locality, 
  - keeping most accesses in DRAM after initial loading.  
- **Thrashing Risk**: Poor locality or oversized working sets cause constant swapping, crippling performance.  
- **DRAM as Cache**: Fully associative, large pages (4KB–2MB), and write-back policies minimize costly disk accesses.  
- **Historical Context**: Virtual memory predates SRAM caches, leading to distinct terminology but similar principles (e.g., demand paging ≈ cache miss handling).  
- **Performance Insight**: 
  - Virtual memory works efficiently *because* of locality; 
  - thrashing signals a need to optimize memory access patterns or increase physical memory.

---

# VM as a Tool for Memory Management

- **Process Isolation**: 
  - Each process gets its own virtual address space and page table, 
  - preventing unauthorized access to other processes' memory.  
- **Memory Mapping**: 
  - Files can be mapped directly into virtual memory, 
  - enabling efficient file I/O and demand paging.  
- **Shared Libraries**: 
  - Common code (like C standard libraries) can be shared across processes by mapping to the same physical pages.  
- **Flexible Allocation**: 
  - Virtual memory allows non-contiguous physical pages to back contiguous virtual pages, 
  - simplifying dynamic memory allocation.  
- **Simplified Linking**: 
  - Programs use fixed virtual addresses for segments, 
  - making executables position-independent.  
- **On-Demand Loading**: 
  - Pages load lazily (only when accessed), 
  - reducing startup overhead and memory waste.  
- **Early Adoption**: 
  - Even systems with limited virtual address spaces (like PDP-11) used VM for memory protection and management benefits.

---

# VM as a Tool for Memory Protection

- Virtual memory `enforces access control` via `permission` bits in PTEs (SUP, READ, WRITE), 
  - preventing unauthorized reads/writes to kernel/other processes' memory.  
- **Kernel/User Mode Isolation**: 
  - SUP(supervisor) bit restricts privileged (kernel-mode) pages to the OS, 
  - user-mode processes can only access pages with `SUP=0`.  
- **Segmentation Faults**: 
  - Violations trigger CPU exceptions (e.g., SIGSEGV), 
  - reported as "segmentation faults" to prevent illegal memory access.  
- **Fine-Grained Control**: 
  - PTEs enable per-page permissions 
  - e.g., read-only code sections, shared writable pages with explicit IPC consent.  
- **Natural Extension of VM**: 
  - Address translation hardware inherently supports protection by validating permissions on every memory access.

---

#  Address Translation

- `Address translation` maps virtual addresses (VAS) to physical addresses (PAS) using page tables, with unmapped pages flagged as absent.
- `MMU hardware` uses a `page table base register (PTBR)` to locate the current page table and splits virtual addresses into `VPN (page number) and VPO (offset)`.
- **Page Hit Flow**: 
   - CPU sends VA to MMU → MMU fetches PTE → Constructs PA → Retrieves data from memory (all hardware-handled).
- **Page Fault Handling**: 
   - MMU detects invalid PTE → Triggers exception → OS handler selects victim page → Swaps in new page → Updates PTE → Restarts instruction.
- **Physical Address Construction**: Combines PPN (from PTE) and VPO to form PA, leveraging fixed page sizes (PPO = VPO).
- **Hardware-OS Cooperation**: Page hits are pure hardware; faults require OS intervention for disk I/O and PTE updates.
- **Efficiency Focus**: Translation optimizations (like caching PTEs) hide latency.

| **Category**| **Symbol** | **Description** |
|-----|---|-------|
| **Basic Parameters**  | N = 2ⁿ | Number of addresses in virtual address space  |
|   | M = 2ᵐ | Number of addresses in physical address space|
|   | P = 2ᵖ | Page size (bytes)  |
| **Virtual Address (VA)** | VPN  | Virtual Page Number (indexes page table) |
|   | VPO   | Virtual Page Offset (bytes) → becomes PPO in physical address|
|   | TLBI  | TLB Index (for TLB cache lookup)   |
|   | TLBT  | TLB Tag (for TLB cache matching)   |
| **Physical Address (PA)** | PPN | Physical Page Number (from PTE)|
|   | PPO   | Physical Page Offset (bytes) = VPO |
| **Cache Addressing**  | CO| Byte Offset within cache block |
|   | CI| Cache Index (selects cache set)|
|   | CT| Cache Tag (matches cache line) |

**Notes:**  
- Page size (P) determines VPO/PPO bit length (e.g., 4KB page → 12-bit offset).  
- TLB (Translation Lookaside Buffer) caches PTEs to accelerate VPN-to-PPN translation.  
- Cache addressing (CO/CI/CT) is orthogonal to VA/PA translation but uses physical addresses.

---

## Speeding Up Address Translation with a TLB

- **Physical Cache Addressing**
  - Most systems use *physical addresses* for SRAM caches to enable process sharing and avoid protection checks (already handled during address translation).
- **Cache-VM Integration** 
  - Address translation (VA→PA) occurs *before* cache lookup, with PTEs cached like normal data.
- **TLB Purpose**
  - A `Translation Lookaside Buffer (TLB)` is an MMU-resident PTE cache that avoids costly main memory accesses for address translation.
- **TLB Operation**  
  - **Hit**: CPU → MMU (TLB) → PA → Cache/Memory → Data
    - On-chip MMU translates VA→PA in 1-2 cycles using TLB entries
  - **Miss**: CPU → MMU (TLB Miss) → L1 Cache → TLB Update → PA → Cache/Memory → Data
    - PTE fetched from L1 cache/memory and stored in TLB 
- **TLB Design** 
  - Highly associative, indexed by VPN bits (TLBI = low bits, TLBT = high bits of VPN).

---

## Multi-Level Page Tables

- **Space Efficiency Problem**  
  - Single 32-bit page tables waste memory (e.g., 4MB always resident) since most virtual address space remains unused.
- **Hierarchical Solution**  Uses tree-like page table levels:  
  - Level 1: Maps large chunks (e.g., 4MB/PTE)  
  - Level 2+: Maps smaller regions (e.g., 4KB/PTE)  
  - Null PTEs skip entire subtrees.
- **On-Demand Loading**  
  - Only Level 1 stays always resident; 
  - other levels page in/out like normal memory, reducing active footprint.
- **Address Translation Flow**  
  - VA splits into k VPNs + VPO → MMU walks k levels (PTE chains) → Combines final PPN + VPO → PA.
- **TLB Acceleration**  
  - Caches frequent multi-level PTEs, making traversal near single-level speed despite complexity.
- **Scalability**  
  - Critical for 64-bit systems where single-level tables would be impossibly large (e.g., 2^52 entries).

---

## ⚒️ Practice
Play with a [virtual memory simulator](https://courses.cs.washington.edu/courses/cse351/vmsim/)

| Component | Specification  |
|------|---------------------|
| **System Specs** | - 14-bit virtual addresses (8-bit VPN + 6-bit VPO)<br>- 12-bit physical addresses (6-bit PPN + 6-bit PPO)<br>- 64-byte pages, 1-byte memory accesses |
| **TLB Structure** | - 4-way set associative (16 entries total)<br>- 2-bit TLBI (index), 6-bit TLBT (tag)<br>- Caches VPN→PPN mappings (e.g., VPN 0x3 → PPN 0xD) |
| **Page Table**   | - Single-level with 256 PTEs (first 16 shown)<br>- Each PTE contains PPN (e.g., VPN 0x0 → PPN 0x28) |
| **Cache Structure** | - Physically addressed, direct-mapped<br>- 16 sets (4-bit CI), 4-byte blocks (2-bit CO), 6-bit CT |

- **Address Translation Flow (TLB Hit)**
  - CPU VA 0x03D4 → MMU extracts VPN 0x0F/VPO 0x14
  - TLB lookup (TLBI=0x3/TLBT=0x3) → hits → returns PPN 0x0D
  - Combines PPN 0x0D + VPO 0x14 → PA 0x354
- **Cache Access (Hit)**
  - PA 0x354 → CT=0x0D, CI=0x5, CO=0x0
  - Cache set 0x5 matches tag → returns data byte 0x36
- **TLB Miss Handling**
  - If TLB miss: MMU fetches PTE from page table in memory
  - If PTE invalid: page fault triggers OS page-in
- **Cache Miss Handling**
  - Valid PTE but cache miss → fetch block from main memory
- **Key Observations**
  - VPO = PPO due to same page size
  - Physical cache uses post-translation addresses
  - TLB avoids page table walks for frequent mappings
- **Efficiency**
  - TLB hits (like this example) avoid memory accesses
  - Cache hits avoid DRAM accesses
  - Worst case: TLB miss + page fault + cache miss = ~1M cycles

---

# ⚒️ Case Study: [The Intel Core i7/Linux Memory System](https://cdrdv2.intel.com/v1/dl/getContent/671447)

- **Address Space & Core Architecture**  
   - 48-bit virtual (256TB)/52-bit physical (4PB) spaces with 32-bit compatibility  
   - Quad-core design with shared L3 cache, DDR3 controller, and QuickPath interconnects  
- **Multi-Level Page Tables**  
   - 4-level hierarchical page tables (Linux uses 4KB pages exclusively)  
   - CR3 register stores L1 table address (process-specific), with 40-bit PPNs enforcing 4KB alignment  
- **Hardware-Enforced Security**  
   - Permission bits (R/W, U/S, XD) control access and execution rights  
   - XD bit prevents code execution in data pages to block buffer overflow exploits  
- **Translation & Tracking**  
   - MMU splits 36-bit VPN into four 9-bit offsets for table walks  
   - A/D bits track page access/dirty status for kernel page management  
- **Cache/TLB Optimization**  
   - Physically addressed caches (L1/L2 8-way, L3 16-way) with 64B blocks  
   - Virtually addressed 4-way set-associative TLBs accelerate address translation

---
---

💡 Topics to be covered in OS
---

## Linux virtual memory system

- **Process Memory Organization**  
  - Each process has a virtual address space divided into areas (code, heap, stack, etc.) with gaps between non-allocated regions.  
  - The kernel tracks these areas via `vm_area_struct` (boundaries, permissions, sharing flags) and optimizes searches with a tree structure.
- **Kernel Virtual Memory**  
  - Maps shared kernel code/data and a direct 1:1 physical memory mapping for hardware access.  
  - Maintains per-process kernel data (page tables, stacks) in separate virtual regions.
- **Page Fault Handling Pipeline**  
  - **Validation**: Checks if the faulting address belongs to a valid VMA; if not → segmentation fault.  
  - **Permission Check**: Verifies access rights (R/W/X) against VMA flags; if violated → protection fault.  
  - **Resolution**: Swaps in/out pages, updates PTEs, and restarts the faulting instruction.
- **Memory Sharing & Protection**  
  - Shared VMAs (e.g., libraries) use common physical pages, while private VMAs employ copy-on-write.  
  - Hardware-enforced isolation via permission bits (`vm_prot`) and user/kernel mode checks.
- **Efficiency Mechanisms**  
  - Demand paging: Loads pages only on first access.  
  - Optimized VMA lookup: Tree structure over linked list for O(log n) searches.  
  - Dirty page tracking: Minimizes disk writes during swaps.

---

# Memory Mapping

- **Memory Mapping Fundamentals**  
  - Virtual memory areas can map to either file-backed sections (executable code/data) or anonymous demand-zero pages (BSS/heap/stack).  
  - Uses demand paging: pages load only on first access, with swap space bounding total allocations.
- **Shared vs Private Mappings**  
  - **Shared**: Multiple processes map same file (e.g., libraries); changes visible across processes and written to disk.  
  - **Private**: Copy-on-write (COW) delays page duplication until writes occur, optimizing memory usage.
- **Process Lifecycle Integration**  
  - **`fork`**: Copies parent's VM structures, marking pages COW to defer physical copies.  
  - **`execve`**: Replaces VM by (1) deleting old areas, (2) mapping new executable sections, (3) linking shared libraries, and (4) setting the entry point.
- **User-Level Control (`mmap`/`munmap`)**  
  - `mmap` creates mappings with configurable permissions (`PROT_READ/WRITE/EXEC`) and flags (`MAP_SHARED`/`PRIVATE`/`ANON`).  
  - `munmap` deletes mappings, freeing virtual address space.
- **Efficiency & Optimization**  
  - COW minimizes memory duplication for private mappings.  
  - Shared mappings reduce disk I/O via single physical copies of files/libraries.  
  - Anonymous mappings avoid disk access for zero-filled pages (e.g., heap/stack growth).

---

## Dynamic Memory Allocation

- **Heap Management Basics**  
   - Managed via `malloc`/`free` with kernel tracking via `brk`.  
   - Blocks are **allocated** (in use) or **free** (available), with metadata headers/footers.  
- **Allocator Types**  
   - **Explicit**: Manual freeing (C/C++).  
   - **Implicit (GC)**: Automatic reclamation (Java/Python).  
- **Core Challenges**  
   - **Fragmentation**:  
     - *Internal*: Wasted space within blocks (padding/minimum sizes).  
     - *External*: Free memory fragmented into unusable chunks.  
   - **Throughput vs. Utilization**: Balance speed (e.g., first-fit) with memory efficiency (e.g., best-fit).  
- **Placement Policies**  
   - **First-fit**: Fast but may leave small gaps.  
   - **Best-fit**: Better utilization but slower (exhaustive search).  
   - **Splitting**: Divides free blocks to fit requests; avoids wasting large blocks.  
- **Coalescing Strategies**  
   - Merges adjacent free blocks to combat fragmentation.  
   - **Boundary tags**: Headers/footers enable O(1) merging (Knuth’s method).  
   - **Immediate vs. Deferred**: Trade-offs between thrashing and fragmentation.  
- **Heap Expansion & Allocation**  
   - Calls `sbrk` to grow heap when no blocks fit.  
   - Blocks aligned to 8B/16B, with headers storing size/status (e.g., allocated bit).  
- **Optimizations**  
   - **Footer elimination**: Omit footers in allocated blocks to reduce overhead.  
   - **Free lists**: Explicit structures (vs. implicit lists) speed up searches.  
- **Common Pitfalls**  
   - **False fragmentation**: Adjacent small free blocks fail larger requests.  
   - **Invalid `free`**: Undefined behavior if pointers are incorrect.  
- **Real-world Allocators**  
   - **dlmalloc**: General-purpose.  
   - **jemalloc/tcmalloc**: Optimized for multithreading.  
- **Key Trade-offs**  
    - **Metadata overhead**: Headers/footers vs. block reuse efficiency.  
    - **Policy choices**: Speed (first-fit) vs. memory use (best-fit, coalescing).  

---

## ⚒️ Putting It Together: Implementing a [Simple Allocator](./code/vm/malloc/)

- **Core Design & Initialization**  
   - Uses an implicit free list with boundary tags (headers/footers) for O(1) coalescing.  
   - Initializes heap with prologue/epilogue blocks to simplify edge cases.  
   - `mm_init` sets up initial heap structure and expands it via `extend_heap`.
- **Block Management**  
   - Minimum block size = 16 bytes (header + footer + alignment).  
   - Macros (`HDRP`, `FTRP`, `NEXT_BLKP`) handle pointer arithmetic for block navigation.  
   - Maintains global `heap_listp` pointing to prologue for invariant checks.
- **Allocation Logic (`mm_malloc`)**  
   - Adjusts requested size (adds overhead, rounds to 8B) and searches free list.  
   - Splits blocks if remainder ≥ 16B; else extends heap via `extend_heap`.
- **Free & Coalescing (`mm_free`)**  
   - Marks blocks free and merges adjacent free blocks using boundary tags.  
   - Handles 4 coalescing cases (both neighbors allocated/free) in constant time.
- **Key Optimizations & Trade-offs**  
   - Prologue/epilogue blocks eliminate edge-condition checks.  
   - Immediate coalescing reduces fragmentation but may thrash.  
   - Trade-offs: Simplicity (implicit list) vs. speed (O(n) searches).  

---

## Explicit Free List & Segregated Free Lists

- **Explicit Free List Optimization**  
   - Replaces implicit list scanning with a doubly linked free list for O(1) freeing (LIFO) or O(n) freeing (address-ordered).  
   - Trade-off: LIFO prioritizes speed, while address-ordering improves memory utilization near best-fit levels.  
   - Requires larger minimum block size (stores predecessor/successor pointers in free blocks).
- **Segregated Free Lists (General Approach)**  
   - Partitions heap into size classes (e.g., powers of 2 or custom ranges) with dedicated free lists per class.  
   - Reduces search time by limiting scans to relevant size classes.  
   - Segregated fits (variable blocks per class) approximate best-fit; simple segregated (fixed blocks) enables O(1) ops but sacrifices fragmentation control.
- **Simple Segregated Storage**  
   - Each size class contains equal-sized blocks (largest in class).  
   - Pros: Zero overhead (no headers), O(1) alloc/free, ideal for fixed-size requests.  
   - Cons: Severe external fragmentation (no coalescing) and internal fragmentation (no splitting).
- **Buddy System (Power-of-2 Variant)**  
   - Specialized segregated allocator where size classes are powers of 2.  
   - Splits/merges blocks recursively via buddy addressing (O(1) coalescing via bit-flip calculation).  
   - Fast but suffers from internal fragmentation; suited for GPU/texture allocators.
- **Production Allocator Strategies**  
   - Modern allocators (e.g., GNU malloc, jemalloc) use hybrid approaches:  
     - Segregated fits for balance of speed and utilization.  
     - Combined with thread-local caches to reduce contention.  
   - Key insight: Segregation approximates best-fit without global heap scans.  

---

## Garbage Collection

- **Core Concept & Purpose**  
   - Automatically reclaims unreachable heap blocks ("garbage") without manual `free`, crucial for languages like Java/Lisp.  
   - Uses a `reachability graph`: 
     - Roots (stack/global vars) point to heap blocks; 
     - unreachable nodes are garbage.  
- **Mark&Sweep Algorithm**  
   - **Mark phase**: Recursively traces pointers from roots, marking reachable blocks (using header bits).  
   - **Sweep phase**: Scans heap to free unmarked blocks, resetting marks for future cycles.  
- **Challenges in C/C++ (Conservative GC)**  
   - No type tags: Integers may mimic pointers, causing `overmarking` (retaining some garbage).  
   - Requires block metadata (headers/trees) to track boundaries, adding overhead.  
- **Integration & Trade-offs**  
   - Runs when `malloc` fails, reclaiming garbage before requesting OS memory.  
   - Pros: Prevents leaks; cons: Cannot compact (fragmentation risk) and may overmark.  
- **Practical Applications & Evolution**  
   - Used in [Boehm GC](https://www.hboehm.info/gc/) for C/C++; contrasts with exact collectors (Java/ML).  
   - Modern optimizations: Parallel marking, generational GC for reduced pauses.  

---

## Common Memory-Related Bugs in C Programs

- **Invalid Memory Access**  
   - *Dereferencing bad pointers* (e.g., unmapped addresses, `scanf("%d", val)`).  
   - *Use-after-free* (accessing freed heap blocks) and *dangling pointers* (references to expired stack variables).  
- **Buffer Overflows & Size Miscalculations**  
   - *Stack buffer overflows* (e.g., unsafe `gets(buf)`).  
   - *Off-by-one errors* (writing past array bounds) and *pointer arithmetic mistakes* (e.g., `p += sizeof(int)` instead of `p++`).  
- **Allocation/Deallocation Errors**  
   - *Memory leaks* (forgetting `free`), *double-free* (corrupting allocator metadata), and *mismatched alloc/free* (e.g., `new`/`delete[]` mismatch).  
   - *Zero-length allocations* (`malloc(0)`) and *integer overflows* in size calculations.  
- **Pointer Misuse & Type Confusion**  
   - *Pointer vs. object size* (e.g., `sizeof(int)` vs. `sizeof(int*)`).  
   - *Incorrect precedence* (e.g., `*size--` decrements the pointer, not the value).  
   - *Type casting errors* (e.g., aliasing violations with `int*` to `float*`).  
- **Uninitialized/Stale Data**  
   - *Reading uninitialized heap memory* (assumed zero-initialization).  
   - *Referencing reallocated/resized memory* (e.g., stale pointers after `realloc`).  
- **Why These Matter**  
  - **Silent Corruption**: Bugs like use-after-free or pointer arithmetic errors often crash *later*, making debugging hard.  
  - **Security Risks**: Buffer overflows and bad pointers are exploit vectors (e.g., code injection).  
  - **Prevention**: Use tools (`valgrind`, ASan), defensive coding, and automated checks.  

---


# References
- [351 VM Simulator](https://courses.cs.washington.edu/courses/cse351/vmsim/)
- [ParaCache Simulator](https://personal.ntu.edu.sg/smitha/ParaCache/Paracache/start.html)
