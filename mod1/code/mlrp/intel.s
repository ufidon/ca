.intel_syntax noprefix   # Use Intel syntax without register prefixes
.section .data
message:
    .asciz "Hello, World!\n"  # Null-terminated string

.section .text
.global _start   # Declare _start as a global symbol

_start:
    mov rax, 1            # syscall: write (64-bit)
    mov rdi, 1            # file descriptor: stdout
    lea rsi, [rip + message]  # pointer to message (RIP-relative addressing)
    mov rdx, 14           # message length
    syscall               # Invoke the syscall

    mov rax, 60           # syscall: exit (64-bit)
    xor rdi, rdi          # exit code 0
    syscall               # Invoke the syscall
    