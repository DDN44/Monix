#include <fat.h>
#include <mem.h>

uint32_t fat_getroot(fatbpb_t *sp)
{
    return (uint32_t)sp->reservedsectors;
}

void fat_init()
{
    mem_cpyblock();
}