#include "drivers/display/vga.h"

void vga_init() {

}

void vga_putc(int x, int y, char c) {
	int char_index = (y * VGA_MODE_WIDTH) + x;
	((uint16_t *) VGA_BASE)[char_index] = (0b00001111 << 8) | c;
}

void vga_shift_up() {
	// copy every character a line up
	for (int i = 0; i < VGA_MODE_WIDTH * VGA_MODE_HEIGHT - 1; i++) {
		((uint16_t *) VGA_BASE)[i] = ((uint16_t *) VGA_BASE)[i + VGA_MODE_WIDTH];
	}
}