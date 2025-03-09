section .multiboot
header_start:
    dd 0xe85250d6                ; magic number
    dd 0                         ; protected mode code
    dd header_end - header_start ; header length

    ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ;dw 4
    ;dw 0
    ;dd 12
    ;dd 0b10

    ;dw 5
    ;dw 0
    ;dd 20
    ;dd 640
    ;dd 480
    ;dd 24

    ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
header_end:
