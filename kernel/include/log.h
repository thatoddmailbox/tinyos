#ifndef _LOG_H
#define _LOG_H

#include <stdarg.h>
#include <stdint.h>

#include "term/term.h"

void kputs(char * message);
void kprintf(const char * format, ...);

#endif