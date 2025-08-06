#include <stdint.h>
#ifndef _ATA_H_
#define _ATA_H_

typedef struct mbrpart {
    uint8_t artib;
    uint8_t chs1;
    uint16_t chs2;
    uint8_t type;
    uint8_t chs3;
    uint16_t chs4;
    uint32_t lba;
    uint32_t sects;
}__attribute__((packed)) mbrpart_t;

void ata_poll();
void ata_sendreq(uint64_t lba, uint16_t sectcount, uint8_t reqtype);
void ata_read(uint64_t lba, uint16_t sectcount, uint8_t *buffer);
void ata_init();
mbrpart_t *ata_getprimary();

#endif