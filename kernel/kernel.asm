bits 32
extern kernel_main
global kernel_boot

kernel_boot:

    LGDT [tabl_desc]

    CALL kernel_main

    JMP $

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

