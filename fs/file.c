#include <fs.h>
#include <stdint.h>
#include <stdker.h>

file_t flist[64];

uint16_t lastid = 0;

void file_init()
{
    flist[0].used = 1;
}

uint8_t *get_filename(num)
{
    return flist[num].name;
}

void add_file(file_t *p, uint8_t *namep)
{
    file_t *free, *prev;

    for(uint16_t i; i < 64; i++)
    {
        if(i >= 63)
        {
            con_print("ERROR: out of file nodes");
            con_newln();
        }
        if(flist[i].used == 0)
        {
            free = &flist[i];
            prev = &flist[i - 1];
            break;
        }
    }

    free->name = namep;
    free->used = 1;
    free->id = ++lastid;
    free->permissions = p->permissions;
    free->pointer = p->pointer;
    free->last_file = prev;
    free->next_file = 0;
    prev->next_file = free;
}

uint16_t get_filecount()
{
    uint16_t count = 0;
    for(uint16_t i = 1; i < 64; i++)
    {
        if(flist[i].used == 1)
        {
            count++;
        }
    }
    return count;
}