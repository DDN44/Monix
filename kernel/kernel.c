#include <stdker.h>
#include <term.h>
#include <irq.h>
#include <mem.h>

void kernel_main(void)
{
    con_init();
    idt_init();

    char str[] = "Kernel loaded and running";
    con_print(&str);
    con_newln();

    while(1)
    {
        term_kernel();
    }

    return;
}