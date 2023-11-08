org 0x7C00
bits 16

; ES is the segment register and DI is the index register
; they are added like so:
; 0000 0001 1010 1100      segment
; +    0000 0101 0011 0001 offset 
; 0000 0001 1111 1111 0001 address

start:
    ; setup segments
    MOV AX, 0
    MOV DS, AX
    MOV ES, AX

    MOV SS, AX
    MOV SP, 0x7C00

loadkernel:

    ;MOV AX, word 0xB000
    ;MOV ES, AX
    ;MOV BX, word 0x8000

    ;MOV [ES:BX], byte 0x48
    ;MOV [ES:BX+1], byte 0x1F

    MOV SI, packet;load kernel into ram
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

    MOV esp, 0x7BFF
    JMP CODESEG:promode32
bits 32
promode32:
;moving:
;    MOV EBX, 0
;    MOV AH, [0x8000+EBX]
;    MOV [0x00000000+EBX], AH
;    INC EBX
;    CMP EBX, 4096
;    JLE moving

    MOV AX, DATASEG
    MOV DS, AX
    MOV SS, AX
    MOV ES, AX
    MOV FS, AX
    MOV GS, AX
    MOV EBP, 0x7BFF
    MOV ESP, EBP
    
    JMP CODESEG:0x8000

irq_handler:
    pusha
    mov al, 0x49
    mov dx, 0x03F8
    out dx, al
    mov al, 0x20
    mov dx, 0x20
    out dx, al
    mov dx, 0xA0
    out dx, al
    popa
    iret
irq_keyboard:
    pusha
    mov al, 0x32
    mov dx, 0x03F8
    out dx, al
    mov al, 0x20
    mov dx, 0x20
    out dx, al
    mov dx, 0xA0
    out dx, al
    popa
    iret

bits 16
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
    dw 0x0028
    dw 0x8000, 0x0000
    dd 0x00000001
    dd 0x00000000

idt_desc:
    dw idt_end - idt_table - 1
    dd idt_table

idt_table:
    dw irq_handler ;0 - 15 of entry address
    dw 0b0000_0000_0000_1000 ;segment selector
    db 0x00 ;no touch :)
    db 0b1000_1110 ;entry options and interrupt type
    dw 0x0000 ;16 - 31

    dw irq_keyboard ;0 - 15 of entry address
    dw 0b0000_0000_0000_1000 ;segment selector
    db 0x00 ;no touch :)
    db 0b1000_1110 ;entry options and interrupt type
    dw 0x0000 ;16 - 31
%rep 38
    dw irq_handler ;0 - 15 of entry address
    dw 0b0000_0000_0000_1000 ;segment selector
    db 0x00 ;no touch :)
    db 0b1000_1110 ;entry options and interrupt type
    dw 0x0000 ;16 - 31
%endrep
idt_end:

times 510-($-$$) db 0
dw 0AA55h
