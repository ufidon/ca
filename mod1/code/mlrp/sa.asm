; Simple example function to find and return
; the sum and average of an array.
; HLL call:
; stats1(arr, len, sum, ave);

; -----
; Arguments:
; arr   - address of the array (passed in rdi)
; len   - length of the array (passed in rsi)
; sum   - address to store the sum (passed in rdx)
; ave   - address to store the average (passed in rcx)

global stats1
stats1:
    ; Prologue: Save registers
    push r12                  ; Save r12, which will be used as the loop counter/index

    ; Initialize registers
    mov r12, 0                ; Initialize counter/index (r12 = 0)
    mov rax, 0                ; Initialize sum (rax = 0)

sumLoop:
    add rax, qword [rdi + r12 * 4] ; sum += arr[r12]
    inc r12                    ; Increment the counter (r12++)
    cmp r12, rsi               ; Compare counter (r12) with length (rsi)
    jl sumLoop                 ; If counter < len, continue the loop

    ; Store the sum in the provided address (rdx)
    mov qword [rdx], rax

    ; Compute the average (sum / len)
    cdq                        ; Sign extend rax into edx:rax
    idiv rsi                   ; Divide rax by len (rsi), quotient in rax (average)
    mov qword [rcx], rax       ; Store the average in the provided address (rcx)

    ; Epilogue: Restore registers and return
    pop r12                    ; Restore r12
    ret                        ; Return from the function
