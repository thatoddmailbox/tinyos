#include <stdint.h>

#include "drivers/display/vga.h"

void kernel_init(const char * command_line) {
	vga_init();
	vga_putc(0, 0, 'H');
	vga_putc(1, 0, 'e');
	vga_putc(2, 0, 'l');
	vga_putc(3, 0, 'l');
	vga_putc(4, 0, 'o');
}