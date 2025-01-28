; yasm -f elf64 goto.s -o goto.o

section .text
    global _start
    global _test

_start:
    ; nop

; long test(long x, long y, long z) 
; x in %rdi, y in %rsi , z in %rdx

_test:
    lea rax, [rdi + rsi]
    add rax, rdx
    cmp rdi, -3
    jge .L2
    cmp rsi, rdx
    jge .13
    mov rax, rdi
    imul rax, rsi
    ret
.13:
    mov rax, rsi
    imul rax, rdx
    ret
.L2:
    cmp rdi, 2
    jle .14
    mov rax, rdi
    imul rax, rdx
.14:
    rep ret

