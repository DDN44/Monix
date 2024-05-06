#include <stdint.h>

#ifndef _GDT_H_
#define _GDT_H_

typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t flaglimit;
    uint8_t base_high;
}__attribute__((packed)) gdt_entry_t;

typedef struct {
    uint16_t size;
    uint32_t addr;
}__attribute__((packed)) gdt_table_t;

extern void gdt_init();
extern void gdt_load(uint32_t addr);

#endif