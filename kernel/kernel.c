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

typedef struct functp{
    void (*sprint)(uint8_t *str);
}__attribute__((packed)) functp_t;

void setup_table()
{
    functp_t *tabl = 0;
    tabl->sprint = &ser_printk;
}

void kernel_main(void *boot_opts)
{
    uint32_t *bootpnt = boot_opts;
    uint32_t bootsize = bootpnt[0];
    for(uint32_t i,x,y=0; i < bootsize; i++)
    {
        x = bootpnt[i];
        y = bootpnt[i + 1];
        if((x == 4) && (y == 16))
        {
            ser_printk("Basic mem High:%d Low:%d\n", bootpnt[i + 2], bootpnt[i +3]);
            con_print_hex32(bootpnt[i + 2]);
            con_print_hex32(bootpnt[i + 3]);
        }
    }
    for(uint32_t i,x,y=0; i < bootsize; i++)
    {
        x = bootpnt[i];
        y = bootpnt[i + 1];
        if(x == 6)
        {
            ser_printk("Ent:%d\n", bootpnt[i + 3]);
        }
    }
    uint32_t cycles = 0;
    //ser_init();
    //ser_print("HELLO");
    mem_init();
    con_init();
    //file_init();
    fat_init();
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

    mbrpart_t *tp = ata_getprimary();

    uint8_t *file = fat_load_file("TEST");

    con_print(file);
    
    ser_printk("fat:%d time:%d\n", fat_get_entry("TEST"), fat_get_entry("TEST")->time);
    ser_printk("esp:%d\n", get_esp());
    
    ser_printk("type:%d lba:%d sects:%d \n", tp->type, tp->lba, tp->sects);

    setup_table();

    functp_t *pnt = 0;

    //pnt->sprint("Hello testing\n");

    file = fat_load_file("EXEC");

    for(uint16_t i=0; i < 40; i++)
    {
        ser_printk("0x%d ", file[i]);
    }

    mem_cpy(file, (uint8_t *)0x01000000, fat_get_entry("EXEC")->size);

    void (*executable)() = 0x01000000;

    executable();

    while(1)
    {
        term_kernel();
    }
    return;
}