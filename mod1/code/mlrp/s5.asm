; Simple example to compute the sum and average for
; a list of numbers.
; *****************************************************

section .data

; Define constants
EXIT_SUCCESS equ 0  ; Successful operation
SYS_exit equ 60     ; Call code for terminate

; Define Data
lst dd 1002, 1004, 1006, 1008, 10010
len dd 5
sum dd 0

; ********************************************************
section .text
global _start

_start:
; Summation loop.
    mov ecx, dword [len]  ; Get length value
    mov rsi, 0            ; Index = 0

sumLoop:
    mov eax, dword [lst + (rsi * 4)] ; Get lst[rsi]
    add dword [sum], eax  ; Update sum
    inc rsi               ; Next item
    loop sumLoop          ; Repeat for all elements

; Done, terminate program.
last:
    mov rax, SYS_exit     ; Call code for exit
    mov rdi, EXIT_SUCCESS ; Exit with success
    syscall
