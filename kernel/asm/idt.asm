bits 32
global idt_init, irq_handler, irq_handler_spur, irq_key_handler, gdt_load, syscall_handler, intcall, stub_table
extern poll_keyboard, functp, syscall_handler_c

syscall_handler:
    call syscall_handler_c

    iret

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

extern exception_handler

eipget:
    mov eax, [esp]
    ret

%macro isr_err_stub 1
isr_stub_%+%1:
    call eipget
    push eax
    mov ax, %1
    push ax
    call exception_handler
    pop ax
    iret 
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    call eipget
    push eax
    mov ax, %1
    push ax
    call exception_handler
    pop ax
    iret
%endmacro

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

stub_table:
%assign i 0 
%rep    32 
    dd isr_stub_%+i ; use DQ instead if targeting 64-bit
%assign i i+1 
%endrep

section .idt_data
%rep 256
    dw irq_handler ;0 - 15 of entry address
    dw 0b0000_0000_0000_1000 ;segment selector
    db 0x00 ;no touch :)
    db 0b1000_1110 ;entry options and interrupt type
    dw 0x0000 ;16 - 31
%endrep