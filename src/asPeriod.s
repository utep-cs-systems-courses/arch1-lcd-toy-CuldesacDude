	.arch msp430g2553
	.p2align 1,0
	.text

	.global asPeriod

asPeriod:			;pd in R12
	sub #2, R1		;allocate memory for 1500
	mov #1500, 0(R1)	;move 1500 into stack
	mov R12, R13		;move pd int R13
	cmp R13, 0(R1)		;1500 - pd negative if pd > 1500
	jl else			;n != v
	add #200, R13		;increment pd
	jmp return
else:
	sub #200, R13		;decrement pd
	jmp return
return:
	add #2, R1		;deallocate memory
	mov R13, R12		;move pd back into R12 and return
	pop R0
	
