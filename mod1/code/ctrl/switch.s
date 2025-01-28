    .section .text
    .global switch_eg
    .global switch2
    .global switcher

# void switch_eg(long x, long n, long *dest)
# x in %rdi, n in %rsi, dest in %rdx
switch_eg:
    subq $100, %rsi            # Compute index = n - 100
    cmpq $6, %rsi              # Compare index with 6
    jg .Adef                   # If index > 6, goto Adef
    jmp *.A4(,%rsi,8)          # Jump to the appropriate case using the jump table

.Adef:                          # Adef: Default case
    movl $0, %edi              # val = 0
    jmp .A2                    # Jump to done

.A3:                           # A3: loc_A (Case 100)
    leaq (%rdi, %rdi, 2), %rax # val = 13 * x
    leaq (%rdi, %rax, 4), %rdi # Update x = 13 * x
    jmp .A2                    # Jump to done

.A5:                           # A5: loc_B (Case 102)
    addq $10, %rdi             # val = x + 10
    jmp .A6                    # Jump to A6 (loc_C)

.A6:                           # A6: loc_C (Case 103)
    addq $11, %rdi             # val = x + 11
    jmp .A2                    # Jump to done

.A7:                           # A7: loc_D (Cases 104, 106)
    imulq %rdi, %rdi           # val = x * x
    jmp .A2                    # Jump to done

.A2:                           # A2: done: Store result in *dest
    movq %rdi, (%rdx)          # *dest = val
    ret                        # Return

# Jump table for switch_eg
    .section .rodata
.A4:
    .quad .A3, .Adef, .A5, .A6, .A7, .Adef, .A7

# void switch2(long x, long *dest)
# x in %rdi
switch2:
    addq $1, %rdi              # Increment x
    cmpq $8, %rdi              # Compare x with 8
    ja .B2                     # If x > 8, goto Bdef
    jmp *.B4(,%rdi,8)          # Jump to the appropriate case using the jump table

.B4:                           # Jump table for switch2
    .quad .B9, .Bdef, .B6, .B7, .B2, .Bdef, .B2, .Bdef, .Bdef

.B9:                           # B9: loc_A (Case 1)
    xorq $15, %rsi             # Example operation: XOR x with 15
    movq %rsi, %rdx            # Move result to %rdx
    jmp .B6                    # Jump to done

.Bdef:                         # Bdef: loc_def (Default case)
    movq $0, %rdi              # Set result to 0
    jmp .B6                    # Jump to done

.B6:                           # B6: done: Store result in *dest
    movq %rdi, (%rdx)          # *dest = val
    ret                        # Return

# void switcher(long a, long b, long c, long *dest)
# a in %rsi, b in %rdi, c in %rdx, dest in %rcx
switcher:
    cmpq $7, %rdi              # Compare b with 7
    ja .C2                     # If b > 7, goto Cdef
    jmp *.C4(,%rdi,8)          # Jump to the appropriate case using the jump table

.C4:                           # Jump table for switcher
    .quad .C3, .C2, .C5, .C2, .C6, .C7, .C2, .C5

.C3:                           # C3: loc_A (Case 0)
    leaq 112(%rdi, %rdi), %rdi # Example operation: %rdi = %rdi * 2 + 112
    jmp .C6                    # Jump to done

.C5:                           # C5: loc_B (Case 1)
    leaq (%rdx, %rsi), %rdi    # Example operation: %rdi = %rdx + %rsi
    salq $2, %rdi              # Shift left by 2 (multiply by 4)
    jmp .C6                    # Jump to done

.C7:                           # C7: loc_C (Case 2)
    xorq $15, %rsi             # Example operation: XOR %rsi with 15
    movq %rsi, %rdx            # Move result to %rdx
    jmp .C6                    # Jump to done

.C2:                           # C2: loc_def: Default case
    movq %rsi, %rdi            # Default value of %rdi
    jmp .C6                    # Jump to done

.C6:                           # C6: done: Store result in *dest
    movq %rdi, (%rcx)          # *dest = %rdi
    ret                        # Return
    