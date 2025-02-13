	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 10
	.globl	_len1
	.align	4, 0x90
_len1:                                  ## @len1
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	movl	$-1, %eax
	.align	4, 0x90
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	incl	%eax
	cmpl	$0, (%rdi)
	leaq	4(%rdi), %rdi
	jne	LBB0_1
## BB#2:
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_len2
	.align	4, 0x90
_len2:                                  ## @len2
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp3:
	.cfi_def_cfa_offset 16
Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp5:
	.cfi_def_cfa_register %rbp
	xorl	%eax, %eax
	cmpl	$0, (%rdi)
	je	LBB1_3
## BB#1:                                ## %.lr.ph.preheader
	xorl	%eax, %eax
	.align	4, 0x90
LBB1_2:                                 ## %.lr.ph
                                        ## =>This Inner Loop Header: Depth=1
	cmpl	$0, 4(%rdi,%rax,4)
	leaq	1(%rax), %rax
	jne	LBB1_2
LBB1_3:                                 ## %._crit_edge
                                        ## kill: EAX<def> EAX<kill> RAX<kill>
	popq	%rbp
	retq
	.cfi_endproc


.subsections_via_symbols
