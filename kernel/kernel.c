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

extern uint32_t get_esp();

void kernel_main(void)
{
    uint32_t cycles = 0;
    //ser_init();
    //ser_print("HELLO");
    con_init();
    con_print_hex32(get_esp());
    //file_init();
    //fat_init();
    irq_init();
    init_keyboard();
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