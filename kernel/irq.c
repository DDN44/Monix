#include <irq.h>
#include <stdker.h>
#include <mem.h>

void cli()
{
    __asm__("cli");
}

void sti()
{
    __asm__("sti");
}

void idt_assign(uint8_t irq, uint32_t addr, idt_entry_t *pnt)
{
    pnt->addr_low = addr & 0xFFFF;
    pnt->selector = 0x0008;
    pnt->zero = 0x00;
    pnt->type = 0b10001110;
    pnt->addr_hi = (addr >> 16) & 0xFFFF;
}

void irq_init()
{
    static idtr_t idt_desc;
    uint16_t i = 0;
    while(i < 256)
    {
        idt_assign(i, irq_handler, 0x8000 + (i * 8));
        i++;
    }

    idt_assign(0, irq_handler, 0x8000 + (0 * 8));
    idt_assign(0x20, irq_key_handler, 0x8000 + (0x21 * 8));

    idt_desc.addr = 0x8000;
    idt_desc.size = 64 * 8 - 1;

    pic_remap(0x20, 0x28);
    idt_init(&idt_desc);
    con_print("IDT: ");
    con_print_hex32(*(uint32_t *)0x8000);
    con_newln();
}