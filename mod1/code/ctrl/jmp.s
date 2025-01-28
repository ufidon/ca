; yasm -f elf64 jmp.s -o jmp.o
; ld -o jmp jmp.o

section .text
    global _start

_start:
    mov rax, rdi         ; Move value in rdi to rax
    jmp .L2              ; Jump to label .L2
    
.L3:
    sar rax, 1           ; Arithmetic right shift on rax
    
.L2:
    test rax, rax        ; Test rax with itself (sets flags)
    jg .L3               ; Jump to .L3 if greater (signed comparison)
    
    rep; ret             ; return
