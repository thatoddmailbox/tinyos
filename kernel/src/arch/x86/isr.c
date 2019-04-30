#include "arch/x86/isr.h"

void isr_handler(registers_t regs) {
	kprintf("isr_handler(%d)\n", regs.int_no);
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

	kprintf("irq_handler(%d)\n", irq_num);

	// if (interrupt_handlers[regs.int_no] != 0)
	// {
	// 	isr_t handler = interrupt_handlers[regs.int_no];
	// 	handler(regs);
	// }
} 