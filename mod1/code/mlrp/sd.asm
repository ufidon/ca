; Example program to demonstrate console output.
; This example will send some messages to the screen.
; **********************************************

section .data
; -----
; Define standard constants
LF          equ 10          ; line feed
NULL        equ 0           ; end of string
TRUE        equ 1           ; true
FALSE       equ 0           ; false
EXIT_SUCCESS equ 0          ; success code
STDIN       equ 0           ; standard input
STDOUT      equ 1           ; standard output
STDERR      equ 2           ; standard error
SYS_read    equ 0           ; read syscall
SYS_write   equ 1           ; write syscall
SYS_open    equ 2           ; file open syscall
SYS_close   equ 3           ; file close syscall
SYS_fork    equ 57          ; fork syscall
SYS_exit    equ 60          ; terminate syscall
SYS_creat   equ 85          ; file open/create syscall
SYS_time    equ 201         ; get time syscall

; -----
; Define some strings
STRLEN      equ 50          ; String length constant
pmpt        db "Enter Text: ", NULL
newLine     db LF, NULL

section .bss
chr         resb 1          ; Reserve 1 byte for character input
inLine      resb STRLEN + 2 ; Reserve space for input buffer + 2 for NULL termination

;------------------------------------------------------

section .text
global _start

_start:
; -----
; Display prompt.
mov rdi, pmpt
call printString

; -----
; Read characters from user (one at a time)
mov rbx, inLine           ; Load the address of the input buffer
mov r12, 0                 ; Initialize character count

readCharacters:
mov rax, SYS_read         ; Syscall code for reading input
mov rdi, STDIN            ; Standard input
lea rsi, [chr]            ; Load the address of the char buffer
mov rdx, 1                ; Read one byte at a time
syscall                   ; Call syscall

mov al, byte [chr]        ; Get the character just read
cmp al, LF                ; Compare with linefeed (LF)
je readDone               ; If LF, input is done

; -----
; Store the character in the input buffer
mov byte [rbx], al        ; Store character in inLine
inc rbx                   ; Move to the next byte in the buffer
inc r12                   ; Increment character count

cmp r12, STRLEN           ; If the character count >= STRLEN, stop reading
jae readDone              ; Jump to readDone if true

jmp readCharacters        ; Otherwise, continue reading characters

readDone:
mov byte [rbx], NULL       ; Null-terminate the string

; -----
; Output the line to verify successful read
mov rdi, inLine
call printString

; -----
; Example done, exit the program
exampleDone:
mov rax, SYS_exit         ; Syscall code for exit
mov rdi, EXIT_SUCCESS     ; Exit with success
syscall                   ; Call syscall to exit

; ******************************************************
; Generic procedure to display a string to the screen.
; String must be NULL terminated.
; Algorithm:
; 1) Count characters in the string (excluding NULL)
; 2) Use syscall to output characters
;
; Arguments:
; 1) address, string
;
; Returns:
; nothing

global printString
printString:
push rbx                    ; Save rbx

; -----
; Count characters in string
mov rbx, rdi                ; Load the address of the string into rbx
mov rdx, 0                  ; Initialize character count to 0

strCountLoop:
cmp byte [rbx], NULL         ; Check for NULL terminator
je strCountDone              ; If NULL, we're done counting
inc rdx                      ; Increment character count
inc rbx                      ; Move to the next byte in the string
jmp strCountLoop             ; Continue the loop

strCountDone:
cmp rdx, 0                   ; If no characters, skip print
je prtDone                   ; If no characters, skip print

; -----
; Call OS to output the string
mov rax, SYS_write           ; Syscall code for write
mov rsi, rdi                 ; Address of string to write
mov rdi, STDOUT              ; Standard output (stdout)
syscall                      ; Call syscall to write the string

; -----
; String printed, return to calling routine
prtDone:
pop rbx                       ; Restore rbx
ret                           ; Return to caller
