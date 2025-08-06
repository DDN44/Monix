bits 32
global idt_init, irq_handler, irq_handler_spur, irq_key_handler, gdt_load, syscall_handler, intcall
extern poll_keyboard, functp

gdt_load:
    pop ebx
    pop eax
    push ebp
    mov ebp, esp

    lgdt [eax]

    pop ebp
    push eax
    push ebx
    ret

idt_init:
    pop ebx
    pop eax
    push ebp
    mov ebp, esp

    lidt [eax]
    sti

    pop ebp
    push eax
    push ebx
    ret

irq_handler:
    pusha

    mov al, 'T'
    mov dx, 0x03F8
    out dx, al
    mov al, 0xA0
    mov dx, 0x20
    out dx, al
    mov al, 0x20
    mov dx, 0x20
    out dx, al
    
    popa
    iret

irq_handler_spur:
    pusha


    mov dx, 0x60

    in al, dx

    popa
    iret

irq_key_handler:
    pusha

    mov al, 'K'
    mov dx, 0x03F8
    out dx, al

    mov al, 32
    call poll_keyboard
    mov al, 0xA0
    mov dx, 0x20
    out dx, al
    mov al, 0x20
    mov dx, 0x20
    out dx, al

    popa
    iret

current_key:
    db 0x00

section .idt_data
%rep 256
    dw irq_handler ;0 - 15 of entry address
    dw 0b0000_0000_0000_1000 ;segment selector
    db 0x00 ;no touch :)
    db 0b1000_1110 ;entry options and interrupt type
    dw 0x0000 ;16 - 31
%endrep