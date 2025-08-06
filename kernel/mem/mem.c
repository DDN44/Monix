#include <stdint.h>
#include <stdker.h>
#include <serial.h>
#include <mem.h>

#define MEMBASE 0x00110000

#define MEMNODESIZE 0x8192

#define HEAPBASE MEMBASE + MEMNODESIZE

#define BLOCKSIZE 512

uint8_t pagemap[1024];

void mem_init()
{
    for(uint16_t i=0; i < 1024; i++)
    {
        pagemap[i] = 0;
    }

    memnode_t *initp = MEMBASE;
    for(uint32_t i=0; i < 1024; i++)
    {
        initp[i].point = 0;
        initp[i].size = 0;
        initp[i].used = 0;
    }
    initp->point = HEAPBASE;
    initp->size = 4;
    initp->used = 1;
}

void *mem_find_free_page()
{
    for(uint32_t i=0; i < 1024; i++)
    {
        for(uint8_t x=0; x < 8; x++)
        {
            uint8_t temp = pagemap[i];
            temp = temp & (1 << x);
            if(temp == 0)
            {
                return (((i << 8) + x) * 4096) + HEAPBASE;
            }
        }
    }
}

void *dumpoint = HEAPBASE;

void *mem_alloc_dum(uint32_t size, memnode_t *node)
{
    void *temp = dumpoint;
    dumpoint += size;
    return temp;
}

void *mem_alloc_gap(uint32_t size, memnode_t *node)
{
    uint8_t run = 1;
    uint32_t x = 0;
    uint32_t gap = 0;
    void *point = 0;
    while(run)
    {
        if((node[x].used == 0) && (node[x + 1].used == 0))
        {
            point = node[x - 1].point + node[x - 1].size;
            run = 0;
        }
    }
    ser_printk("Gap:%d\n", gap);
    return point;
}

void *mem_alloc_heap(uint32_t size)
{
    memnode_t *nodep = MEMBASE;
    while(nodep->used == 1)
    {
        if(nodep >= HEAPBASE)
        {
            ser_printk("Memory Error: out of heap nodes\n");
            return 0;
        }
        nodep += sizeof(memnode_t);
    }

    nodep->size = size;
    nodep->point = mem_alloc_dum(size, nodep);
    nodep->used = 1;

    ser_printk("Memory allocated:%d\n", size);

    return nodep->point;
}

void mem_cpy(uint8_t *from, uint8_t *to, uint32_t count)
{
    for(uint32_t i=0; i < count; i++)
    {
        to[i] = from[i];
    }
}

void mem_cpyblock(uint8_t *from, uint8_t *to, uint32_t count)
{
    uint16_t i = 0;
    uint16_t iblk = 0;
    while(iblk < count)
    {
        from = from + (BLOCKSIZE * iblk);
        to = to + (BLOCKSIZE * iblk);
        while(i < BLOCKSIZE)
        {
            to[i] = from[i];
            i++;
        }
        iblk++;
    }

    return;
}