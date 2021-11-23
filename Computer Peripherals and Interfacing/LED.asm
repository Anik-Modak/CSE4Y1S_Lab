;*****************************************
;     MDA-Win8086 EXPERIMENT PROGRAM    *
;     FILENAME  : LED.ASM
;     PROCESSOR : I8086
;     Serialy on and off all 4 LED
;*****************************************

CODE	SEGMENT
	ASSUME	CS:CODE,DS:CODE,ES:CODE,SS:CODE
	;
PPIC_C	EQU	1FH
PPIC	EQU	1DH
PPIB	EQU	1BH
PPIA	EQU	19H
	;
	ORG 1000H
	MOV AL, 10000000B
	OUT PPIC_C, AL
	;
	MOV AL, 11111111B
	OUT PPIA, AL
	;
	MOV AL, 00000000B
	OUT PPIC, AL
	;

L1: MOV SI, OFFSET FONT
	MOV BL, 08H
	;
L2:	MOV AL, BYTE PTR CS:[SI]
	OUT PPIB, AL
	CALL	TIMER
	INC 	SI
	DEC		BL
	JNZ L2
	JMP L1
	;
	INT 3
	;
TIMER:	MOV	CX,1

TIMER1:	NOP
		LOOP	TIMER1
		RET
		;
	
FONT:   DB      11110001B
        DB      11110011B
        DB      11111011B
        DB      11111111B
        DB      11111110B
        DB      11111100B
        DB      11110100B
        DB      11110000B
        ;	
	
CODE	ENDS
	END
