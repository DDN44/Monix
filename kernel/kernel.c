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
    //ser_init();
    ////con_print_hex32(*(uint32_t *)0x8000);
    ////con_newln();

    uint8_t str[] = "Kernel loaded and running";
    con_print(&str);
    con_newln();

    while(1)
    {
        term_kernel();
        if(cycles == 0)
        {
            uint8_t poll = poll_keyboard();
            if(poll == 0x02)
            {
                con_print_hex32(poll);
                con_print("pressed 1 " + 0x8E00);
            }
        }
        cycles++;
    }

    return;
}