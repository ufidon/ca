; nasm -f elf64 octa.s -o octa.o
; gcc -no-pie -nostartfiles  -o octa octa.o

section .data
    ; 64-bit signed and unsigned integers
    signed_a      dq 1234567890123456789
    signed_b      dq 987654321098765432
    unsigned_a    dq 12345678901234567890
    unsigned_b    dq 9876543210987654321

    ; Format strings for printing
    fmt_signed_mul_64    db "64-bit Signed Multiplication: %ld * %ld = %ld", 10, 0
    fmt_unsigned_mul_64  db "64-bit Unsigned Multiplication: %lu * %lu = %lu", 10, 0
    fmt_signed_div_64    db "64-bit Signed Division: %ld / %ld = %ld", 10, 0
    fmt_signed_mod_64    db "64-bit Signed Modulus: %ld %% %ld = %ld", 10, 0
    fmt_unsigned_div_64  db "64-bit Unsigned Division: %lu / %lu = %lu", 10, 0
    fmt_unsigned_mod_64  db "64-bit Unsigned Modulus: %lu %% %lu = %lu", 10, 0
    fmt_signed_mul_128   db "128-bit Signed Multiplication: %ld * %ld = %ld (high) %ld (low)", 10, 0
    fmt_unsigned_mul_128 db "128-bit Unsigned Multiplication: %lu * %lu = %lu (high) %lu (low)", 10, 0
    fmt_signed_div_128   db "128-bit Signed Division: %ld / %ld = %ld", 10, 0
    fmt_signed_mod_128   db "128-bit Signed Modulus: %ld %% %ld = %ld", 10, 0
    fmt_unsigned_div_128 db "128-bit Unsigned Division: %lu / %lu = %lu", 10, 0
    fmt_unsigned_mod_128 db "128-bit Unsigned Modulus: %lu %% %lu = %lu", 10, 0

section .bss
    ; Temporary storage for results
    signed_mul_64    resq 1
    unsigned_mul_64  resq 1
    signed_div_64    resq 1
    signed_mod_64    resq 1
    unsigned_div_64  resq 1
    unsigned_mod_64  resq 1
    signed_mul_128   resq 2  ; High and low parts
    unsigned_mul_128 resq 2  ; High and low parts
    signed_div_128   resq 1
    signed_mod_128   resq 1
    unsigned_div_128 resq 1
    unsigned_mod_128 resq 1

section .text
    global _start
    extern printf

_start:
    ; Load 64-bit signed values
    mov rax, [signed_a]
    mov rbx, [signed_b]

    ; 64-bit signed multiplication
    imul rbx
    mov [signed_mul_64], rax

    ; 64-bit signed division and modulus
    mov rax, [signed_a]
    cqo                ; Sign-extend rax into rdx
    idiv qword [signed_b]
    mov [signed_div_64], rax
    mov [signed_mod_64], rdx

    ; Load 64-bit unsigned values
    mov rax, [unsigned_a]
    mov rbx, [unsigned_b]

    ; 64-bit unsigned multiplication
    mul rbx
    mov [unsigned_mul_64], rax

    ; 64-bit unsigned division and modulus
    mov rax, [unsigned_a]
    xor rdx, rdx       ; Clear rdx for unsigned division
    div qword [unsigned_b]
    mov [unsigned_div_64], rax
    mov [unsigned_mod_64], rdx

    ; 128-bit signed multiplication
    mov rax, [signed_a]
    imul qword [signed_b]
    mov [signed_mul_128], rdx  ; High 64 bits
    mov [signed_mul_128 + 8], rax  ; Low 64 bits

    ; 128-bit signed division and modulus
    mov rax, [signed_a]
    cqo                ; Sign-extend rax into rdx
    idiv qword [signed_b]
    mov [signed_div_128], rax
    mov [signed_mod_128], rdx

    ; 128-bit unsigned multiplication
    mov rax, [unsigned_a]
    mul qword [unsigned_b]
    mov [unsigned_mul_128], rdx  ; High 64 bits
    mov [unsigned_mul_128 + 8], rax  ; Low 64 bits

    ; 128-bit unsigned division and modulus
    mov rax, [unsigned_a]
    xor rdx, rdx       ; Clear rdx for unsigned division
    div qword [unsigned_b]
    mov [unsigned_div_128], rax
    mov [unsigned_mod_128], rdx

    ; Print results
    ; 64-bit signed multiplication
    mov rdi, fmt_signed_mul_64
    mov rsi, [signed_a]
    mov rdx, [signed_b]
    mov rcx, [signed_mul_64]
    call printf

    ; 64-bit unsigned multiplication
    mov rdi, fmt_unsigned_mul_64
    mov rsi, [unsigned_a]
    mov rdx, [unsigned_b]
    mov rcx, [unsigned_mul_64]
    call printf

    ; 64-bit signed division
    mov rdi, fmt_signed_div_64
    mov rsi, [signed_a]
    mov rdx, [signed_b]
    mov rcx, [signed_div_64]
    call printf

    ; 64-bit signed modulus
    mov rdi, fmt_signed_mod_64
    mov rsi, [signed_a]
    mov rdx, [signed_b]
    mov rcx, [signed_mod_64]
    call printf

    ; 64-bit unsigned division
    mov rdi, fmt_unsigned_div_64
    mov rsi, [unsigned_a]
    mov rdx, [unsigned_b]
    mov rcx, [unsigned_div_64]
    call printf

    ; 64-bit unsigned modulus
    mov rdi, fmt_unsigned_mod_64
    mov rsi, [unsigned_a]
    mov rdx, [unsigned_b]
    mov rcx, [unsigned_mod_64]
    call printf

    ; 128-bit signed multiplication
    mov rdi, fmt_signed_mul_128
    mov rsi, [signed_a]
    mov rdx, [signed_b]
    mov rcx, [signed_mul_128]  ; High 64 bits
    mov r8, [signed_mul_128 + 8]  ; Low 64 bits
    call printf

    ; 128-bit unsigned multiplication
    mov rdi, fmt_unsigned_mul_128
    mov rsi, [unsigned_a]
    mov rdx, [unsigned_b]
    mov rcx, [unsigned_mul_128]  ; High 64 bits
    mov r8, [unsigned_mul_128 + 8]  ; Low 64 bits
    call printf

    ; 128-bit signed division
    mov rdi, fmt_signed_div_128
    mov rsi, [signed_a]
    mov rdx, [signed_b]
    mov rcx, [signed_div_128]
    call printf

    ; 128-bit signed modulus
    mov rdi, fmt_signed_mod_128
    mov rsi, [signed_a]
    mov rdx, [signed_b]
    mov rcx, [signed_mod_128]
    call printf

    ; 128-bit unsigned division
    mov rdi, fmt_unsigned_div_128
    mov rsi, [unsigned_a]
    mov rdx, [unsigned_b]
    mov rcx, [unsigned_div_128]
    call printf

    ; 128-bit unsigned modulus
    mov rdi, fmt_unsigned_mod_128
    mov rsi, [unsigned_a]
    mov rdx, [unsigned_b]
    mov rcx, [unsigned_mod_128]
    call printf

    ; Exit program
    mov rax, 60         ; syscall: exit
    xor rdi, rdi        ; status: 0
    syscall