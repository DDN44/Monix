#include <stdker.h>
#include <term.h>
#include <irq.h>
#include <mem.h>
#include <ata.h>
#include <serial.h>
#include <fat.h>
#include <gdt.h>
#include <fs.h>

#define IDLE __asm__("nop; nop; nop; nop; nop; nop; nop; nop; nop; nop;")

void kernel_main(void)
{
    gdt_init();
    uint8_t cycles = 0;
    con_init();
    file_init();
    //fat_init();
    irq_init();
    //init_keyboard();
    //file_t testfile;
    //uint8_t testp[3] = "hi";
    //uint8_t testn[] = "fiul";
    //testfile.pointer = &testp;
    //add_file(&testfile, &testn);
    //con_print_hex32(get_filecount());

    con_print("Kernel loaded and running");
    con_newln();

    while(1)
    {
        term_kernel();
    }

    return;
}