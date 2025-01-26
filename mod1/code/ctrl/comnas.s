; yasm -f elf64 -o comnas.o comnas.s
; ld -o comnas comnas.o
; ./comnas
; echo $?

section .data
    ; Define two long values for comparison
    a dq 10  ; a = 10
    b dq 20  ; b = 20

section .text
global _start

_start:
    ; Load values into registers
    mov rdi, [a]  ; Load a into rdi
    mov rsi, [b]  ; Load b into rsi

    ; Compare a and b
    cmp rdi, rsi  ; Compare a (rdi) and b (rsi)

    ; Set al to 1 if a < b, otherwise 0
    setl al       ; Set lower byte of rax based on comparison

    ; Zero-extend al to eax (and clear upper bytes of rax)
    movzx eax, al ; Move byte to 32-bit register, zero-extending

    ; Exit the program with the result as the exit code
    ; Use the lower 8 bits of eax as the exit status
    movzx edi, al ; Move the result (0 or 1) into edi (exit status)
    mov rax, 60   ; syscall: exit
    syscall