#include "term/vgaterm.h"

int vgaterm_x = 0;
int vgaterm_y = 0;

void vgaterm_init() {
	vgaterm_x = 0;
	vgaterm_y = 0;
}

void vgaterm_putc(char c) {
	if (c == '\n') {
		vgaterm_x = 0;
		vgaterm_y++;
		return;
	}

	if (vgaterm_y >= VGA_MODE_HEIGHT) {
		// scroll everything up
		vga_shift_up();
		vgaterm_y = VGA_MODE_HEIGHT - 1;		
	}

	vga_putc(vgaterm_x, vgaterm_y, c);
	vgaterm_x++;
	if (vgaterm_x >= VGA_MODE_WIDTH) {
		vgaterm_x = 0;
		vgaterm_y++;
	}
}

term_interface_t vgaterm = {
	.init = vgaterm_init,
	.putc = vgaterm_putc
};