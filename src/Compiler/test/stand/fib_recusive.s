	.file	"fib_recusive.c"
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
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	sw	zero,-20(s0)
	sw	zero,-28(s0)
	li	a5,10
	sw	a5,-32(s0)
	li	a5,1
	sw	a5,-24(s0)
	j	.L2
.L3:
	lw	a0,-20(s0)
	call	Fibonacci
	sw	a0,-28(s0)
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
.L2:
	lw	a4,-24(s0)
	lw	a5,-32(s0)
	ble	a4,a5,.L3
	lw	a5,-28(s0)
	mv	a0,a5
	lw	ra,28(sp)
	lw	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.align	2
	.globl	Fibonacci
	.type	Fibonacci, @function
Fibonacci:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	sw	s1,20(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	lw	a5,-20(s0)
	bne	a5,zero,.L6
	li	a5,0
	j	.L7
.L6:
	lw	a4,-20(s0)
	li	a5,1
	bne	a4,a5,.L8
	li	a5,1
	j	.L7
.L8:
	lw	a5,-20(s0)
	addi	a5,a5,-1
	mv	a0,a5
	call	Fibonacci
	mv	s1,a0
	lw	a5,-20(s0)
	addi	a5,a5,-2
	mv	a0,a5
	call	Fibonacci
	mv	a5,a0
	add	a5,s1,a5
.L7:
	mv	a0,a5
	lw	ra,28(sp)
	lw	s0,24(sp)
	lw	s1,20(sp)
	addi	sp,sp,32
	jr	ra
	.size	Fibonacci, .-Fibonacci
	.ident	"GCC: (GNU) 11.1.0"
