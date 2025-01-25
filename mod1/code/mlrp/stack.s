; yasm -f elf64 -o stack.o stack.s
; ld -o stack stack.o

; | Data Size   | Push Instruction/Workaround                     | Pop Instruction/Workaround                     |
; |-------------|-------------------------------------------------|------------------------------------------------|
; | **Byte (8-bit)**  | `sub rsp, 1; mov byte ptr [rsp], al`      | `mov al, byte ptr [rsp]; add rsp, 1`           |
; | **Word (16-bit)** | `sub rsp, 2; mov word ptr [rsp], ax`      | `mov ax, word ptr [rsp]; add rsp, 2`           |
; | **Dword (32-bit)**| `push eax` (zero-extended to 64 bits)     | `pop eax` (upper 32 bits zeroed)               |
; | **Qword (64-bit)**| `push rax`                                | `pop rax`                                      |
; 
;  **Key Points**:
; 1. **Default Behavior**: In x86-64, `push` and `pop` are optimized for 64-bit operations. Smaller sizes require manual adjustments.
; 2. **Alignment**: The stack pointer (`rsp`) must always be aligned to 8 bytes (64 bits) for proper function calls and system interactions. Pushing smaller sizes can break this alignment unless carefully managed.
; 3. **Efficiency**: Using `push` and `pop` for 64-bit values is more efficient than manually adjusting the stack pointer for smaller sizes.

section .data
    byte_val  db 0xAA
    word_val  dw 0x1234
    dword_val dd 0x56789ABC
    qword_val dq 0x1122334455667788

section .text
    global _start

_start:
    ; Push a byte
    sub rsp, 1
    mov al, byte [byte_val]
    mov byte [rsp], al

    ; Push a word
    sub rsp, 2
    mov ax, word [word_val]
    mov word [rsp], ax

    ; Push a dword (zero-extended to 64 bits)
    mov eax, dword [dword_val]  ; Load dword into eax (zero-extended to rax)
    push rax                    ; Push 64-bit value

    ; Push a qword
    push qword [qword_val]

    ; Pop a qword
    pop rax

    ; Pop a dword (only lower 32 bits are meaningful)
    pop rax                     ; Pop 64-bit value into rax
    mov eax, eax                ; Clear upper 32 bits (optional)

    ; Pop a word
    mov ax, word [rsp]
    add rsp, 2

    ; Pop a byte
    mov al, byte [rsp]
    add rsp, 1

    ; Exit program
    mov eax, 60         ; syscall: exit
    xor edi, edi        ; status: 0
    syscall