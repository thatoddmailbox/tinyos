#include <stdint.h>

#include "term/term.h"
#include "term/vgaterm.h"

#include "log.h"

void kernel_early() {
	term_init();
	term_set_current(&vgaterm);
}

void kernel_init(const char * command_line) {
	kprintf("Hello, this is a test. Command line: %s\n", command_line);
}