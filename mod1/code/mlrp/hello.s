.section .data
message:
    .asciz "Hello, World!\n"

.section .text
.globl _start

_start:
    movq $1, %rax             # syscall: write
    movq $1, %rdi             # file descriptor: stdout
    lea message(%rip), %rsi   # pointer to message
    movq $14, %rdx            # message length
    syscall

    movq $60, %rax            # syscall: exit
    xor %rdi, %rdi            # exit code 0
    syscall
