ORG 00H
MOV DPTR, #2000H 	; Initialize Source address
	MOV R1, #0AH 	; Initialize count of 10
	CLR A 			; “A” will accumulate the Sum, and also get the data from Ext. RAM
	MOV B, #00H 		; B register will accumulate the Carry
	MOV R0, #00H 	; R0 will be used to store the sum for next iteration
REPEAT: MOVX A, @DPTR 	; Get the data from Ext RAM
	ADD A, R0 		; Add the data to the previous sum
	JNC SKIP 		; If no carry, then directly proceed ahead
	INC B 			; If there is a carry, increment B Register
SKIP: 	INC DPTR 		; Increment source address
	MOV R0, A 		; Store current Sum in R0 from next iteration
	DJNZ R1, REPEAT 	; Decrement count. If Count is NOT ZERO then repeat.
	MOV DPTR, #3000H 	; DPTR gets address to store the Sum
	MOVX @DPTR, A 	; Store Sum
	INC DPTR 		; DPTR gets address to store the Carry
	MOV A, B		; Transfer Carry from B to A register
	MOVX @DPTR, A 	; Store Carry
	END			; End of program
