section .data
    ; Data section for variables
    global_var dd 42          ; A global variable (4 bytes)
    array      dd 10, 20, 30, 40, 50 ; An array of 4-byte integers
    format     db "Value: %d", 0x0A, 0 ; Format string for printing

section .bss
    ; Uninitialized data section
    result resd 1             ; Reserve space for a result variable

section .text
    global _start
    extern printf              ; use C library printf

_start:
    ; 1. Immediate Addressing Mode
    mov eax, 5                ; Load immediate value 5 into eax
    call print_value          ; Print the value in eax

    ; 2. Register Addressing Mode
    mov ebx, eax              ; Copy value from eax to ebx
    call print_value          ; Print the value in ebx

    ; 3. Direct (Absolute) Addressing Mode
    mov eax, [global_var]     ; Load value from global_var into eax
    call print_value          ; Print the value in eax

    ; 4. Register Indirect Addressing Mode
    lea rsi, [array]          ; Load address of array into rsi
    mov eax, [rsi]            ; Load first element of array into eax
    call print_value          ; Print the value in eax

    ; 5. Base + Displacement Addressing Mode
    mov eax, [rsi + 8]        ; Load third element of array (index 2, 4 bytes each)
    call print_value          ; Print the value in eax

    ; 6. Indexed Addressing Mode
    mov rdi, 2                ; Index = 2
    mov eax, [rsi + rdi*4]    ; Load array[2] into eax
    call print_value          ; Print the value in eax

    ; 7. Scaled Indexed Addressing Mode
    mov rdi, 3                ; Index = 3
    mov eax, [rsi + rdi*4]    ; Load array[3] into eax (scale factor = 4)
    call print_value          ; Print the value in eax

    ; 8. RIP-Relative Addressing Mode
    lea rsi, [global_var]  ; Load address of global_var into rsi
    mov eax, [rsi]         ; Dereference the address in rsi to get the value
    call print_value          ; Print the value in eax

    ; 9. Base + Index + Displacement Addressing Mode
    mov rdi, 1                ; Index = 1
    mov eax, [rsi + rdi*4 + 4] ; Load array[1 + 1] (array[2]) into eax
    call print_value          ; Print the value in eax

    ; Exit the program
    mov eax, 60               ; syscall: exit
    xor edi, edi              ; status 0
    syscall

print_value:
    ; Save registers
    push rdi
    push rsi
    push rax

    ; Prepare arguments for printf
    lea rdi, [format]   ; Format string
    mov esi, eax        ; Value to print
    xor eax, eax        ; Clear eax (required for varargs functions)
    call printf         ; Call printf

    ; Restore registers
    pop rax
    pop rsi
    pop rdi
    ret