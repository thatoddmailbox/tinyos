#ifndef _TERM_VGATERM_H
#define _TERM_VGATERM_H

#include "drivers/display/vga.h"

#include "term/term.h"

void vgaterm_putc(char c);

term_interface_t vgaterm;

#endif