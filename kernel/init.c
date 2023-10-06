#include <mem.h>

void (*funcpoint)(kernel_entry) = 0xF0000000;

uint8_t kernelmoved = 0;

void kernel_init()
{
    if(kernelmoved == 0)
    {
        mem_cpyblock(0x8000, 0xF0000000, 4);
        kernelmoved = 1;
        (*funcpoint)();
    }
}