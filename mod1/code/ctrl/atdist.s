# as -o atdist.o atdist.s
# ld -o atdist atdist.o

    .section .text
    .globl _start
    .globl dist

_start:

dist:
    # rval = y - x
    movq %rsi, %rax       # Move y (%rsi) to %rax
    subq %rdi, %rax       # Subtract x (%rdi) from %rax

    # eval = x - y
    movq %rdi, %rdx       # Move x (%rdi) to %rdx
    subq %rsi, %rdx       # Subtract y (%rsi) from %rdx

    # Compare x and y
    cmpq %rsi, %rdi       # Compare x (%rdi) with y (%rsi)
    cmovge %rdx, %rax     # If x >= y, move eval (%rdx) to rval (%rax)

    # Return rval
    ret                   # Return the result in %rax
