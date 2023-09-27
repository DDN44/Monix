#include <stdint.h>

extern const uint16_t VGA_WIDTH;
extern const uint16_t VGA_COLOR;
extern uint16_t con_x;
extern uint16_t con_y;
extern uint16_t cursor_pos;

void con_init();
void con_newln();
void con_putc(char color, const char chara);
void con_print(char *s);
void con_print_hex32(uint32_t num);

static inline void outb(uint16_t port, uint8_t val);
static inline char inb(uint16_t port);

void disable_cursor();