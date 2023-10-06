#include <stdint.h>

#define BLOCKSIZE 512

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