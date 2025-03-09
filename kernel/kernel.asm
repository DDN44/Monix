bits 32
extern kernel_main
global kernel_boot, get_esp

kernel_boot:
    cli

    lgdt [tabl_desc]
    jmp 0x0008:fix_segment
fix_segment:
    mov ax, 0x0010
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    call kernel_main

    jmp $

get_esp:
    mov eax, esp
    ret

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

