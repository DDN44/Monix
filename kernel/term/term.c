#include <stdker.h>
#include <fat.h>

uint8_t keybuffer[16];
uint8_t bufpos = 0;

uint8_t promptpresent = 0;
uint8_t initial = 0;

uint8_t term_cmp(uint8_t *str1, uint8_t *str2)
{
    uint8_t x = 255;
    uint16_t i;
    for(i = 0; x != 0; i++)
    {
        x = str2[i];
        if((str1[i] ^ str2[i]) != 0)
        {
            return 0;
        }
    }
    return 1;
}

void clear_buf(uint8_t *buf, uint32_t size)
{
    for(uint32_t i=0; i < size; i++)
    {
        buf[i] = 0;
    }
}

void term_cmd(uint8_t *buf)
{
    if(strcmp(buf, "dir") == 0)
    {
        con_newln();
        fat_dir_list();
    }
    if(strcmp(buf, "repet") == 0)
    {
        con_newln();
        con_print(reqstr_keyboard());
    }

    clear_buf(keybuffer, 16);
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
        if(lastkey == 0)
        {
            keyevnt = 0;
            return;
        }
        if(lastkey == 0x1C)
        {
            lastkey = 0;
            keyevnt = 0;
            term_cmd(keybuffer);
            con_newln();
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