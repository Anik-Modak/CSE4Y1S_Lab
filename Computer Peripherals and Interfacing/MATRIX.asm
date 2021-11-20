;*****************************************
;     MDA-Win8086 EXPERIMENT PROGRAM    *
;     FILENAME  : MATRIX_4.ASM
;     PROCESSOR : I8086
;     DOT MATRIX TEST
;     printing from 0 to 9 and repeat with 5 sec delay
;*****************************************
CODE	SEGMENT
	ASSUME	CS:CODE,DS:CODE,ES:CODE,SS:CODE
	;
PPIC_C	EQU	1EH ; control register
PPIC	EQU	1CH ; c port
PPIB	EQU	1AH
PPIA	EQU	18H
	;	
	ORG	1000H
	MOV	AL,10000000B
	OUT	PPIC_C,AL
	;
	MOV	AL,11111111B
	OUT	PPIA,AL
	;
L1:	MOV	SI,OFFSET FONT1
	;
	MOV	BL,10  ; font No.
L3:	MOV	BH,50 ; display time
	;
L2:	PUSH	SI
	CALL	SCAN
	POP	SI
	DEC	BH
	JNZ	L2
	;
	ADD	SI,8
	DEC	BL
	JNZ	L3
        ;
	JMP	L1
	;
	;	
	;
SCAN    PROC	NEAR
	MOV	AH,00000001B
SCAN1:	MOV	AL,BYTE PTR CS:[SI]
	OUT	PPIB,AL
	;		
	MOV	AL,AH
	OUT	PPIC,AL
	CALL	TIMER
	INC	SI
	CLC
	ROL	AH,1
	JNC	SCAN1
	RET
SCAN	ENDP
	;
TIMER:	MOV	CX,300
TIMER1:	NOP
	NOP
	NOP
	NOP
	LOOP	TIMER1
	RET
	;
FONT1:  DB  11111111B
        DB  11000011B
		DB	10111101B
		DB	10111101B
        DB  10111101B
		DB	10111101B
        DB  11000011B
		DB	11111111B
	;
FONT2:  DB  11111111B
        DB  11111111B
		DB	10111111B
		DB	10000000B
        DB  11111111B
		DB	11111111B
        DB  11111111B
		DB	11111111B
	;
FONT3:  DB  11111111B
        DB  10110000B
		DB	10110110B
		DB	10110110B
        DB  10110110B
		DB	10000110B
        DB  11111111B
		DB	11111111B
	;
FONT4:  DB  11111111B
        DB  10110110B
        DB  10110110B
        DB  10110110B
        DB  10110110B
        DB  10110110B
        DB  10000000B
		DB	11111111B
	;
FONT5:  DB  11111111B
        DB  11111111B
        DB  10000111B
        DB  11110111B
        DB  11110111B
        DB  11110111B
        DB  10000000B
        DB  11111111B
	;
FONT6:  DB  11111111B
        DB  10000110B
        DB  10110110B
        DB  10110110B
        DB  10110110B
        DB  10110110B
        DB  10110000B
        DB  11111111B
	;	
FONT7:  DB  11111111B
        DB  10000000B
        DB  10110110B
        DB  10110110B
        DB  10110110B
        DB  10110110B
        DB  10110000B
        DB  11111111B
	;
FONT8:  DB  11111111B
        DB  11111111B
        DB  10111111B
        DB  10111111B
        DB  10111111B
        DB  10000000B
        DB  11111111B
        DB  11111111B

FONT9:  DB  11111111B
        DB  10000000B
		DB	10110110B
		DB	10110110B
        DB  10110110B
		DB	10110110B
        DB  10000000B
		DB	11111111B
	
FONT10: DB  11111111B
        DB  10000110B
		DB	10110110B
		DB	10110110B
        DB  10110110B
		DB	10110110B
        DB  10000000B
		DB	11111111B

	;
CODE	ENDS
	END
	
	
