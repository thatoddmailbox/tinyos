#include <stdint.h>

#include "term/term.h"
#include "term/vgaterm.h"

void kernel_init(const char * command_line) {
	term_init();
	term_set_current(&vgaterm);
	term_get_current()->puts("Hello");
}