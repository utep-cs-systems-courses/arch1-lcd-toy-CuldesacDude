	.arch msp4302553
	.p2align 1,0

	.text

	.extern sirenState
	.extern sirenShapeAdvance
	.extern siren

jt:
	.word case0
	.word case1

	.global sirenStateAdvance

sirenStateAdvance:
	cmp.b #2, &sirenState
	jge end			;jmp if n == v non neg if sirenState > 2
	mov.b &sirenState, R12
	add.b R12, R12
	mov jt(R12), R0

case0:
	call #siren		;advance our states
	call #sirenShapeAdvance
	add.b #1, &sirenState	;increment sirenState
	jmp end
case1:
	call #siren
	call #sirenShapeAdvance
	sub.b #1, &sirenState
	jmp end
end:
	pop R0
	
