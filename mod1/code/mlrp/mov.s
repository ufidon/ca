section .data
    ; Example data with labels
    byte_val db 0xFF  ; Byte at address labeled 'byte_val'
    word_val dw 0x1234 ; Word at address labeled 'word_val'
    dword_val dd 0x12345678 ; Dword at address labeled 'dword_val'
    qword_val dq 0x1122334455667788 ; Qword at address labeled 'qword_val'

section .bss
    ; Reserve space for results and define labels
    resb_label resb 1  ; Reserve 1 byte for updated byte_val
    resw_label resw 1  ; Reserve 2 bytes for updated word_val
    resd_label resd 1  ; Reserve 4 bytes for updated dword_val
    resq_label resq 1  ; Reserve 8 bytes for updated qword_val

section .text
    global _start

_start:
    ; Load example data into registers
    mov al, [byte_val]   ; Load byte_val into AL (8-bit)
    mov bx, [word_val]   ; Load word_val into BX (16-bit)
    mov ecx, [dword_val] ; Load dword_val into ECX (32-bit)
    mov rdx, [qword_val] ; Load qword_val into RDX (64-bit)

    ; Perform operations using the loaded data
    add al, 1            ; Increment AL by 1 (0xFF + 1 = 0x100, but AL is 8-bit, so it wraps to 0x00)
    add bx, 1            ; Increment BX by 1 (0x1234 + 1 = 0x1235)
    add ecx, 1           ; Increment ECX by 1 (0x12345678 + 1 = 0x12345679)
    add rdx, 1           ; Increment RDX by 1 (0x1122334455667788 + 1 = 0x1122334455667789)

    ; Store results in reserved memory (.bss section)
    mov [resb_label], al       ; Store updated AL into reserved byte
    mov [resw_label], bx       ; Store updated BX into reserved word
    mov [resd_label], ecx      ; Store updated ECX into reserved dword
    mov [resq_label], rdx      ; Store updated RDX into reserved qword

    ; Exit program
    mov eax, 60         ; syscall: exit
    xor edi, edi        ; status: 0
    syscall