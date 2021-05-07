
	/*r2 status registers]
	r3 constant generator */
	.arch	msp430g2553
	.p2align 1,0

	.text

h:
	
	.word option0
	.word option1
	.word option2
	.word option3

	.global assemSound

assemSound:
	sub #2, r1
	mov #0, 0(r1)

	cmp #4, r12
	jhs end

	cmp #0, r12
	jl end
	
	add r12, r12
	mov h(r12), r1

option0:
	mov #400, 0(r1)
	mov 0(r1), r12
	call #buzzer_set_period

	jmp end
	
option1:
	mov #600, 0(r1)
	mov 0(r1), r12
	call #buzzer_set_period

	jmp end

option2:
	mov #700, 0(r1)
	mov 0(r1), r12
	call #buzzer_set_period

	jmp end

option3:
	mov #800, 0(r1)
	mov 0(r1), r12
	call #buzzer_set_period

	jmp end

	
end:
	/*
	r1 [*p(800)][][][]
	r1[0] -> r12 (*pointer(int 800))
	buzzer_set_period(r12)
	*/
	add #2, r1   	;r1 stack pointer 
	pop r0		;reset program counter 

	

	
