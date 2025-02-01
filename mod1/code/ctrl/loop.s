section .data
    msg1 db 'Basic loop: ', 10
    len1 equ $ - msg1
    msg2 db 'JRCXZ demo:', 10
    len2 equ $ - msg2
    char db '*'
    newline db 10

section .text
    global _start

_start:
    ; Print initial message
    mov rax, 1          ; write syscall
    mov rdi, 1          ; stdout
    mov rsi, msg1
    mov rdx, len1
    syscall

    ; Basic LOOP demonstration
    mov rcx, 5          ; counter = 5
basic_loop:
    push rcx            ; save counter
    
    mov rax, 1          ; print *
    mov rdi, 1
    mov rsi, char
    mov rdx, 1
    syscall
    
    pop rcx             ; restore counter
    loop basic_loop     ; dec rcx and jump if rcx != 0

    ; Print newline
    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

    ; JRCXZ demonstration (x64 version of JECXZ)
    mov rax, 1
    mov rdi, 1
    mov rsi, msg2
    mov rdx, len2
    syscall

    xor rcx, rcx        ; rcx = 0
    jrcxz zero_detected ; jump if rcx = 0
    jmp exit
zero_detected:
    mov rax, 1
    mov rdi, 1
    mov rsi, char
    mov rdx, 1
    syscall

exit:
    ; Exit program
    mov rax, 60         ; exit syscall
    xor rdi, rdi        ; return 0
    syscall