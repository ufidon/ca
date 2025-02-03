section .data

bNumA db 42
bNumB db 73
bNumC db 5
bAns1 db 0
bAns2 db 0
bRem2 db 0
bAns3 db 0

wNumA dw 4321
wNumB dw 1234
wNumC dw 167
wAns1 dw 0
wRem2 dw 0
wAns3 dw 0

dNumA dd 42000
dNumB dd -3157
dNumC dd -293
dAns1 dd 0
dRem2 dd 0
dAns3 dd 0

qNumA dq 730000
qNumB dq -13456
qNumC dq -1279
qAns1 dq 0

qRem2 dq 0
qAns3 dq 0

dquad1 dq 0x1A00000000000000 
       dq 0x0000000000000000
dquad2 dq 0x2C00000000000000
       dq 0x0000000000000000
dqSum dq 0, 0

section .bss
wAns2 resw 2
dAns2 resq 2
qAns2 resq 4

section .text
global _start

_start:

; Byte Operations
mov al, byte [bNumA]
mul al
mov word [wAns1], ax

mov al, byte [bNumA]
mul byte [bNumB]
mov word [wAns2], ax

; Word Operations
mov ax, word [wNumA]
mul word [wNumB]
mov word [dAns2], ax
mov word [dAns2+2], dx

; Double-Word Operations
mov eax, dword [dNumA]
mul dword [dNumB]
mov dword [qAns2], eax
mov dword [qAns2+4], edx

; Quad-Word Operations
mov rax, qword [qNumA]
mul qword [qNumB]
mov qword [dqSum], rax
mov qword [dqSum+8], rdx

; Signed Multiplication
imul ax, word [wNumA], -13
mov word [wAns1], ax

; imul ax, word [wNumA], word [wNumB]    ; Invalid

mov ax, word [wNumA]   ; Load wNumA into AX
imul word [wNumB]      ; Multiply AX by wNumB (Result in DX:AX)
mov word [wAns2], ax   ; Store lower 16-bit result
mov word [wAns2+2], dx ; Store upper 16-bit result


imul eax, dword [dNumA], 113
mov dword [dAns1], eax

; imul eax, dword [dNumA], dword [dNumB] ; Invalid
mov eax, dword [dNumA]  ; Load dNumA into EAX
imul dword [dNumB]      ; Multiply EAX by dNumB (Result in EDX:EAX)
mov dword [dAns2], eax  ; Store lower 32-bit result
mov dword [dAns2+4], edx ; Store upper 32-bit result


imul rax, qword [qNumA], 7096
mov qword [qAns1], rax

; imul rax, qword [qNumA], qword [qNumB] ; Invalid
mov rax, qword [qNumA]  ; Load qNumA into RAX
imul qword [qNumB]      ; Multiply RAX by qNumB (Result in RDX:RAX)
mov qword [qAns2], rax  ; Store lower 64-bit result
mov qword [qAns2+8], rdx ; Store upper 64-bit result


mov rcx, qword [qNumA]
imul rbx, rcx, 7096
mov qword [qAns1], rbx

; Division Operations
mov al, byte [bNumA]
mov ah, 0
mov bl, 3
div bl
mov byte [bAns1], al

mov ax, 0
mov al, byte [bNumA]
div byte [bNumB]
mov byte [bAns2], al
mov byte [bRem2], ah

mov al, byte [bNumA]
mul byte [bNumC]
div byte [bNumB]
mov byte [bAns3], al

mov ax, word [wNumA]
mov dx, 0
mov bx, 5
div bx
mov word [wAns1], ax

mov dx, 0
mov ax, word [wNumA]
div word [wNumB]
mov word [wAns2], ax
mov word [wRem2], dx

mov ax, word [wNumA]
mul word [wNumC]
div word [wNumB]
mov word [wAns3], ax

; Signed Division
mov eax, dword [dNumA]
cdq
mov ebx, 7
idiv ebx
mov dword [dAns1], eax

mov eax, dword [dNumA]
cdq
idiv dword [dNumB]
mov dword [dAns2], eax
mov dword [dRem2], edx

mov eax, dword [dNumA]
imul dword [dNumC]
idiv dword [dNumB]
mov dword [dAns3], eax

mov rax, qword [qNumA]
cqo
mov rbx, 9
idiv rbx
mov qword [qAns1], rax

mov rax, qword [qNumA]
cqo
idiv qword [qNumB]
mov qword [qAns2], rax
mov qword [qRem2], rdx

mov rax, qword [qNumA]
imul qword [qNumC]
idiv qword [qNumB]
mov qword [qAns3], rax

; ************************************************************
; Done, terminate program.
last:
mov rax, 60  ; Call code for exit
mov rdi, 0  ; Exit program with success
syscall