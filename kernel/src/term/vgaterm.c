#include "term/vgaterm.h"

int vgaterm_x = 0;
int vgaterm_y = 0;

void vgaterm_init() {
	vgaterm_x = 0;
	vgaterm_y = 0;
}

void vgaterm_puts(char * msg) {
	char * c = msg;
	while (*c) {
		vga_putc(vgaterm_x, vgaterm_y, *c);
		vgaterm_x++;
		if (vgaterm_x >= VGA_MODE_WIDTH) {
			vgaterm_x = 0;
			vgaterm_y++;
		}
		c++;
	}
}

term_interface_t vgaterm = {
	.init = vgaterm_init,
	.puts = vgaterm_puts
};