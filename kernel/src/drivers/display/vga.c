#include "drivers/display/vga.h"

void vga_init() {

}

void vga_putc(int x, int y, char c) {
	int char_index = (y * VGA_MODE_WIDTH) + x;
	((uint16_t *) VGA_BASE)[char_index] = (0b00001111 << 8) | c;
}