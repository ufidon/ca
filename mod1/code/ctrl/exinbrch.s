section .text
global _start

_start:

; Function: long arith(long x)
; Input: x in rdi
arith:
    lea rax, [rdi + 7]        ; rax = x + 7
    test rdi, rdi             ; Test if x is negative
    cmovns rax, rdi           ; If x >= 0, rax = x
    sar rax, 3                ; rax = rax >> 3 (arithmetic shift right by 3)
    ret                       ; Return rax

; Function: long _test(long x, long y)
; Inputs: x in rdi, y in rsi
_test:
    lea rax, [rdi * 8]        ; rax = 8 * x
    test rsi, rsi             ; Test if y <= 0
    jle L2                    ; If y <= 0, jump to L2
    mov rax, rsi              ; rax = y
    sub rax, rdi              ; rax = y - x
    mov rdx, rdi              ; rdx = x
    and rdx, rsi              ; rdx = x & y
    cmp rdi, rsi              ; Compare x and y
    cmovge rax, rdx           ; If x >= y, rax = rdx (x & y)
    ret                       ; Return rax

L2:
    add rdi, rsi              ; rdi = x + y
    cmp rsi, -2               ; Compare y with -2
    cmovle rax, rdi           ; If y <= -2, rax = rdi (x + y)
    ret                       ; Return rax
