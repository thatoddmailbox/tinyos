#ifndef _TERM_TERM_H
#define _TERM_TERM_H

#include <stddef.h>

typedef struct {
	void (*init)();
	void (*puts)(char *);
} term_interface_t;

void term_init();
term_interface_t * term_get_current();
term_interface_t * term_set_current(term_interface_t * new_term);

#endif