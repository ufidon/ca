section .data
    ; Message for output
    result_msg db "Result: 0x", 0
    newline db 0xA, 0

    ; Example inputs
    x dq 0x12345678  ; Example input x
    y dq 0x87654321  ; Example input y
    z dq 0xABCDEF01  ; Example input z

section .bss
    ; Buffer to store hexadecimal result
    hex_buffer resb 16

section .text
    global _start

_start:
    ; Load inputs into registers
    mov rdi, [x]    ; Load x into %rdi
    mov rsi, [y]    ; Load y into %rsi
    mov rdx, 0      ; way one to clear rdx
    mov rdx, [z]    ; Load z into %rdx
    xor rdx, rdx    ; way two to clear rdx
    mov rdx, [z]    ; Load z into %rdx

    ; Perform the operations
    or rsi, rdi     ; t1 = x | y
    sar rdi, 3      ; t2 = t1 >> 3 (arithmetic right shift by 3)
    not rdi         ; t3 = ~t2 (bitwise NOT)
    mov rax, rdx    ; Move z into %rax
    sub rax, rdi    ; t4 = z - t3

    ; Print the result
    call print_hex  ; Print the result in hexadecimal
    call print_newline ; Print a newline

    ; Exit the program
    mov rax, 60     ; syscall: exit
    xor rdi, rdi    ; status: 0
    syscall

; Function to print a hexadecimal value
print_hex:
    lea rdi, [hex_buffer]   ; Load address of hex_buffer
    mov rcx, 16             ; Number of digits to print
.convert_loop:
    rol rax, 4              ; Rotate left by 4 bits
    mov bl, al              ; Copy lower 4 bits to bl
    and bl, 0xF             ; Isolate lower 4 bits
    cmp bl, 9               ; Check if it's a digit or letter
    jbe .digit
    add bl, 7               ; Adjust for letters (A-F)
.digit:
    add bl, '0'             ; Convert to ASCII
    mov [rdi], bl           ; Store in hex_buffer
    inc rdi                 ; Move to next buffer position
    loop .convert_loop      ; Repeat for all digits

    ; Print the result message
    mov rax, 1              ; syscall: write
    mov rdi, 1              ; file descriptor: stdout
    lea rsi, [result_msg]   ; message to print
    mov rdx, 9              ; length of message
    syscall

    ; Print the hexadecimal value
    mov rax, 1              ; syscall: write
    mov rdi, 1              ; file descriptor: stdout
    lea rsi, [hex_buffer]   ; buffer to print
    mov rdx, 16             ; number of bytes to print
    syscall
    ret

; Function to print a newline
print_newline:
    mov rax, 1              ; syscall: write
    mov rdi, 1              ; file descriptor: stdout
    lea rsi, [newline]      ; newline character
    mov rdx, 1              ; number of bytes to print
    syscall
    ret