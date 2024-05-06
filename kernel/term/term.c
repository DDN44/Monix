#include <stdker.h>

uint8_t keybuffer[16];
uint8_t bufpos = 0;

uint8_t promptpresent = 0;

void term_kernel()
{
    if(promptpresent == 0)
    {
        char prompt[] = ">";
        con_print(&prompt);
        promptpresent = 1;
    }

    if(keyrel == 1)
    {
        con_putc(VGA_COLOR, lastkey);
        keybuffer[bufpos] = lastkey;
        bufpos++;
    }

    return;
}