#include <stdint.h>
#include <gdt.h>

gdt_entry_t zero = {
    0, // limit low
    0, // base low
    0, // base mid
    0, // access
    0, // flag + limit
    0  // base high
};

gdt_entry_t codeseg = {
    0xFFFF, // limit low
    0x0000, // base low
    0x00, // base mid
    0b10011010, // access
    0b11001111, // flag + limit
    0x00  // base high
};

gdt_entry_t dataseg = {
    0xFFFF, // limit low
    0x0000, // base low
    0x00, // base mid
    0b10010010, // access
    0b11001111, // flag + limit
    0x00  // base high
};

void gdt_set_entry(uint32_t num, gdt_entry_t *pnt, gdt_entry_t *ent)
{
    pnt = pnt + (num * sizeof(gdt_entry_t));
    pnt->limit_low = ent->limit_low;
    pnt->base_low = ent->base_low;
    pnt->base_mid = ent->base_mid;
    pnt->access = ent->access;
    pnt->flaglimit = ent->flaglimit;
    pnt->base_high = ent->base_high;
}

gdt_table_t table;

void gdt_init()
{
    gdt_set_entry(0, 0x8800, &zero);
    gdt_set_entry(1, 0x8800, &codeseg);
    gdt_set_entry(2, 0x8800, &dataseg);

    table.size = (8 * 3) - 1;
    table.addr = 0x00008800;

    gdt_load(&table);
}