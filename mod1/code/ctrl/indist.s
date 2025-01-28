; yasm -f elf64 -o indist.o indist.s
; ld -o indist indist.o

section .text
    global _start
    global dist
_start:

dist:
    ; rval = y - x
    mov rax, rsi         ; Move y (in rsi) to rax
    sub rax, rdi         ; Subtract x (in rdi) from rax

    ; eval = x - y
    mov rdx, rdi         ; Move x (in rdi) to rdx
    sub rdx, rsi         ; Subtract y (in rsi) from rdx

    ; Compare x and y
    cmp rdi, rsi         ; Compare x (in rdi) with y (in rsi)
    cmovge rax, rdx      ; If x >= y, move eval (in rdx) to rval (in rax)

    ; Return rval
    ret                  ; Return the result in rax
