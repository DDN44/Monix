#include <stdint.h>

const uint16_t VGA_WIDTH = 160;
uint8_t VGA_COLOR;
uint16_t con_x;
uint16_t con_y;
uint16_t cursor_pos;

void con_init()
{
    con_x = 0;
    con_y = 0;
    VGA_COLOR = 0x0A;
    return;
}

void con_newln()
{
    con_x = 0;
    con_y += 1;
}

void con_putc(char color, const char chara)
{
    cursor_pos = 0;
    volatile char *screen_mem = (volatile char*)0xB8000;

    if(con_x >= VGA_WIDTH)
    {
        con_y++;
        con_x = 0;
    }
    cursor_pos = con_x + (con_y * VGA_WIDTH);
    screen_mem[cursor_pos] = chara;
    screen_mem[cursor_pos + 1] = color;
    con_x += 2;
}

void con_print(char *s)
{
    char *string = s;
    uint16_t i = 0;
    while(string[i] != 0)
    {
        con_putc(VGA_COLOR, string[i]);
        i++;
    }
}

void con_print_hex32(uint32_t num)
{
    char hextable[16] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46};
    
    char numseg8 = (num << 28) >> 28;
    char numseg7 = (num << 24) >> 28;
    char numseg6 = (num << 20) >> 28;
    char numseg5 = (num << 16) >> 28;
    char numseg4 = (num << 12) >> 28;
    char numseg3 = (num << 8) >> 28;
    char numseg2 = (num << 4) >> 28;
    char numseg1 = num >> 28;

    numseg1 = hextable[numseg1];
    numseg2 = hextable[numseg2];
    numseg3 = hextable[numseg3];
    numseg4 = hextable[numseg4];
    numseg5 = hextable[numseg5];
    numseg6 = hextable[numseg6];
    numseg7 = hextable[numseg7];
    numseg8 = hextable[numseg8];

    con_putc(VGA_COLOR, 0x30);
    con_putc(VGA_COLOR, 0x78);

    con_putc(VGA_COLOR, numseg1);
    con_putc(VGA_COLOR, numseg2);
    con_putc(VGA_COLOR, numseg3);
    con_putc(VGA_COLOR, numseg4);
    con_putc(VGA_COLOR, numseg5);
    con_putc(VGA_COLOR, numseg6);
    con_putc(VGA_COLOR, numseg7);
    con_putc(VGA_COLOR, numseg8);

    return;
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) :"memory");
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline char inb(uint16_t port)
{
    char ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}