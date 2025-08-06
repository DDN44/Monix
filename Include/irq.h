#include <stdint.h>

#ifndef _IRQ_H_
#define _IRQ_H_

typedef struct {
   uint16_t addr_low;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  zero;            // unused, set to 0
   uint8_t  type;            // gate type, dpl, and p fields
   uint16_t addr_hi;         // offset bits 16..31
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t size;
    uint32_t addr;
} __attribute__((packed)) idtr_t;

uint32_t get_idt();
void sti();
void cli();
void idt_assign(uint8_t irq, uint32_t addr, idt_entry_t *pnt);
void irq_cpu_init();
void idt_init(uint32_t desc);
void irq_init();
void intcall();
void syscall_handler();
void irq_handler();
void irq_handler_spur();
void irq_key_handler();
void irq_handler_c();
#endif