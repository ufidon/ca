    .global test      # Declare test as a global symbol
    .text             # Switch to text section

; long test(long x, long y, long z) 
; x in %rdi, y in %rsi , z in %rdx

test:
    leaq (%rdi,%rsi), %rax
    addq %rdx, %rax
    cmpq $-3, %rdi
    jge .L2
    cmpq %rdx, %rsi
    jge .13
    movq %rdi, %rax
    imulq %rsi, %rax
    ret

.13:
    movq %rsi, %rax
    imulq %rdx, %rax
    ret

.L2:
    cmpq $2, %rdi
    jle .14
    movq %rdi, %rax
    imulq %rdx, %rax

.14:
    rep ret
