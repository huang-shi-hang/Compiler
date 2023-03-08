	.text
	.align	2
	.globl	f
	.type	f,@function
f:
	addi	sp,sp,-44
	sw	ra,40(sp)
	sw	fp,36(sp)
	mv	fp,sp
	sw	x12,44(fp)
	sw	x13,48(fp)
	sw	x14,52(fp)
	sw	x15,56(fp)
	sw	x16,60(fp)
	sw	x17,64(fp)
	lw	x10,44(fp)
	sw	a0,24(fp)
	lw	x10,48(fp)
	sw	a0,28(fp)
	lw	a0,24(fp)
	lw	a1,28(fp)
	add	a0,a0,a1
	sw	a0,24(fp)
	lw	x10,52(fp)
	sw	a0,28(fp)
	lw	a0,24(fp)
	lw	a1,28(fp)
	add	a0,a0,a1
	sw	a0,24(fp)
	lw	x10,56(fp)
	sw	a0,28(fp)
	lw	a0,24(fp)
	lw	a1,28(fp)
	add	a0,a0,a1
	sw	a0,24(fp)
	lw	x10,60(fp)
	sw	a0,28(fp)
	lw	a0,24(fp)
	lw	a1,28(fp)
	add	a0,a0,a1
	sw	a0,24(fp)
	lw	x10,64(fp)
	sw	a0,28(fp)
	lw	a0,24(fp)
	lw	a1,28(fp)
	add	a0,a0,a1
	sw	a0,24(fp)
	lw	x10,68(fp)
	sw	a0,28(fp)
	lw	a0,24(fp)
	lw	a1,28(fp)
	add	a0,a0,a1
	sw	a0,24(fp)
	j	f_0
	nop
	mv	a0,zero
f_0:
	mv	sp,fp
	lw	ra,40(sp)
	lw	fp,36(sp)
	addi	sp,sp,44
	jr	ra
	nop
	.text
	.align	2
	.globl	main
	.type	main,@function
main:
	addi	sp,sp,-44
	sw	ra,40(sp)
	sw	fp,36(sp)
	mv	fp,sp
	li	a0,1
	sw	a0,28(fp)
	mv	x12,a0
	li	a0,2
	sw	a0,28(fp)
	mv	x13,a0
	li	a0,3
	sw	a0,28(fp)
	mv	x14,a0
	li	a0,4
	sw	a0,28(fp)
	mv	x15,a0
	li	a0,5
	sw	a0,28(fp)
	mv	x16,a0
	li	a0,6
	sw	a0,28(fp)
	mv	x17,a0
	li	a0,7
	sw	a0,28(fp)
	sw	a0,24(fp)
	call	f
	nop
	sw	a0,28(fp)
	j	main_0
	nop
	mv	a0,zero
main_0:
	mv	sp,fp
	lw	ra,40(sp)
	lw	fp,36(sp)
	addi	sp,sp,44
	jr	ra
	nop
