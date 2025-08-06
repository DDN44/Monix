org 0x01000000
bits 32

start:
    pusha
    mov eax, [0]
    mov ebx, text
    push ebx
    call eax
    popa
    ret

text:
    db 'hello from exec', 0