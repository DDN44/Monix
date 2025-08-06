#include <fat.h>
#include <mem.h>
#include <stdker.h>
#include <serial.h>
#include <ata.h>
#include <irq.h>

//fat 16 implementation

typedef struct fat_state{
    fatbpb_t *bpbbegin;
    uint16_t *fattable;
    uint32_t partsize; // partition size in lba
    uint32_t fatlba;
    uint16_t fatsize; // fat size in lba
    uint32_t fatsizeb;
    uint16_t clustersize; // cluster size in bytes
    uint32_t clusteraddr;
    uint16_t rootlba;
    void *rootaddr; //
    uint16_t rootsize; // also in lba
    uint16_t rootsizeb; // root size in bytes
    uint32_t clusterbase;
} fat_state_t;

fat_state_t *state1;

const uint32_t fatbase = 0x00100000;

void fat_init_state()
{
    cli();
    mbrpart_t *mbr = ata_getprimary();
    void *read = mem_alloc_heap(512);
    fatbpb_t *bpb = read;
    ata_read(mbr->lba, 1, read);
    state1 = mem_alloc_heap(sizeof(fat_state_t));
    ser_printk("state:%d\n", &state1);

    printk("resrv:%d\n", bpb->reservedsectors);

    state1->bpbbegin = bpb;
    state1->partsize = mbr->sects;
    state1->fatlba = mbr->lba + bpb->reservedsectors;
    state1->fatsize = bpb->sectorsperfat * bpb->fatnum;
    state1->fatsizeb = state1->fatsize * bpb->sectorbytes;
    state1->clustersize = bpb->sectorperclust * bpb->sectorbytes;
    state1->rootlba = bpb->reservedsectors + state1->fatsize + mbr->lba;
    ser_printk("state:%d\n", &state1);
    state1->rootsize = (bpb->rootentries * 32) / bpb->sectorbytes;
    state1->rootsizeb = bpb->rootentries * 32;
    state1->clusterbase = state1->rootlba + state1->rootsize;
    state1->fattable = mem_alloc_heap(state1->fatsizeb);
    ata_read(state1->fatlba, state1->fatsize, state1->fattable);
    uint8_t *root = mem_alloc_heap(512);
    for(uint16_t i=0; i < 512; i++)
    {
        root[i] = 0;
    }
    ata_read(state1->rootlba, 1, root);
    for(uint16_t i=0; i < 512; i++)
    {
        ser_printk("0x%d ", root[i]);
    }
    state1->rootaddr = root;
}

void fat_create_entry()
{

}

uint16_t fat_entry_count()
{
    ser_printk("rootaddr:%d\n", state1->rootaddr);
    fatstd_t *entp = state1->rootaddr;
    uint16_t count;

    for(uint32_t i=0; i < 512; i++)
    {
        if(entp[i].attribute == 0x20) count++;
    }
    return count;
}

uint8_t fatstr[32];

uint8_t *fat_fixstr(uint8_t *str, uint8_t len)
{
    for(uint8_t i=0; i < 32; i++)
    {
        fatstr[i] = 0;
    }

    for(uint16_t i=0; i < len; i++)
    {
        fatstr[i] = str[i];
        if(fatstr[i] == 0x20)
        {
            fatstr[i] = 0;
        }
    }

    return &fatstr;
}

fatstd_t *fat_get_entry(uint8_t *str)
{
    fatstd_t *entp = state1->rootaddr;
    for(uint16_t i=0; i < state1->bpbbegin->rootentries; i++)
    {
        if(strcmp(str, fat_fixstr(&entp[i].name, 11)) == 0)
        {
            return &entp[i];
        }
    }

    return 0;
}

void *fat_load_file(uint8_t *str)
{
    fatstd_t *entry = fat_get_entry(str);
    uint16_t clust = entry->clustlow;
    ser_printk("clust res:%d\n", state1->fattable[clust]);
    uint32_t clustnum = state1->bpbbegin->sectorperclust * (entry->size / state1->bpbbegin->sectorperclust);
    if((entry->size % state1->bpbbegin->sectorperclust != 0) && (entry->size > (state1->bpbbegin->sectorbytes * state1->bpbbegin->sectorperclust))) clustnum += state1->bpbbegin->sectorperclust;
    if(state1->fattable[clust] >= 0xFFF8)
    {
        void *result = mem_alloc_heap(state1->bpbbegin->sectorperclust * state1->bpbbegin->sectorbytes);
        ata_read(state1->clusterbase + ((clust - 2) * state1->bpbbegin->sectorperclust), clustnum, result);
        ser_printk("clust:%d sectper:%d base:%d file:%d\n", clust, state1->bpbbegin->sectorperclust, state1->clusterbase, state1->clusterbase + ((clust - 2) * state1->bpbbegin->sectorperclust));
        return result;
    }

    return 0;
}

void fat_dir_list()
{
    uint16_t count = fat_entry_count();
    fatstd_t *entp = state1->rootaddr;
    for(uint16_t i=0; i < count; i++)
    {
        if(entp[i].attribute != 0)
        {
            con_print(&entp[i].name);
            printk(" Ent:%d, Size:%d\n", i, entp[i].size);
        }
    }
}

void fat_init()
{
    fat_init_state();
    printk("bpbaddr:%d\n", state1->bpbbegin);
    printk("partsize:%d\n", state1->partsize);
    printk("fatlba:%d\n", state1->fatlba);
    printk("fatsize:%d\n", state1->fatsize);
    printk("clustersize:%d\n", state1->clustersize);
    printk("rootlba:%d\n", state1->rootlba);
    printk("rootsize:%d\n", state1->rootsize);
    printk("rootsizeb:%d\n", state1->rootsizeb);

    printk("Fat Entries:%d\n", fat_entry_count());
}