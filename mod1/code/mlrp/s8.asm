; Simple example program to convert an integer into an ASCII string.
; *********************************************************

section .data
; -----
; Define constants
NULL        equ 0         ; NULL terminator
EXIT_SUCCESS equ 0        ; successful operation
SYS_exit    equ 60        ; syscall code for terminate

; -----
; Define Data
intNum      dd 1498      ; Integer number to be converted

section .bss
strNum      resb 10      ; Reserve space for string (10 bytes)

; *********************************************************
section .text
global _start
_start:
; Convert an integer to an ASCII string.
; -----
; Part A - Successive division to get the digits
mov eax, dword [intNum]    ; Get the integer to be converted
mov rcx, 0                 ; digitCount = 0
mov ebx, 10                ; Set divisor for dividing by 10

divideLoop:
mov edx, 0                 ; Clear the remainder (edx)
div ebx                    ; Divide eax by 10, result in eax, remainder in edx
push rdx                    ; Push the remainder (digit) onto the stack
inc rcx                     ; Increment digitCount
cmp eax, 0                  ; If (eax == 0), check if division is complete
jne divideLoop             ; If not zero, continue dividing

; -----
; Part B - Convert remainders (digits) and store them in string
mov rbx, strNum            ; Get address of string
mov rdi, 0                 ; idx = 0 (index into string)

popLoop:
pop rax                     ; Pop the digit (in rdx, now in rax)
add al, '0'                 ; Convert integer to ASCII by adding "0"
mov byte [rbx + rdi], al    ; Store the character in the string at [rbx + rdi]
inc rdi                     ; Increment the index (rdi)
loop popLoop                ; Loop until all digits are popped

; -----
; Null-terminate the string
mov byte [rbx + rdi], NULL  ; Null-terminate the string

; -----
; Done, terminate program
last:
mov rax, SYS_exit           ; syscall for exit
mov rdi, EXIT_SUCCESS       ; Exit with success
syscall                     ; Make the syscall to exit the program
