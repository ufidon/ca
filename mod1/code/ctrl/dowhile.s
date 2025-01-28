# long fact_do(long n)
# n in %rdi
fact_do:
    movl $1, %eax          # Set result = 1
.L2:                       # loop:
    imulq %rdi, %rax       # Compute result *= n
    subq $1, %rdi          # Decrement n
    cmpq $1, %rdi          # Compare n:1
    jg .L2                 # If n > 1, goto loop
    rep; ret               # Return

# long dw_loop(long x)
# x initially in %rdi
dw_loop:
    movq %rdi, %rax        # Copy x to %rax (result)
    movq %rdi, %rcx        # Copy x to %rcx
    imulq %rdi, %rcx       # Compute y = x * x (stored in %rcx)
    leaq (%rdi,%rdi), %rdx # Compute n = 2 * x (stored in %rdx)
.L3:
    leaq 1(%rcx,%rax), %rax # x += y + 1
    subq $1, %rdx          # Decrement n
    testq %rdx, %rdx       # Test if n > 0
    jg .L3                 # If n > 0, goto loop
    rep; ret               # Return
    