#ifndef _DRIVERS_DISPLAY_VGA_H
#define _DRIVERS_DISPLAY_VGA_H

#include <stdint.h>

#define VGA_BASE 0xB8000
#define VGA_MODE_WIDTH 80
#define VGA_MODE_HEIGHT 25

void vga_init();
void vga_putc(int x, int y, char c);
void vga_shift_up();

#endif