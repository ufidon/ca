section .text
global switch_eg
global switch2
global switcher

; void switch_eg(long x, long n, long *dest)
; x in rdi, n in rsi, dest in rdx
switch_eg:
    sub rsi, 100              ; Compute index = n - 100
    cmp rsi, 6                ; Compare index with 6
    jg .Adef                  ; If index > 6, goto Adef
    jmp [.A4 + rsi*8]         ; Jump to the appropriate case using the jump table

.Adef:                        ; Adef: Default case
    mov edi, 0                ; val = 0
    jmp .A2                   ; Jump to done

.A3:                          ; A3: loc_A (Case 100)
    lea rax, [rdi + rdi*2]    ; val = 13 * x
    lea rdi, [rdi + rax*4]    ; Update x = 13 * x
    jmp .A2                   ; Jump to done

.A5:                          ; A5: loc_B (Case 102)
    add rdi, 10               ; val = x + 10
    jmp .A6                   ; Jump to A6 (loc_C)

.A6:                          ; A6: loc_C (Case 103)
    add rdi, 11               ; val = x + 11
    jmp .A2                   ; Jump to done

.A7:                          ; A7: loc_D (Cases 104, 106)
    imul rdi, rdi             ; val = x * x
    jmp .A2                   ; Jump to done

.A2:                          ; A2: done: Store result in *dest
    mov [rdx], rdi            ; *dest = val
    ret                       ; Return

; Jump table for switch_eg
section .rodata
.A4:
    dq .A3, .Adef, .A5, .A6, .A7, .Adef, .A7

; void switch2(long x, long *dest)
; x in rdi
switch2:
    add rdi, 1                ; Increment x
    cmp rdi, 8                ; Compare x with 8
    ja .B2                    ; If x > 8, goto Bdef
    jmp [.B4 + rdi*8]         ; Jump to the appropriate case using the jump table

.B4:                          ; Jump table for switch2
    dq .B9, .Bdef, .B6, .B7, .B2, .Bdef, .B2, .Bdef, .Bdef

.B9:                          ; B9: loc_A (Case 1)
    xor rsi, 15               ; Example operation: XOR x with 15
    mov rdx, rsi              ; Move result to rdx
    jmp .B6                   ; Jump to done

.Bdef:                        ; Bdef: loc_def (Default case)
    mov rdi, 0                ; Set result to 0
    jmp .B6                   ; Jump to done

.B6:                          ; B6: done: Store result in *dest
    mov [rdx], rdi            ; *dest = val
    ret                       ; Return

; Define missing labels for switch2
.B2:                          ; B2: loc_B (Case 4, 6)
    mov rdi, 42               ; Example value for cases 4 and 6
    jmp .B6                   ; Jump to done

.B7:                          ; B7: loc_C (Case 3)
    mov rdi, 99               ; Example value for case 3
    jmp .B6                   ; Jump to done

; void switcher(long a, long b, long c, long *dest)
; a in rsi, b in rdi, c in rdx, dest in rcx
switcher:
    cmp rdi, 7                ; Compare b with 7
    ja .C2                    ; If b > 7, goto Cdef
    jmp [.C4 + rdi*8]         ; Jump to the appropriate case using the jump table

.C4:                          ; Jump table for switcher
    dq .C3, .C2, .C5, .C2, .C6, .C7, .C2, .C5

.C3:                          ; C3: loc_A (Case 0)
    lea rdi, [rdi + rdi + 112] ; Example operation: rdi = rdi * 2 + 112
    jmp .C6                   ; Jump to done

.C5:                          ; C5: loc_B (Case 1)
    lea rdi, [rdx + rsi]      ; Example operation: rdi = rdx + rsi
    shl rdi, 2                ; Shift left by 2 (multiply by 4)
    jmp .C6                   ; Jump to done

.C7:                          ; C7: loc_C (Case 2)
    xor rsi, 15               ; Example operation: XOR rsi with 15
    mov rdx, rsi              ; Move result to rdx
    jmp .C6                   ; Jump to done

.C2:                          ; C2: loc_def: Default case
    mov rdi, rsi              ; Default value of rdi
    jmp .C6                   ; Jump to done

.C6:                          ; C6: done: Store result in *dest
    mov [rcx], rdi            ; *dest = rdi
    ret                       ; Return
    