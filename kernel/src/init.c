#include <stdint.h>

#include "drivers/manager.h"

#include "irq/irq.h"

#include "memory/kmalloc.h"
#include "memory/manager.h"

#include "term/term.h"
#include "term/vgaterm.h"

#include "log.h"

void kernel_early() {
	term_init();
	term_set_current(&vgaterm);

	irq_init();

	memory_manager_init(&kernel_memory_manager);
}

void kernel_init(const char * command_line) {
	drivers_init();
	drivers_setup();

	kprintf("Hello, this is a test. Command line: %s\n", command_line);

	void * yay = kmalloc(4);
	kprintf("Allocated 4 bytes at 0x%x\n", yay);

	void * yay2 = kmalloc(20);
	kprintf("Allocated 20 bytes at 0x%x\n", yay2);

	void * yay3 = kmalloc(4);
	kprintf("Allocated 4 bytes at 0x%x\n", yay3);

	// khexdump((void *) 0xC0100000, 64);

	kfree(yay2);
	kprintf("Freed 16 bytes at 0x%x\n", yay2);

	// khexdump((void *) 0xC0100000, 64);

	void * yay4 = kmalloc(4);
	kprintf("Allocated 4 bytes at 0x%x\n", yay4);

	// khexdump((void *) 0xC0100000, 64);

	// *((uint32_t *)(0xC1000ABC)) = 0x0;

	kprintf("yay\n");
	kprintf("yay\n");
	kprintf("yay\n");

	// asm volatile ("int $0x3");

	asm volatile ("sti");

	while (1) {}
}