; Simple example program to compute the
; sum of squares from 1 to n.
; **********************************************

section .data

; Define constants
SUCCESS equ 0  ; Successful operation
SYS_exit equ 60  ; Call code for terminate

; Define Data
n dd 10
sumOfSquares dq 0

; *******************************************************
section .text
global _start

_start:
; Compute sum of squares from 1 to n (inclusive).
; Approach:
; for (i=1; i<=n; i++)
;     sumOfSquares += i^2;

mov rbx, 1         ; i = 1
mov ecx, dword [n] ; n (loop counter)

sumLoop:
    mov rax, rbx             ; get i
    mul rax                  ; i^2
    add qword [sumOfSquares], rax ; sumOfSquares += i^2
    inc rbx                  ; i++
    loop sumLoop             ; repeat while i <= n

; Done, terminate program.
last:
    mov rax, SYS_exit        ; Call code for exit
    mov rdi, SUCCESS         ; Exit with success
    syscall
