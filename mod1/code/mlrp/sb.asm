; Simple example function to find and return the minimum,
; maximum, sum, medians, and average of an array.
; -----
; HLL call:
; stats2(arr, len, min, med1, med2, max, sum, ave);
;
; Arguments:
; arr    - address of the array (rdi)
; len    - length of the array (esi)
; min    - address to store the minimum value (rdx)
; med1   - address to store the first median (rcx)
; med2   - address to store the second median (r8)
; max    - address to store the maximum value (r9)
; sum    - address to store the sum (stack at rbp + 16)
; ave    - address to store the average (stack at rbp + 24)

global stats2
stats2:
    ; Prologue
    push rbp                    ; Save the base pointer
    mov rbp, rsp                ; Set up the stack frame
    push r12                     ; Save r12, which will be used for iteration

    ; -----
    ; Get min and max.
    mov eax, dword [rdi]         ; Load the first element (min) into eax
    mov dword [rdx], eax         ; Store min in the provided address (rdx)
    
    mov r12, rsi                 ; Load length (len) into r12
    dec r12                       ; Set r12 = len - 1
    mov eax, dword [rdi + r12 * 4] ; Load last element into eax (max)
    mov dword [r9], eax          ; Store max in the provided address (r9)

    ; -----
    ; Get medians
    mov rax, rsi                 ; Load len into rax
    mov rdx, 0                   ; Clear rdx (for division)
    mov r12, 2                   ; Set divisor for median calculation (length / 2)
    div r12                       ; rax = len / 2 (quotient in rax, remainder in rdx)
    cmp rdx, 0                   ; Check if the length is even or odd
    je evenLength                ; If remainder is 0, it's an even length array

    ; Odd length - Single median
    mov r12d, dword [rdi + rax * 4] ; Get the middle element (median)
    mov dword [rcx], r12d        ; Store median 1 in rcx
    mov dword [r8], r12d         ; Store median 2 in r8
    jmp medDone                  ; Skip evenLength code

evenLength:
    ; Even length - Two medians
    mov r12d, dword [rdi + rax * 4] ; Get arr[len/2]
    mov dword [rcx], r12d        ; Store median 1 in rcx
    dec rax                       ; Get arr[len/2 - 1]
    mov r12d, dword [rdi + rax * 4] ; Get arr[len/2 - 1]
    mov dword [r8], r12d         ; Store median 2 in r8

medDone:
    ; -----
    ; Find sum
    mov eax, 0                   ; Initialize sum to 0
    mov r12, 0                    ; Initialize index to 0
sumLoop:
    add eax, dword [rdi + r12 * 4] ; sum += arr[i]
    inc r12                       ; Increment index
    cmp r12, rsi                  ; Compare index with len
    jl sumLoop                    ; If index < len, continue the loop

    ; Store the sum in the provided address (stack at rbp + 16)
    mov r12, qword [rbp + 16]
    mov dword [r12], eax          ; Store sum at [rbp + 16]

    ; -----
    ; Calculate average
    cdq                           ; Sign extend eax into edx:eax
    idiv esi                      ; Divide sum by len (esi), quotient in eax (average)
    
    ; Store the average in the provided address (stack at rbp + 24)
    mov r12, qword [rbp + 24]
    mov dword [r12], eax          ; Store average at [rbp + 24]

    ; Epilogue
    pop r12                        ; Restore r12
    pop rbp                        ; Restore the base pointer
    ret                            ; Return from the function


; -----------------------------------------
; Example function

global expFunc
expFunc:
    ; Prologue: Save registers and set up stack frame
    push rbp                      ; Save the old base pointer
    mov rbp, rsp                  ; Set up the stack frame
    sub rsp, 404                  ; Allocate space for local variables

    ; Save registers that will be used
    push rbx
    push r12

    ; -----
    ; Initialize count local variable to 0
    mov dword [rbp-404], 0        ; count = 0

    ; -----
    ; Increment count variable (for example)
    inc dword [rbp-404]           ; count++

    ; -----
    ; Loop to initialize tmpArr to all 0's
    lea rbx, dword [rbp-400]      ; Load address of tmpArr into rbx
    mov r12, 0                    ; Initialize index to 0

zeroLoop:
    mov dword [rbx + r12 * 4], 0  ; tmpArr[index] = 0
    inc r12                       ; Increment index
    cmp r12, 100                  ; Compare index with 100
    jl zeroLoop                   ; If index < 100, continue loop

    ; -----
    ; Done, restore all and return to calling routine

    pop r12                        ; Restore r12
    pop rbx                        ; Restore rbx
    mov rsp, rbp                  ; Restore the stack pointer
    pop rbp                        ; Restore the old base pointer
    ret                            ; Return to the caller

    ; Epilogue: Clear locals
