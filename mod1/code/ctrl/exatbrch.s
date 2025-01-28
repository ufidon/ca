    .section .text
    .globl _start
    .globl dist

_start:

# long arith(long x)
# x in %rdi
arith:
    leaq    7(%rdi), %rax   # %rax = x + 7
    testq   %rdi, %rdi      # Test if x is negative
    cmovns  %rdi, %rax      # If x >= 0, %rax = x
    sarq    $3, %rax        # %rax = %rax >> 3 (arithmetic shift right by 3)
    ret                     # Return %rax

# long test(long x, long y)
# x in %rdi, y in %rsi
test:
    leaq    0(,%rdi,8), %rax  # %rax = 8 * x
    testq   %rsi, %rsi        # Test if y <= 0
    jle     .L2               # If y <= 0, jump to .L2
    movq    %rsi, %rax        # %rax = y
    subq    %rdi, %rax        # %rax = y - x
    movq    %rdi, %rdx        # %rdx = x
    andq    %rsi, %rdx        # %rdx = x & y
    cmpq    %rsi, %rdi        # Compare x and y
    cmovge  %rdx, %rax        # If x >= y, %rax = %rdx (x & y)
    ret                       # Return %rax
.L2:
    addq    %rsi, %rdi        # %rdi = x + y
    cmpq    $-2, %rsi         # Compare y with -2
    cmovle  %rdi, %rax        # If y <= -2, %rax = %rdi (x + y)
    ret                       # Return %rax    
    