#include <stdint.h>

#define wait() asm("nop; nop; nop; nop; nop");

extern const uint16_t VGA_WIDTH;
extern const uint16_t VGA_COLOR;
extern uint16_t con_x;
extern uint16_t con_y;
extern uint16_t cursor_pos;

void init_keyboard();
uint8_t keyboard_in();
uint8_t poll_keyboard();
void con_init();
void con_newln();
void con_putc(char color, const char chara);
void con_print(char *s);
void con_print_hex32(uint32_t num);
void con_printkernelpanic(uint32_t pannum);

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

void disable_cursor();