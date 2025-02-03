; Simple example demonstrating basic stack operations.
; Reverse a list of numbers - in place.
; Method: Put each number on stack, then pop each number
; back off, and then put back into memory.
; *****************************************************

section .data
; -----
; Define constants
EXIT_SUCCESS equ 0       ; successful operation
SYS_exit     equ 60      ; syscall code for terminate

; -----
; Define Data
numbers dq 121, 122, 123, 124, 125
len      dq 5

; ****************************************************
section .text
global _start
_start:

; Loop to put numbers on stack
mov rcx, qword [len]    ; Load length of numbers
mov rbx, numbers        ; Load address of numbers array
mov r12, 0               ; Initialize index counter
mov rax, 0               ; Clear rax register (not used yet)

pushLoop:
push qword [rbx + r12*8] ; Push each number onto stack
inc r12                   ; Increment index
loop pushLoop             ; Loop until all numbers are pushed onto stack

; -----
; All the numbers are on stack (in reverse order).
; Loop to get them back off and put them back into the original list...

mov rcx, qword [len]     ; Reload length of numbers
mov rbx, numbers         ; Reload address of numbers array
mov r12, 0               ; Reset index counter

popLoop:
pop rax                   ; Pop number from stack into rax
mov qword [rbx + r12*8], rax ; Store the popped number back into memory
inc r12                   ; Increment index
loop popLoop              ; Loop until all numbers are popped off the stack

; -----
; Done, terminate program.

last:
mov rax, SYS_exit        ; syscall for exit
mov rdi, EXIT_SUCCESS     ; exit with success
syscall                  ; make the syscall to exit the program
