#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

void * memcpy(void * dst, const void * src, size_t num);

char * strdup(const char * str);
size_t strlen(const char * str);

#endif