org 0x01000000
bits 32

start:
    mov eax, [0]
    mov ebx, text
    push ebx
    call eax
    pop ebx
    
    mov ebx, [4]
    mov eax, 0
    push eax
    call ebx

    jmp $

text:
    db 'hello from exec', 0x00