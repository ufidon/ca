section .data

dValue dd 0
bNum db 42
wNum dw 5000
dNum dd 73000
qNum dq 73000000

bAns db 0
wAns dw 0
dAns dd 0
qAns dq 0

bNum1 db 42
bNum2 db 73

wNum1 dw 4321
wNum2 dw 1234

dNum1 dd 42000
dNum2 dd 73000

qNum1 dq 42000000
qNum2 dq 73000000

dquad1 dq 0x1A00000000000000
        dq 0x0000000000000000

dquad2 dq 0x2C00000000000000
        dq 0x0000000000000000

dqSum dq 0

section .text

global _start

_start:
; Store values
mov dword [dValue], 27
mov al, byte [bNum]
mov byte [bAns], al
mov ax, word [wNum]
mov word [wAns], ax
mov eax, dword [dNum]
mov dword [dAns], eax
mov rax, qword [qNum]
mov qword [qAns], rax

; Addition operations
; Byte addition
mov al, byte [bNum1]
add al, byte [bNum2]
mov byte [bAns], al

; Word addition
mov ax, word [wNum1]
add ax, word [wNum2]
mov word [wAns], ax

; Double-word addition
mov eax, dword [dNum1]
add eax, dword [dNum2]
mov dword [dAns], eax

; Quadword addition
mov rax, qword [qNum1]
add rax, qword [qNum2]
mov qword [qAns], rax

; Increment operations
inc rax
inc byte [bNum]
inc word [wNum]
inc dword [dNum]
inc qword [qNum]

; 128-bit addition
mov rax, qword [dquad1]
mov rdx, qword [dquad1+8]
add rax, qword [dquad2]
adc rdx, qword [dquad2+8]
mov qword [dqSum], rax
mov qword [dqSum+8], rdx

; Subtraction operations
; Byte subtraction
mov al, byte [bNum1]
sub al, byte [bNum2]
mov byte [bAns], al

; Word subtraction
mov ax, word [wNum1]
sub ax, word [wNum2]
mov word [wAns], ax

; Double-word subtraction
mov eax, dword [dNum1]
sub eax, dword [dNum2]
mov dword [dAns], eax

; Quadword subtraction
mov rax, qword [qNum1]
sub rax, qword [qNum2]
mov qword [qAns], rax

; Decrement operations
dec rax ; rax = rax - 1
dec byte [bNum] ; bNum = bNum - 1
dec word [wNum] ; wNum = wNum - 1
dec dword [dNum] ; dNum = dNum - 1
dec qword [qNum] ; qNum = qNum - 1

; ************************************************************
; Done, terminate program.
last:
mov rax, 60  ; Call code for exit
mov rdi, 0  ; Exit program with success
syscall