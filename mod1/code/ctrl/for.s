    .global fact_for
    .global fun_b

# Function fact_for: long fact_for(long n)
# n is in %rdi
fact_for:
    # Set result = 1
    movl $1, %eax

    # Set i = 2
    movl $2, %edx

.LS:
    # Compare i with n
    cmpq %rdi, %rdx
    jg .done      # If i > n, we are done

    # Compute result *= i
    imulq %rdx, %rax

    # Increment i
    addq $1, %rdx

    # Jump to loop
    jmp .LS

.done:
    # Return result in %rax
    ret


# Function fun_b: long fun_b(unsigned long x)
# x is in %rdi
fun_b:
    # Set 64 as the limit in %rdx
    movl $64, %edx

    # Set result = 0
    movl $0, %eax

.L10:
    # Copy x to %rcx
    movq %rdi, %rcx

    # Perform bitwise AND with 1
    andl $1, %ecx

    # Add the result to %rax (shifting result left by 1)
    addq %rax, %rax

    # Perform OR with the result of the AND operation
    orq %rcx, %rax

    # Right shift x by 1
    shrq %rdi

    # Decrement loop counter
    subq $1, %rdx

    # Continue the loop if %rdx is not zero
    jne .L10

    # Return result in %rax
    ret
