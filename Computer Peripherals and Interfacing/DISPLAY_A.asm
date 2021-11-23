;*****************************************
;     MDA-Win8086 EXPERIMENT PROGRAM    *
;     FILENAME  : DISPLAY_A.ASM
;     PROCESSOR : I8086
;     DOT MATRIX TEST
;     printing A in dot matrix
;*****************************************

CODE    SEGMENT
        ASSUME CS:CODE, DS:CODE, ES:CODE, SS:CODE
        ;
PPIC_C  EQU  1EH
PPIC    EQU  1CH
PPIB    EQU  1AH
PPIB    EQU  18H
    ;
    ORG 1000H
    MOV AL, 10000000B
    OUT PPIC_C, AL
    ;
    MOV AL, 11111111B
    OUT PPIA, AL
    ;

L1: MOV SI, OFFSET FONT
    ;
    MOV AH, 00000001H
    ;
    MOV AL, BYTE PTR CS:[SI]
    OUT PPIB, AL
    MOV AL, AH
    OUT PPIC, AL
    CALL TIMER
    INC  SI
    CLC
    ROL AH, 1
    JNC L2
    JMP L1
    ;

    INT 3
    ;
TIMER: MOV CX, 300
T1:     NOP
        LOOP T1
        ;
        RET

FONT:   DB  11111111B
        DB  11000000B
        DB  10110111B
        DB  01110111B
        DB  01110111B
        DB  10110111B
        DB  11000000B
        DB  11111111B
        ;
CODE    ENDS
        END