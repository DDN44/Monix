#include <stdint.h>

#ifndef _BRICKFS_H
#define _BRICKFS_H

#define ENTDIR 0x80
#define ENTFILE 0x10

#define MAGIC 0x8FDA27F9

typedef struct
{
    uint32_t magic;
    uint32_t blocknum;
    uint32_t blocksize;
    uint16_t bricksize; // in blocks
    uint32_t alocblk;
    uint32_t alocsize; // in blocks
    uint32_t rootblk;
    uint16_t rootentnum;
}__attribute__((packed)) brickheader_t;

typedef struct
{
    uint8_t type;
    uint8_t name[23];
    uint32_t bricknum;
    uint32_t size;
}__attribute__((packed)) brickent_t;


#endif