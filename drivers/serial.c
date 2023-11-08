#include <stdint.h>
#include <stdker.h>

void ser_sendbyte(uint16_t com, uint8_t byte)
{
    outb(com, byte);
}

void ser_print(uint8_t *string)
{
    uint32_t i = 0;
    while(string[i] != 0)
    {
        ser_sendbyte(0x3F8, string[i]);
        i++;
    }
}

//COM1 0x3F8
//+0 Data
//+1 interrupt enable
//+2 interrupt identification
//+3 line control
//+4 modem control
//+5 line status
//+6 modem status
//+7 scratch

uint8_t com_init(uint16_t com)
{
    outb(com + 1, 0x00);
    outb(com + 3, 0x80);
    outb(com + 0, 0x01);
    outb(com + 1, 0x00);
    outb(com + 3, 0x03);
    outb(com + 2, 0xC7);
    outb(com + 4, 0x0B);
    outb(com + 4, 0x1E);
    outb(com + 0, 0xAE);

    //if(inb(com + 0) != 0xAE)
    //{
    //    return 1;
    //}

    outb(com + 4, 0x0F);
    return 0;
}

void ser_init()
{
    com_init(0x3F8);
    //if(com_init(0x3F8))
    //{
    //    uint8_t sererr[] = "Serial port error";
    //    con_print(&sererr);
    //    con_newln();
    //}
}