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
    pnt->type = 0b10001111;
    pnt->addr_hi = (addr >> 16) & 0xFFFF;
}

idtr_t idt_desc;

static idt_entry_t idt_table[256];
// IDT is copied into address 0x8D00 and loaded

void irq_init()
{
    //mem_cpyblock(0x7C95, 0x0500, 1);
    //uint16_t i = 0;
    //while(i < 64)
    //{
    //    idt_assign(i, irq_handler, &idt_table[i]);
    //    i++;
    //}
    idt_desc.addr = 0x7CB0;
    idt_desc.size = 40 * 8 - 1;

    idt_init(&idt_desc);
    uint8_t elplpl[] = "IDT: ";
    con_print(&elplpl);
    con_print_hex32(*(uint32_t *)0x7CB0);
    con_newln();
}