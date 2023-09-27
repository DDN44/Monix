org 0x7E00
bits 16

%DEFINE ENDL 0x0D, 0x0A

main:
    MOV SI, data
    CALL puts

    ;MOV AX, word 0xB000
    ;MOV ES, AX
    ;MOV BX, word 0x8000

    ;MOV [ES:BX], byte 0x48
    ;MOV [ES:BX+1], byte 0x1F

    MOV SI, packet;load kernal into ram
    MOV AH, 0x42
    MOV DL, 0x80

    INT 0x13

    ;MOV ax, 0x2401 ;A20
    ;INT 0x15

    MOV AH, 0x0
    MOV AL, 0x3
    INT 0x10

    CLI
    LGDT [tabl_desc]

    MOV eax, cr0 
    OR al, 1       ; set PE (Protection Enable) bit in CR0 (Control Register 0)
    MOV cr0, eax

    MOV esp, stak
    JMP CODESEG:promode32

stak:
bits 32
promode32:
    MOV AX, DATASEG
    MOV DS, AX
    MOV SS, AX
    MOV ES, AX
    MOV FS, AX
    MOV GS, AX
    MOV EBP, 0x90000
    MOV ESP, EBP
    
    JMP CODESEG:0x8000

ene:
    JMP ene

bits 16
    JMP end

puts:
    PUSH SI
    PUSH AX

.loop:
    LODSB
    OR AL, AL
    JZ .done

    MOV AH, 0x0E
    MOV BH, 0
    INT 0x10
    JMP .loop

.done:
    POP AX
    POP SI
    RET

data: db 'hello from loader', ENDL, 0

end:
    jmp end

tabl:
    dq 0 ;NULL 64 bit

codedes:
    dw 0xFFFF ;limit
    dw 0x0000 ;base 0-15
    db 0x00 ;base 16-23
    db 0b10011010 ;access byte
    db 0b11001111 ;limit then flags right to left
    db 0x00 ;base 24-31

datades:
    dw 0xFFFF ;limit
    dw 0x0000 ;base 0-15
    db 0x00 ;base 16-23
    db 0b10010010 ;access byte
    db 0b11001111 ;limit then flags right to left
    db 0x00 ;base 24-31
tabl_end:

tabl_desc:
    dw tabl_end - tabl - 1
    dd tabl

    CODESEG equ codedes - tabl
    DATASEG equ datades - tabl

packet:
    db 16
    db 0
    dw 0x0004
    dw 0x8000, 0x0000
    dd 0x00000002
    dd 0x00000000

times 512-($-$$) db 0