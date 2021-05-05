	.arch msp430g2553
	.p2align 1,0
	.text

	.global compare

compare:			;a in R12, b in R13
	cmp R12, R13		;b - a no borrow if a>=b
	jlo else
	mov.b #1, R12
	jmp out
else:
	mov.b #0, R12
	jmp out
out:
	pop R0
	
