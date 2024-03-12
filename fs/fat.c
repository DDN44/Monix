#include <fat.h>
#include <mem.h>

//fat 16 implementation

const uint32_t fatbase = 0x00100000;

fatbpb_t *fatbegin = fatbase + 3;

uint16_t clustersize;

uint32_t fat_getroot(fatbpb_t *sp)
{
    return (uint32_t)sp->reservedsectors;
}

void fat_setclustersize()
{

}

void fat_init()
{
    
}