; nasm -f elf64 shift.s -o shift.o
; ld shift.o -o shift

section .data
    ; Messages for output
    left_shift_msg db "Left Shift (0x8000000F << 4): 0x", 0
    right_arithmetic_msg db "Right Arithmetic Shift (0x8000000F >> 4): 0x", 0
    right_logical_msg db "Right Logical Shift (0x8000000F >> 4): 0x", 0
    newline db 0xA, 0

    ; Example values
    x dd 0x8000000F  ; Unsigned value for left and logical shifts
    y dd 0x8000000F  ; Signed value for arithmetic shift
    shift_amount db 4 ; Shift amount

section .bss
    ; Buffer to store hexadecimal result
    hex_buffer resb 8

section .text
    global _start

_start:
    ; Perform Left Shift
    mov eax, [x]            ; Load x into eax
    mov cl, [shift_amount]  ; Load shift amount into cl
    shl eax, cl             ; Perform left shift
    call print_result       ; Print result
    lea rsi, [left_shift_msg]
    call print_string

    ; Perform Right Arithmetic Shift
    mov eax, [y]            ; Load y into eax
    mov cl, [shift_amount]  ; Load shift amount into cl
    sar eax, cl             ; Perform arithmetic right shift
    call print_result       ; Print result
    lea rsi, [right_arithmetic_msg]
    call print_string

    ; Perform Right Logical Shift
    mov eax, [x]            ; Load x into eax
    mov cl, [shift_amount]  ; Load shift amount into cl
    shr eax, cl             ; Perform logical right shift
    call print_result       ; Print result
    lea rsi, [right_logical_msg]
    call print_string

    ; Exit program
    mov rax, 60             ; syscall: exit
    xor rdi, rdi            ; status: 0
    syscall

; Function to print a hexadecimal result
print_result:
    lea rdi, [hex_buffer]   ; Load address of hex_buffer
    mov ecx, 8              ; Number of digits to print
.convert_loop:
    rol eax, 4              ; Rotate left by 4 bits
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

    ; Print hex_buffer
    mov rax, 1              ; syscall: write
    mov rdi, 1              ; file descriptor: stdout
    lea rsi, [hex_buffer]   ; buffer to print
    mov rdx, 8              ; number of bytes to print
    syscall

    ; Print newline
    mov rax, 1              ; syscall: write
    mov rdi, 1              ; file descriptor: stdout
    lea rsi, [newline]      ; newline character
    mov rdx, 1              ; number of bytes to print
    syscall
    ret

; Function to print a string
print_string:
    mov rax, 1              ; syscall: write
    mov rdi, 1              ; file descriptor: stdout
    mov rdx, 0              ; Calculate string length
.calc_length:
    cmp byte [rsi + rdx], 0
    je .print
    inc rdx
    jmp .calc_length
.print:
    syscall
    ret