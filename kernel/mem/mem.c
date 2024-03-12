#include <stdint.h>
#include <stdker.h>
#include <mem.h>

#define MEMBASE 0x00100000

#define MEMNODESIZE 0x4096

#define HEAPBASE MEMBASE + MEMNODESIZE

#define BLOCKSIZE 512

uint8_t *mem_alloc_heap(uint32_t size)
{
    memnode_t *nodep = MEMBASE;
    while(nodep->used == 1)
    {
        if(nodep >= HEAPBASE)
        {
            con_print("Memory Error: out of heap nodes");
            con_newln();
        }
        nodep += sizeof(memnode_t);
    }

}

void mem_cpyblock(uint32_t *from, uint32_t *to, uint32_t count)
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