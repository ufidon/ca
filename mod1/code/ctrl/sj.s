# as -o sj.o sj.s
# ld -o sj sj.o

.globl switch_eg
        .type   switch_eg, @function
switch_eg:
        pushq   %rbp
        movq    %rsp, %rbp

        movl    $1, -8(%rbp)  # w = 1

        cmpq    $6, %rdi       # Compare x with 6
        jg      .Ldefault       # Jump to default if x > 6

        cmpq    $1, %rdi       # Compare x with 1
        jl      .Ldefault       # Jump to default if x < 1

        # Jump table
        movq    switch_table(,%rdi,8), %rax  # Load address from jump table
        jmp     *%rax                      # Indirect jump

switch_table:
        .quad   .Lcase1        # Case 1
        .quad   .Lcase2        # Case 2
        .quad   .Lcase3        # Case 3
        .quad   .Ldefault      # Case 4 (missing, falls through to default)
        .quad   .Lcase5        # Case 5
        .quad   .Lcase5        # Case 6 (same as case 5)

.Lcase1:
        movq    %rsi, %rax     # y in rax
        imulq   %rdx, %rax     # w = y * z
        movq    %rax, -8(%rbp) # store w
        jmp     .Lend

.Lcase2:
        movq    %rsi, %rax     # y in rax
        cqo                     # Prepare for division (sign-extend rax into rdx:rax)
        idivq   %rdx             # w = y / z
        movq    %rax, -8(%rbp)  # store w

.Lcase3:
        movq    -8(%rbp), %rax # load w
        addq    %rdx, %rax     # w += z
        movq    %rax, -8(%rbp)  # store w
        jmp     .Lend

.Lcase5:
        movq    -8(%rbp), %rax # load w
        subq    %rdx, %rax     # w -= z
        movq    %rax, -8(%rbp)  # store w
        jmp     .Lend

.Ldefault:
        movq    $2, -8(%rbp)  # w = 2

.Lend:
        movq    -8(%rbp), %rax # load w
        movq    %rbp, %rsp
        popq    %rbp
        ret
