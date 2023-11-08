bits 32
global idt_init, irq_handler

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
    mov al, 0x49
    mov dx, 0x03F8
    out dx, al
    mov al, 0x20
    mov dx, 0x20
    out dx, al
    popa
    iret
