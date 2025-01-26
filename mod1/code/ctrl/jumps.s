; nasm -f elf64 -g -o jumps.o jumps.s
; yasm -f elf64 -g dwarf2  -o jumps.o jumps.s
; ld -o jumps jumps.o

section .data
    prompt db "Guess a number between 0 and 9: ", 0
    too_low db "Too low! Try again: ", 0
    too_high db "Too high! Try again: ", 0
    correct db "Congratulations! You guessed the correct number!", 0
    invalid db "Invalid guess! Please enter a number between 0 and 9: ", 0
    newline db 10
    seed dq 0  ; Seed for the random number generator

section .bss
    guess resb 2  ; Reserve space for user input (1 byte for digit + 1 byte for newline)

section .text
    global _start

_start:
    and rsp, -16 ; align stack

    ; Seed the random number generator using the current time
    mov rax, 201  ; syscall: gettimeofday
    xor rdi, rdi  ; NULL (no timezone struct)
    syscall
    mov rdi, rax  ; Use the lower bits of the time as the seed
    call srand

    ; Generate a random number between 0 and 9
    call rand
    xor rdx, rdx
    mov rcx, 10
    div rcx       ; Divide random number by 10, remainder (rdx) is between 0 and 9
    mov r8, rdx   ; Store the random number in r8

    ; Prompt the user
    mov rsi, prompt
    call print_string

game_loop:
    ; Read user input
    mov rax, 0          ; syscall: read
    mov rdi, 0          ; file descriptor: stdin
    mov rsi, guess      ; buffer to store input
    mov rdx, 2          ; read up to 2 bytes (1 digit + newline)
    syscall

    ; Convert input to integer
    movzx r9, byte [guess]  ; Load the first byte of input
    cmp r9, '0'
    jl invalid_input
    cmp r9, '9'
    jg invalid_input
    sub r9, '0'             ; Convert ASCII to integer

    ; Compare guess with random number
    cmp r9, r8
    jl guess_too_low
    jg guess_too_high

    ; Correct guess
    mov rsi, correct
    call print_string
    jmp exit

invalid_input:
    mov rsi, invalid
    call print_string
    jmp game_loop

guess_too_low:
    mov rsi, too_low
    call print_string
    jmp game_loop

guess_too_high:
    mov rsi, too_high
    call print_string
    jmp game_loop

exit:
    ; Exit the program
    mov rax, 60         ; syscall: exit
    xor rdi, rdi        ; exit code 0
    syscall

; Function to print a null-terminated string
print_string:
    mov rax, 1          ; syscall: write
    mov rdi, 1          ; file descriptor: stdout
    call strlen         ; Calculate string length
    mov rdx, rax        ; Length of the string
    mov rax, 1
    syscall
    ret

; Function to calculate the length of a null-terminated string
strlen:
    xor rax, rax        ; Initialize length counter
strlen_loop:
    cmp byte [rsi + rax], 0
    je strlen_done
    inc rax
    jmp strlen_loop
strlen_done:
    ret

; Function to seed the random number generator
srand:
    mov [seed], rdi      ; Store the seed value
    ret

; Function to generate a random number
rand:
    mov rax, [seed]
    mov rcx, 1103515245
    mul rcx
    add rax, 12345
    mov [seed], rax
    shr rax, 16
    and rax, 0x7FFF
    ret
