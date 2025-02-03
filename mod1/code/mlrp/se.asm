; Example program to demonstrate file I/O.
; This example will open/create a file, write some information to the file, and close the file.
; Note, the file name and write message are hard-coded for the example.

section .data
; -----
; Define standard constants.
LF        equ 10         ; line feed
NULL      equ 0          ; end of string
TRUE      equ 1          ; true
FALSE     equ 0          ; false
EXIT_SUCCESS equ 0      ; success code
STDIN     equ 0          ; standard input
STDOUT    equ 1          ; standard output
STDERR    equ 2          ; standard error
SYS_read  equ 0          ; read syscall
SYS_write equ 1          ; write syscall
SYS_open  equ 2          ; file open syscall
SYS_close equ 3          ; file close syscall
SYS_fork  equ 57         ; fork syscall
SYS_exit  equ 60         ; terminate syscall
SYS_creat equ 85         ; file open/create syscall
SYS_time  equ 201        ; get time syscall
O_CREAT  equ 0x40        ; create file flag
O_TRUNC  equ 0x200       ; truncate file flag
O_APPEND equ 0x400       ; append flag
O_RDONLY equ 0x0         ; read-only
O_WRONLY equ 0x1         ; write-only
O_RDWR   equ 0x2         ; read-write
S_IRUSR  equ 00400       ; read permission for owner
S_IWUSR  equ 00200       ; write permission for owner
S_IXUSR  equ 00100       ; execute permission for owner

; -----
; Variables for main.
newLine  db LF, NULL
header   db "File Write Example.", LF, NULL
fileName db "url.txt", NULL
url      db "http://www.google.com", LF, NULL
len      dq $-url-1    ; length of the URL string
writeDone db "Write Completed.", LF, NULL
fileDesc dq 0         ; file descriptor
errMsgOpen db "Error opening file.", LF, NULL
errMsgWrite db "Error writing to file.", LF, NULL

;--------------------------------------------------------
section .text
global _start
_start:
; -----
; Display header line...
mov rdi, header
call printString

; -----
; Attempt to open file.
mov rax, SYS_creat          ; syscall for open/create
mov rdi, fileName           ; file name
mov rsi, S_IRUSR | S_IWUSR  ; file permissions (read/write)
syscall
cmp rax, 0                  ; check for success
jl errorOnOpen              ; if less than 0, error occurred
mov qword [fileDesc], rax   ; store the file descriptor

; -----
; Write to file.
mov rax, SYS_write          ; syscall for write
mov rdi, qword [fileDesc]   ; file descriptor
mov rsi, url                ; address of characters to write
mov rdx, qword [len]        ; number of characters to write
syscall
cmp rax, 0                  ; check for success
jl errorOnWrite             ; if less than 0, error occurred
mov rdi, writeDone          ; success message
call printString

; -----
; Close the file.
mov rax, SYS_close          ; syscall for close
mov rdi, qword [fileDesc]   ; file descriptor
syscall
jmp exampleDone

; -----
; Error on open.
errorOnOpen:
mov rdi, errMsgOpen
call printString
jmp exampleDone

; -----
; Error on write.
errorOnWrite:
mov rdi, errMsgWrite
call printString
jmp exampleDone

; -----
; Example program done.
exampleDone:
mov rax, SYS_exit          ; syscall for exit
mov rdi, EXIT_SUCCESS      ; exit with success
syscall

; **********************************************************
; Generic function to display a string to the screen.
; String must be NULL terminated.
; Algorithm:
; 1) Count characters in string (excluding NULL)
; 2) Use syscall to output characters
;
; Arguments:
; 1) address, string
;
; Returns: nothing

global printString
printString:
push rbx                    ; Save rbx
mov rbx, rdi                ; Load the address of the string into rbx
mov rdx, 0                  ; Initialize character count to 0

; Count characters in string.
strCountLoop:
cmp byte [rbx], NULL         ; Check for NULL terminator
je strCountDone              ; If NULL, we're done counting
inc rdx                      ; Increment character count
inc rbx                      ; Move to the next byte in the string
jmp strCountLoop             ; Continue the loop

strCountDone:
cmp rdx, 0                   ; If no characters, skip print
je prtDone                   ; If no characters, skip print

; Call OS to output the string.
mov rax, SYS_write           ; Syscall code for write
mov rsi, rdi                 ; Address of string to write
mov rdi, STDOUT              ; Standard output
syscall                      ; Call syscall to write the string

; String printed, return to calling routine.
prtDone:
pop rbx                       ; Restore rbx
ret                           ; Return to caller
