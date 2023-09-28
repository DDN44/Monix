#include <stdker.h>
#include <term.h>
#include <irq.h>

void kernel_main(void)
{
    con_init();

    char str[] = "Kernel loaded and running";
    con_print(&str);
    con_newln();

    

    while(1)
    {
        term_kernel();
    }

    return;
}