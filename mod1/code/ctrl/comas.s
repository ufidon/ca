# as -o comas.o comas.s
# ld -o comas comas.o
# ./comas && echo $?

.global _start

.section .data
    # Define two long values for comparison
    a: .quad 10  # a = 10
    b: .quad 20  # b = 20

.section .text
_start:
    # Load values into registers
    movq a, %rdi  # Load a into %rdi
    movq b, %rsi  # Load b into %rsi

    # Compare a and b
    cmpq %rsi, %rdi  # Compare a (rdi) and b (rsi)

    # Set %al to 1 if a < b, otherwise 0
    setl %al         # Set lower byte of %eax based on comparison

    # Zero-extend %al to %eax (and clear upper bytes of %rax)
    movzbl %al, %eax # Move byte to 32-bit register, zero-extending

    # Exit the program with the result as the exit code
    movzbl %al, %edi # Move the result (0 or 1) into edi (exit status)
    movq $60, %rax   # syscall: exit
    syscall
