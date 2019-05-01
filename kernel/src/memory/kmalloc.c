#include "memory/kmalloc.h"

void * kmalloc(uint32_t size) {
	return memory_manager_alloc(&kernel_memory_manager, size);
}

void kfree(void * pointer) {
	memory_manager_free(&kernel_memory_manager, pointer);
}