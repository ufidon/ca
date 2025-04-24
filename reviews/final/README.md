# Final Review
- Covers mod 2

---

## Y86-64 ISA and sequential implementation

- What are the shortest instructions in Y86-64?
  - What are their encoding?
- What are the longest instructions in Y86-64 and their encoding?
- What instructions update the condition codes?
  - What instructions depend on these condition codes?
- What are the stack operation instructions?
  - What do they do during their `execution` stage?

---

## Y86-64 pipeline implementation

- What is the effect of pipelining on task throughput and latency?
- What is `load/use` data hazard?
  - How to solve it?
- When will control hazard occur and how to solve it?
- What are the exceptions in Y86?
  - How to handle them?
- Given an unpipelined system with computation logic that takes 200ps, and 20ps to load registers:
  - What is the latency in ps? What is the throughput in GIPS?
  - If it can be evenly divided into a 5 stage pipeline,
    - What is the new latency in ps? What is the new throughput in GIPS?

---

## The memory hierarchy

- What are the three types of cache associativity?
  - How to determine a cache line in each type?
- How to handle issues with writes?
- What is the locality of instruction fetches?
- How to write cache-friendly code?
- What are the cache misses and their causes?
- What are the cache misses in direct-mapped cache?
  - What causes them? Can they be avoided and how?
- Given a cache of size 32KB with block size of 64B, it's organized as (S,E,B), 
  - where S is the number of sets, E is the number of cache lines per set, and B is the block size. Note: B in those numbers means byte. 1KB=1024B
  - find the values of (S,E) for each of the following associativity:
    - direct-mapped cache: E=1, S=C/B
    - 8-way set associativity cache: E=8, S=C/(E×B)
    - fully associative cache: S=1, E=C/B
- Given an address A, how to find the data pointed by A in a cache?
  - set index → valid bit ‖ tag → block offset
  - refer to [Generic Cache Memory Organization](https://github.com/ufidon/ca/blob/main/mod2/mh.md)

---

## Virtual memory

- How to locate the page table of a process?
- What will happen during a TLB hit? a TLB miss?
  - Will a TLB miss cause a page fault?
- What is the main purpose of a multi-level page table?
- How does VM work as a tool for memory protection?
- How does VM work as a tool for memory management?
- What is demand paging?
- What is the cause of thrashing?
  - How to mitigate it?
- Given a `page table (PPN ↔ VPN)`
  - N = 2ⁿ	Number of addresses in virtual address space
  - M = 2ᵐ	Number of addresses in physical address space
  - P = 2ᵖ	Page size (bytes)
  - How to convert a virtual address to a physical address?
    - VA = VPN ‖ VPO, PA = PPN ‖ PPO, VPO=PPO
    - look for PPN in the page table given VPN

---

## Exceptional control flow
- What are the differences between instruction `syscall` vs. `int 0x80`?
- How are exception handled?
  - What are the three resolution paths in exception handling?
- How do Unix systems report system call errors?
- What are the differences between `fork()` vs. `execve()`?
- How to implement signal handlers?
- What are the popular signals, their usages, and their handling?

---

## Optimizing program performance

- What is loop unrolling?
  - What are its advantages and limits?
- What are the capabilities and limitations of optimizing compilers?
- What is the usage of accumulator?
  - What factor limits the usage of multiple accumulators?
- What are the performance improvement techniques?
- How to utilize memory performance?