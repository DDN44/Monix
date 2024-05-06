#include <fat.h>
#include <mem.h>
#include <stdker.h>
#include <ata.h>

//fat 16 implementation

const uint32_t fatbase = 0x00100000;

fatbpb_t *bpbbegin = fatbase + 3;

uint16_t fatsize; // fat size in lba
uint16_t clustersize;
uint32_t clusteraddr;
uint16_t rootlba;
uint32_t rootaddr;
uint16_t rootsize; // also in lba
uint16_t rootsizeb;

void fat_create_entry()
{

}

uint16_t fat_entry_count()
{
    fatstd_t *entp = rootaddr;
    uint16_t count;

    for(uint32_t i; i < bpbbegin->rootentries; i++)
    {
        if(entp->attribute != 0x00) count++;
        entp++;
    }
    return count;
}

void fat_init()
{
    ata_read(0, 1000, 0x00100000);

    fatsize = bpbbegin->fatnum * bpbbegin->sectorsperfat;
    clustersize = bpbbegin->sectorbytes * bpbbegin->sectorperclust;
    rootlba = (bpbbegin->sectorsperfat * bpbbegin->fatnum) + bpbbegin->reservedsectors;
    rootaddr = (rootlba * bpbbegin->sectorbytes) + fatbase;
    rootsize = (bpbbegin->rootentries * 32) / bpbbegin->sectorbytes;
    rootsizeb = rootsize * bpbbegin->sectorbytes;
    clusteraddr = (fatsize + rootsize + bpbbegin->reservedsectors) * bpbbegin->sectorbytes;
    
    ata_read(rootlba, rootsize, rootaddr);

    con_print_hex32(rootlba);

    con_print_hex32(rootsize);

    con_print_hex32(rootaddr);

    con_print_hex32(*(uint32_t *)0x00110800);

    con_print_hex32(fat_entry_count());
}