#include <stdint.h>

#define wait() asm("nop; nop; nop; nop; nop");

extern uint8_t lastkey;
extern uint8_t keyrel;

extern const uint16_t VGA_WIDTH;
extern uint16_t VGA_COLOR;
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
void io_wait();

void pic_remap(int offset1, int offset2);

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

void disable_cursor();