	.file	"add.c"
	.option nopic
	.attribute arch, "rv32i2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,8
	sw	a5,-20(s0)
	li	a5,29
	sw	a5,-24(s0)
	li	a5,84
	sw	a5,-28(s0)
	lw	a5,-28(s0)
	addi	a5,a5,3
	lw	a4,-20(s0)
	add	a5,a4,a5
	sw	a5,-28(s0)
	lw	a5,-28(s0)
	addi	a5,a5,-3
	sw	a5,-28(s0)
	lw	a5,-28(s0)
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 11.1.0"
