ORG 0000H
 MOV DPTR,#4200H 
MOV A,@DPTR 
MOV R1,A 
LOOP: DEC R1
 MOV B,R1 
MUL AB
 CJNE R1,#01,LOOP
 MOV DPTR,#4201H 
MOVX @DPTR,A
 END