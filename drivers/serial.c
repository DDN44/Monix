#include <stdint.h>
#include <stdker.h>
#include <stdarg.h>

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

void ser_printk(uint8_t *str, ...)
{
    va_list va;
    uint8_t x = 255;
    uint16_t count = 0;
    for(uint16_t i=0; x != 0; i++)
    {
        x = str[i];
        if(x == '%')
        {
            count++;
        }
    }
    x = 255;
    va_start(va, count);
    for(uint16_t i=0; x != 0; i++)
    {
        x = str[i];
        if(x == '%')
        {
            switch(str[i + 1])
            {
                case 'd':
                    char buf[20];
                    var_to_str(va_arg(va, uint32_t), buf);
                    ser_print(buf);
                    i++;
                    break;
            }
        } else if(x == '\n'){
            ser_sendbyte(0x3F8, '\n');
        } else {
            ser_sendbyte(0x3F8, x);
        }
    }
    va_end(va);
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