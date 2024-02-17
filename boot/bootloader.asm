org 0x7E00
bits 32

start:
    jmp 0x8E00
end:
    jmp end

; eax is string address
prnt:
    mov ecx, 0
    mov edx, 0
prntloop:
    mov bl, [eax + ecx]
    cmp bl, 0
    jz prntend
    
    mov [0xb8000 + edx], bl
    mov [0xb8000 + edx + 1], byte 0x07

    inc ecx
    inc edx
    inc edx
    
    jmp prntloop
prntend:
    ret

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

string:
    db 'hello world', 0

idt_desc:
    dw idt_end - idt_table - 1
    dd idt_table

; this is to put the idt table at 0x8000 
times 512-($-$$) db 0

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
%rep 254
    dw irq_handler ;0 - 15 of entry address
    dw 0b0000_0000_0000_1000 ;segment selector
    db 0x00 ;no touch :)
    db 0b1000_1110 ;entry options and interrupt type
    dw 0x0000 ;16 - 31
%endrep
idt_end:
    
times 4096-($-$$) db 0