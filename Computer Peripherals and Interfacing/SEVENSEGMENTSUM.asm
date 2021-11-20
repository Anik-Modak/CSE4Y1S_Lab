;*****************************************
;     MDA-Win8086 EXPERIMENT PROGRAM    *
;     FILENAME  : SEVENSEGMENTSUM.ASM
;     PROCESSOR : I8086
;     8255 TEST
;     showing two numbers and their sum
;*****************************************
CODE	SEGMENT
	ASSUME	CS:CODE,DS:CODE,ES:CODE,SS:CODE
	;
PPIC_C	EQU	1FH
PPIC	EQU	1DH
PPIB	EQU	1BH
PPIA	EQU	19H
	;	
	ORG	1000H
	MOV	AL,10000000B
	OUT	PPIC_C,AL
	;
	MOV	AL,11110000B
	OUT	PPIB,AL
	;
	MOV	AL,00000000B
	OUT	PPIC,AL
	
    ; sum segment
    MOV  BX, 5H ; numebr 1
    MOV  DX, 4H ; number 2


    ; display first   number
    MOV     CX, BX
    PUSH    SI
    CALL    DISPLAY
    POP     SI
        		
    ; display second number
	MOV     CX, DX
    PUSH    SI
    CALL    DISPLAY
    POP     SI
	
	; Adding two numbers	
    ADD     BX, DX
        
    ; Display output
    MOV     CX, BX
    PUSH    SI
    CALL    DISPLAY
    POP     SI
	
	JMP    SKIP ; skipping for the last call / serial process
	
    ; Displays the objects on BL
DISPLAY PROC    NEAR
	
 	MOV	SI,OFFSET DATA
 	ADD     SI, CX
	MOV	AL,BYTE PTR CS:[SI]     		
	OUT	PPIA,AL

    ; delay
    MOV  CX, 60000
T1: NOP
    NOP
    NOP
    NOP
    LOOP T1
	
    RET   	
DISPLAY ENDP        	
SKIP:

	;
	INT	3
	;		
DATA:	DB	11000000B
		DB	11111001B
		DB	10100100B
		DB	10110000B
		DB	10011001B
		DB	10010010B
		DB	10000010B
		DB	11111000B
		DB	10000000B
		DB	10010000B
		DB	00H
CODE	ENDS
	END