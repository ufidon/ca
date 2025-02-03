; Floating-Point Example Program
; ***********************************************************

section .data
; -----
; Define constants.
NULL        equ 0           ; end of string
TRUE        equ 1           ; true
FALSE       equ 0           ; false
EXIT_SUCCESS equ 0          ; successful operation
SYS_exit    equ 60          ; system call code for terminate

; -----
fltLst      dq 21.34, 6.15, 9.12, 10.05, 7.75
            dq 1.44, 14.50, 3.32, 75.71, 11.87
length      dq 15           ; length of the list
lstSum      dq 0.0          ; to store the sum of the list
lstAve      dq 0.0          ; to store the average of the list

; ***********************************************************

section .text
global _start

_start:
; -----
; Loop to find floating-point sum.
mov ecx, [length]          ; Load length of list
mov rbx, fltLst            ; Load address of fltLst into rbx
mov rsi, 0                  ; Initialize counter (index) to 0
movsd xmm1, qword [lstSum] ; Initialize xmm1 (sum) with lstSum (0.0)

sumLp:
movsd xmm0, qword [rbx + rsi * 8] ; Load next float from list into xmm0
addsd xmm1, xmm0                  ; Add xmm0 (current number) to xmm1 (sum)
inc rsi                            ; Increment index
loop sumLp                         ; Repeat for all elements

; Save the sum into lstSum
movsd qword [lstSum], xmm1

; -----
; Compute average of entire list.
cvtsi2sd xmm0, dword [length]     ; Convert length (integer) to double (xmm0)
cvtsd2si rax, xmm0                ; Convert xmm0 (double) back to integer to get count
movsd xmm1, xmm0                  ; Move the double value to xmm1 for division
divsd xmm1, xmm0                  ; Divide sum by length to get the average

; Save the average into lstAve
movsd qword [lstAve], xmm1

; -----
; Done, terminate program.
last:
mov rax, SYS_exit                ; System call code for exit
mov rdi, EXIT_SUCCESS             ; Exit with success code
syscall                          ; Invoke syscall to terminate the program

; ***********************************************************
; Get fltLst[i] and update sum
; i++
; Save sum and compute average
; Exit with success
