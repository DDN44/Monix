#include <stdint.h>

#ifndef _FS_H_
#define _FS_H_

typedef struct {
    uint8_t used;
    uint8_t *name;
    uint16_t id;
    uint16_t permissions;
    uint32_t pointer;
    uint32_t last_file;
    uint32_t next_file;
} file_t;

void file_init();
void add_file(file_t *p, uint8_t *namep);
uint16_t get_filecount();
uint8_t *get_filename(num);

#endif