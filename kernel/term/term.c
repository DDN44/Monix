#include <stdker.h>

uint8_t keybuffer[16];
uint8_t bufpos = 0;

uint8_t promptpresent = 0;
uint8_t initial = 0;

uint8_t term_cmp(uint8_t *str1, uint8_t *str2)
{
    for(uint16_t i,x = 0; x != 0; i++)
    {
        if((str1[i] ^ str2[i]) != 0)
        {
            return 0;
        }
    }
    return 1;
}

void term_cmd(uint8_t *buf)
{
    if(term_cmp(buf, "fuck"))
    {
        con_print("succ");
    }
}

void term_kernel()
{
    if(initial == 0)
    {
        for(uint8_t i = 0; i < 16; i++)
        {
            keybuffer[i] = 0;
        }
        initial = 1;
    }

    if(promptpresent == 0)
    {
        con_print(">");
        promptpresent = 1;
    }

    if(keyevnt == 1)
    {
        if(lastkey == 0x1C)
        {
            term_cmd(keybuffer);
            con_newln();
            con_print_hex32(bufpos);
            promptpresent = 0;
            bufpos = 0;
        }else{
            con_putc(VGA_COLOR, lastkey);
            keybuffer[bufpos] = lastkey;
            bufpos++;
        }
        keyevnt = 0;
    }

    return;
}