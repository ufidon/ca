    .text
    .globl _start

# long fact_while(long n)
# n in %rdi
fact_while:
    cmpq $1, %rdi            # Compare n with 1
    jle .L1                   # If n <= 1, jump to done
    movl $1, %eax            # Set result = 1 (initialize eax to 1)
.L2:
    imulq %rdi, %rax         # result = result * n
    subq $1, %rdi            # Decrement n
    cmpq $1, %rdi            # Compare n with 1
    jne .L2                  # If n != 1, repeat the loop
    ret

.L1:
    movl $1, %eax            # result = 1 (base case, when n <= 1)
    ret

# long ifpop_while(long a, long b)
# a in %rdi, b in %rsi
ifpop_while:
    movl $1, %eax            # Set result = 1 (initialize eax to 1)
    jmp .L3                   # Jump to check condition

.L4:
    leaq (%rdi, %rsi), %rdx   # %rdx = a + b
    imulq %rdx, %rax          # Multiply result * (a + b)
    addq $1, %rdi             # Increment a
.L3:
    cmpq %rsi, %rdi           # Compare a with b
    jl .L4                    # If a < b, jump to loop
    ret

# long fact_while2(long a, long b)
# a in %rdi, b in %rsi
fact_while2:
    testq %rsi, %rsi          # Test if b <= 0
    jle .L5                   # If b <= 0, jump to done
    movq %rsi, %rax           # Set result = b
.L6:
    imulq %rdi, %rax          # result = result * a
    subq %rdi, %rsi           # Decrement b
    testq %rsi, %rsi          # Test if b <= 0
    jne .L6                   # If b > 0, continue loop
    ret

.L5:
    movl $1, %eax             # result = 1 (base case, when b <= 0)
    ret

# long fun_a(unsigned long x)
# x in %rdi
fun_a:
    movl $0, %eax             # Set result = 0
    jmp .L7                    # Jump to the test loop

.L8:
    xorq %rdi, %rax           # XOR the result with x
    shrq %rdi                 # Shift x right by 1
.L7:
    testq %rdi, %rdi          # Test if x == 0
    jne .L8                   # If x != 0, repeat the loop
    andl $1, %eax             # Set result = result & 1 (extract the last bit)
    ret

_start:
    # You can test the functions here by calling them
    # Example: Call fact_while(5)
    movq $5, %rdi             # Pass 5 as the argument
    call fact_while
    # The result is in %eax
    # You can add code here to exit or print the result
    ret
