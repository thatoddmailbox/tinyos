#ifndef _MEMORY_KMALLOC_H
#define _MEMORY_KMALLOC_H

#include <stddef.h>
#include <stdint.h>

#include "memory/manager.h"

void * kmalloc(uint32_t size);
void kfree(void * pointer);

#endif