#ifndef _LOG_H
#define _LOG_H

#define LOG_HEXDUMP_LINE_SIZE 16

#include <stdarg.h>
#include <stdint.h>

#include "term/term.h"

void khexdump(void * data, uint32_t size);
void kputs(char * message);
void kprintf(const char * format, ...);

#endif