#include <stdker.h>
#include <term.h>
#include <irq.h>
#include <mem.h>
#include <ata.h>
#include <serial.h>

void kernel_main(void)
{
    uint8_t cycles = 0;
    con_init();
    irq_init();
    init_keyboard();
    

    con_print("Kernel loaded and running");
    con_newln();

    while(1)
    {
        if(keyrel == 0)
        {
            if(lastkey == 0x31)
            {
                
            }
        }
        term_kernel();
    }

    return;
}