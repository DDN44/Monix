bits 32
global idt_init

idt_init:
    push ebp
    mov ebp, esp

    lidt [idt_desc]
    sti

    pop ebp
    ret

irq_handler:

    mov [0xb8000], word 0x1F32

    cli
    hlt

    iret

idt_desc:
    dw idt_end - idt_table - 1
    dd idt_table

idt_table:
%rep 256
    dw irq_handler ;0 - 15 of entry address
    dw 0b0000_0000_0000_1000 ;segment selector
    db 0x00 ;no touch :)
    db 0b1000_1111 ;entry options and interrupt type
    dw 0x0000 ;16 - 31
%endrep
idt_end: