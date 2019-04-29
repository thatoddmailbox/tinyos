#include <stdint.h>

#include "term/term.h"
#include "term/vgaterm.h"

#include "log.h"

void kernel_init(const char * command_line) {
	term_init();
	term_set_current(&vgaterm);
	kprintf("Hello, this is a test. Command line: %s\n", command_line);
}