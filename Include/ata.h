#include <stdint.h>

void ata_poll();
void ata_sendreq(uint64_t lba, uint16_t sectcount, uint8_t reqtype);
void ata_read(uint64_t lba, uint16_t sectcount, uint8_t *buffer);
void ata_init();