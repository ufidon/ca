; Example Program to demonstrate a simple macro
; **************************************************

; Define the macro
%macro aver 3
    ; Macro body to calculate the average of a list
    mov eax, 0               ; Clear the accumulator register (sum)
    mov ecx, dword [%2]      ; Load length of the list into ecx
    mov r12, 0               ; Initialize index counter (r12 = 0)
    lea rbx, [%1]            ; Load the address of the list into rbx

%%sumLoop:
    add eax, dword [rbx + r12 * 4]  ; Add list[n] to eax (sum)
    inc r12                     ; Increment index counter
    loop %%sumLoop              ; Repeat for all elements

    cdq                         ; Sign-extend eax into edx:eax
    idiv dword [%2]             ; Divide sum by length (average)
    mov dword [%3], eax         ; Store the result (average) into the given memory location
%endmacro

; **************************************************

section .data
; -----
; Define constants
EXIT_SUCCESS equ 0       ; Success exit code
SYS_exit     equ 60      ; Syscall code for exit

; -----
; Define Data
list1  dd 4, 5, 2, -3, 1
len1   dd 5
ave1   dd 0

list2  dd 2, 6, 3, -2, 1, 8, 19
len2   dd 7
ave2   dd 0

; **************************************************

section .text
global _start
_start:

; -----
; Use the macro in the program to calculate averages
aver list1, len1, ave1  ; Calculate the average for list1 and store in ave1
aver list2, len2, ave2  ; Calculate the average for list2 and store in ave2

; -----
; Done, terminate program
last:
mov rax, SYS_exit        ; Syscall for exit
mov rdi, EXIT_SUCCESS     ; Exit with success
syscall                  ; Make the syscall to exit the program

; 1st data set: list1, len1, ave1
; 2nd data set: list2, len2, ave2
; Exit with success
