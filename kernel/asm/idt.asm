bits 32
global idt_init, irq_handler, irq_key_handler
extern poll_keyboard

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

    mov al, 'I'
    mov dx, 0x03F8
    out dx, al
    mov al, 0x20
    mov dx, 0x20
    out dx, al
    
    popa
    iret

irq_key_handler:
    pusha

    call poll_keyboard
    mov dx, 0x03F8
    out dx, al
    mov al, 0x20
    mov dx, 0x20
    out dx, al

    popa
    iret

current_key:
    db 0x00