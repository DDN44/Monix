org 0x7C00
bits 16

%DEFINE ENDL 0x0D, 0x0A

start:
    JMP main

; ES is the segment register and DI is the index register
; they are added like so:
; 0000 0001 1010 1100      segment
; +    0000 0101 0011 0001 offset 
; 0000 0001 1111 1111 0001 address

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

main:
    ; setup segments
    MOV AX, 0
    MOV DS, AX
    MOV ES, AX

    MOV SS, AX
    MOV SP, 0x7C00
    
    MOV SI, init
    CALL puts

    MOV SI, packet
    MOV AH, 0x42
    MOV DL, 0x80

    PUSH SI

    INT 0x13

    POP SI

    JMP 0x7E00


.halt:
    JMP .halt

init: db 'init... ', ENDL, 0

packet:
    db 16
    db 0
    dw 0x0001
    dw 0x7E00, 0x0000
    dd 0x00000001
    dd 0x00000000

times 510-($-$$) db 0
dw 0AA55h
