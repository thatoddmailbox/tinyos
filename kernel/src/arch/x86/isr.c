#include "arch/x86/isr.h"

const char * exceptions[] = {
	"Divide Error",
	"Debug",
	"NMI",
	"Breakpoint",
	"Overflow",
	"BOUND Range Exceeded",
	"Invalid Opcode",
	"Device Not Available",
	"Double Fault",
	"CoProcessor Segment Overrun",
	"Invalid TSS",
	"Segment Not Present",
	"Stack Segment Fault",
	"General Protection Fault",
	"Page Fault",
	"Reserved",
	"Floating-Point Error",
	"Alignment Check",
	"Machine Check",
	"SIMD Floating-Point Exception",
	"Virtualization Exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

void page_fault(registers_t * regs) {
	uint32_t faulting_address;
	asm volatile("mov %%cr2, %0" : "=r" (faulting_address));

	kprintf("unhandled page fault at 0x%x\n", faulting_address);
	kprintf(":(\n");

	while (1) {}
}

void isr_handler(registers_t regs) {
	if (regs.int_no == 14) {
		page_fault(&regs);
		return;
	}

	kprintf("Unhandled exception (%d) - %s\n", regs.int_no, exceptions[regs.int_no]);

	while (1) {}
}

void irq_handler(registers_t regs) {
	// send eoi signals to pic
	if (regs.int_no >= 40) {
		// slave was involved, send eoi to it too
		pic_slave_eoi();
	}
	pic_master_eoi();

	uint32_t irq_num = regs.int_no - 32;
	if (irq_num == 0) {
		return;
	}

	irq_handle(irq_num);
} 