; Command Line Arguments Example
; -------------------------------------------------------

section .data
; -----
; Define standard constants.
LF          equ 10         ; line feed
NULL        equ 0          ; end of string
TRUE        equ 1          ; true
FALSE       equ 0          ; false
EXIT_SUCCESS equ 0         ; success code
STDIN       equ 0          ; standard input
STDOUT      equ 1          ; standard output
STDERR      equ 2          ; standard error
SYS_read    equ 0          ; read syscall
SYS_write   equ 1          ; write syscall
SYS_open    equ 2          ; file open syscall
SYS_close   equ 3          ; file close syscall
SYS_fork    equ 57         ; fork syscall
SYS_exit    equ 60         ; terminate syscall
SYS_creat   equ 85         ; file open/create syscall
SYS_time    equ 201        ; get time syscall

; -----
; Variables for main.
newLine     db LF, NULL    ; new line string

section .text
global main

main:
; -----
; Get command line arguments and echo to screen.
; Based on the standard calling convention,
; rdi = argc (argument count)
; rsi = argv (starting address of argument vector)

mov r12, rdi      ; Save argc (argument count) for later use
mov r13, rsi      ; Save argv (starting address of argument vector)

; -----
; Simple loop to display each argument to the screen.
; Each argument is a NULL terminated string, so we can just
; print directly.
printArguments:
mov rdi, newLine   ; Load address of newLine (newline) to rdi
call printString   ; Call printString to print the newline

mov rbx, 0         ; Initialize index (argument counter)
printLoop:
mov rdi, qword [r13 + rbx * 8] ; Load address of the argument
call printString   ; Print the argument string

mov rdi, newLine   ; Load address of newLine (newline) to rdi
call printString   ; Print newline after argument

inc rbx            ; Increment index (argument counter)
cmp rbx, r12       ; Compare index with argc (argument count)
jl printLoop       ; If index < argc, continue loop

; -----
; Example program done.
exampleDone:
mov rax, SYS_exit  ; Syscall code for exit
mov rdi, EXIT_SUCCESS ; Exit with success
syscall            ; Call the syscall to terminate the program

; **********************************************************
; Generic procedure to display a string to the screen.
; String must be NULL terminated.
; Algorithm:
; 1) Count characters in string (excluding NULL)
; 2) Use syscall to output characters
; Arguments:
; 1) address, string
; Returns: nothing

global printString
printString:
push rbp            ; Save the base pointer
mov rbp, rsp        ; Set up the stack frame
push rbx            ; Save rbx register

; -----
; Count characters in string.
mov rbx, rdi        ; Load address of string into rbx
mov rdx, 0          ; Initialize character count to 0

strCountLoop:
cmp byte [rbx], NULL ; Check for NULL terminator
je strCountDone      ; If NULL, we are done counting
inc rdx              ; Increment character count
inc rbx              ; Move to the next byte in the string
jmp strCountLoop     ; Continue the loop

strCountDone:
cmp rdx, 0           ; If no characters, skip print
je prtDone           ; If no characters, skip print

; -----
; Call OS to output string.
mov rax, SYS_write   ; Syscall code for write
mov rsi, rdi         ; Address of string to write
mov rdi, STDOUT      ; File descriptor (standard output)
syscall              ; Call syscall to write the string

prtDone:
pop rbx              ; Restore rbx register
pop rbp              ; Restore the base pointer
ret                  ; Return to the caller
