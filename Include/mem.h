#include <stdint.h>

#ifndef _MEM_H_
#define _MEM_H_

typedef struct{
    void *point;
    uint8_t used;
    uint32_t size;
} memnode_t;

void *mem_alloc_heap(uint32_t size);
void mem_init();
void mem_cpy(uint8_t *from, uint8_t *to, uint32_t count);
void mem_cpyblock(uint8_t *from, uint8_t *to, uint32_t count);
void *mem_find_free_page();

#endif