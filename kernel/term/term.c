#include <stdker.h>

uint8_t promptpresent = 0;

void term_kernel()
{
    if(promptpresent == 0)
    {
        char prompt[] = ">";
        con_print(&prompt);
        promptpresent = 1;
    }
    return;
}