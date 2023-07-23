ORG 0x7C00

SECTION .TEXT
    MOV AX, 0
    MOV DS, AX
    MOV ES, AX
    MOV GS, AX
    MOV FS, AX
    MOV SS, AX

    ; set video mode
    MOV AX, 0x10
    INT 0x10

    ; Load kernel
    MOV BX, 0x8000   ; Destination address
    MOV AH, 0x02
    MOV AL, 30       ; num sectors
    MOV CH, 0        ; Cylinder number
    MOV CL, 2        ; Sector number
    MOV DH, 0        ; Head number
    INT 0x13

    ;MOV AH, 0x2
    ;INT 0x1A
    ;PUSH DX

    JMP 0x8000  ; jump to kernel

TIMES 510-($-$$) DB 0
DW 0xAA55
