#include <stdker.h>
#include <term.h>
#include <irq.h>
#include <mem.h>
#include <ata.h>
#include <serial.h>

void kernel_main(void)
{
    con_init();
    irq_init();
    //ser_init();
    ////con_print_hex32(*(uint32_t *)0x8000);
    ////con_newln();

    con_print_hex32(*(uint32_t *)0x00100000);
    con_newln();

    uint8_t str[] = "Kernel loaded and running";
    con_print(&str);
    con_newln();

    while(1)
    {
        term_kernel();
    }

    return;
}