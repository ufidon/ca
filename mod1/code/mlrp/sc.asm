; Example program to demonstrate console output.
; This example will send some messages to the screen.
; **********************************************

section .data
; -----
; Define standard constants.
LF        equ 10           ; line feed
NULL      equ 0            ; end of string
TRUE      equ 1            ; true
FALSE     equ 0            ; false
EXIT_SUCCESS equ 0         ; success code
STDIN     equ 0            ; standard input
STDOUT    equ 1            ; standard output
STDERR    equ 2            ; standard error
SYS_read  equ 0            ; read syscall
SYS_write equ 1            ; write syscall
SYS_open  equ 2            ; file open syscall
SYS_close equ 3            ; file close syscall
SYS_fork  equ 57           ; fork syscall
SYS_exit equ 60            ; terminate syscall
SYS_creat equ 85           ; file open/create syscall
SYS_time equ 201           ; get time syscall

; -----
; Define some strings.
message1  db "Hello World.", LF, NULL
message2  db "Enter Answer: ", NULL
newLine   db LF, NULL

;------------------------------------------------------

section .text
global _start

_start:
; -----
; Display first message.
mov rdi, message1
call printString

; -----
; Display second message and then newline
mov rdi, message2
call printString
mov rdi, newLine
call printString

; -----
; Example program done.
exampleDone:
mov rax, SYS_exit
mov rdi, EXIT_SUCCESS
syscall

; ******************************************************
; Generic function to display a string to the screen.
; String must be NULL terminated.
;
; Algorithm:
; 1) Count characters in string (excluding NULL)
; 2) Use syscall to output characters
;
; Arguments:
; 1) address, string
;
; Returns:
; nothing

global printString
printString:
push rbx

; -----
; Count characters in string.
mov rbx, rdi           ; Load address of string into rbx
mov rdx, 0             ; Initialize character count to 0

strCountLoop:
cmp byte [rbx], NULL    ; Check if we reached NULL terminator
je strCountDone        ; If yes, we are done counting
inc rdx                ; Increment character count
inc rbx                ; Move to next character
jmp strCountLoop       ; Continue loop

strCountDone:
cmp rdx, 0             ; Check if string length is 0
je prtDone             ; If no characters, skip print

; -----
; Call OS to output string.
mov rax, SYS_write     ; System code for write()
mov rsi, rdi           ; Address of characters to write
mov rdi, STDOUT        ; Standard output (stdout)
syscall                ; System call to write the string

; -----
; String printed, return to calling routine.
prtDone:
pop rbx                ; Restore rbx
ret                    ; Return from function
