ORG 
ORG 00H
MOV DPTR, #2000H
	MOVX A, @DPTR
	MOV R0, A
MOV R1, #01H
MOV R0, #00H
HERE: 	SUBB A, R1
	INC R1
	INC R1
	INC R0
	CJNE A, #00H, HERE
	INC DPTR
	MOV A, R0
MOVX @DPTR,A
END
