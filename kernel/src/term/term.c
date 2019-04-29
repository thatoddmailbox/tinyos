#include "term/term.h"

term_interface_t * current_term = NULL;

void term_init() {
	current_term = NULL;
}

term_interface_t * term_get_current() {
	return current_term;
}

void term_set_current(term_interface_t * new_term) {
	current_term = new_term;
	current_term->init();
}