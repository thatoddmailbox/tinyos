#include <stdint.h>

#include "memory/manager.h"

#include "term/term.h"
#include "term/vgaterm.h"

#include "log.h"

void kernel_early() {
	term_init();
	term_set_current(&vgaterm);

	memory_manager_init(&kernel_memory_manager);
}

void kernel_init(const char * command_line) {
	kprintf("Hello, this is a test. Command line: %s\n", command_line);

	void * yay = memory_manager_alloc(&kernel_memory_manager, 4);
	kprintf("Allocated 4 bytes at 0x%x\n", yay);

	void * yay2 = memory_manager_alloc(&kernel_memory_manager, 20);
	kprintf("Allocated 20 bytes at 0x%x\n", yay2);

	void * yay3 = memory_manager_alloc(&kernel_memory_manager, 4);
	kprintf("Allocated 4 bytes at 0x%x\n", yay3);

	khexdump((void *) 0x100000, 64);

	memory_manager_free(&kernel_memory_manager, yay2);
	kprintf("Freed 16 bytes at 0x%x\n", yay2);

	khexdump((void *) 0x100000, 64);

	void * yay4 = memory_manager_alloc(&kernel_memory_manager, 4);
	kprintf("Allocated 4 bytes at 0x%x\n", yay4);

	khexdump((void *) 0x100000, 64);

	kprintf("yay\n");
	kprintf("yay\n");
	kprintf("yay\n");

	while (1) {}
}