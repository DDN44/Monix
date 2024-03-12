#include <stdint.h>

#ifndef _MEM_H_
#define _MEM_H_

typedef struct{
    uint32_t *point;
    uint8_t used;
    uint32_t size;
} memnode_t;

uint8_t *mem_alloc_heap(uint32_t size);

void mem_cpyblock(uint32_t *from, uint32_t *to, uint32_t count);

#endif