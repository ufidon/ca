; **Key Points**
; 
; - **Avoid Hardcoded Addresses**: Hardcoded addresses like `0x100` are not valid in user-space programs. Use the stack or heap instead.
; - **Stack Allocation**: Use `sub rsp, <size>` to allocate memory on the stack for temporary storage.
; - **Proper Memory Access**: Ensure that all memory accesses are within valid, allocated regions.


section .data
    ; No initialized data needed

section .bss
    ; Reserve space for heap memory
    heap_ptr resq 1  ; Pointer to allocated heap memory

section .text
    global _start

_start:
    ; Allocate heap memory (using brk syscall)
    mov rax, 12         ; syscall: brk
    xor rdi, rdi        ; Get current break (heap start)
    syscall
    mov [heap_ptr], rax ; Save heap start address

    ; Allocate 32 bytes on the heap
    add rax, 32         ; Request 32 bytes
    mov rdi, rax        ; Set new break
    mov rax, 12         ; syscall: brk
    syscall

    ; Initialize stack with input data
    mov qword [rsp], 0xFF   ; Push 0xFF to stack (simulates address 0x100)
    mov qword [rsp + 8], 0xAB ; Push 0xAB to stack (simulates address 0x108)
    mov qword [rsp + 16], 0x13 ; Push 0x13 to stack (simulates address 0x110)
    mov qword [rsp + 24], 0x11 ; Push 0x11 to stack (simulates address 0x118)

    ; Initialize registers
    mov rax, rsp        ; rax = stack pointer (simulates address 0x100)
    mov rcx, 0x1        ; rcx = 0x1
    mov rdx, 0x3        ; rdx = 0x3

    ; Perform operations
    add  [rax], rcx        ; [rax] = 0xFF + 0x1 = 0x100
    sub  [rax + 8], rdx    ; [rax + 8] = 0xAB - 0x3 = 0xA8

    ; the imul instruction cannot directly multiply a memory location by an immediate value
    ; refer to https://www.felixcloutier.com/x86/imul
    mov rbx, [rax + rdx*8]      ; Load value from memory into rbx
    imul rbx, 16                ; Multiply rbx by 16
    mov [rax + rdx*8], rbx      ; Store result back into memory

    inc qword [rax + 16]        ; [rax + 16] = 0x13 + 1 = 0x14
    dec rcx                     ; rcx = 0x1 - 1 = 0x0
    sub rax, rdx                ; rax = 0x100 - 0x3 = 0xFD

    ; Store results on the heap
    mov rbx, [heap_ptr]         ; Load heap pointer
    mov [rbx], rax              ; Store rax (0xFD) at heap_ptr
    mov [rbx + 8], rcx          ; Store rcx (0x0) at heap_ptr + 8

    ; no mem to mem movement
    mov r8,  [rax]
    mov [rbx + 16],  r8         ; Store [rax] (0x100) at heap_ptr + 16
    mov r9,  [rax + 8]
    mov [rbx + 24],  r9         ; Store [rax + 8] (0xA8) at heap_ptr + 24

    ; Exit program
    mov eax, 60         ; syscall: exit
    xor edi, edi        ; status: 0
    syscall    