#include <stdint.h>

void ser_init();
uint8_t com_init(uint16_t com);
void ser_sendbyte(uint16_t com, uint8_t byte);