#include "arch/x86/pic.h"

void pic_init() {
	// set up master pic
	outb(PIC1_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4); // icw1
	outb(PIC1_DATA, 32); // icw2: offset
	outb(PIC1_DATA, 2 << 1); // icw3: tell master pic there's a slave pic on irq2
	outb(PIC1_DATA, PIC_ICW4_8086); // icw4
	outb(PIC1_DATA, 0); // default to no masking

	// set up slave pic
	outb(PIC2_COMMAND, PIC_ICW1_INIT | PIC_ICW1_ICW4); // icw1
	outb(PIC2_DATA, 40); // icw2: offset
	outb(PIC2_DATA, 2); // icw3: tell slave pic it's on irq2
	outb(PIC2_DATA, PIC_ICW4_8086); // icw4
	outb(PIC2_DATA, 0); // default to no masking
}

void pic_master_eoi() {
	outb(PIC1_COMMAND, PIC_EOI);
}

void pic_slave_eoi() {
	outb(PIC2_COMMAND, PIC_EOI);
}