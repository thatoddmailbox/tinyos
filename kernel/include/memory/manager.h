#ifndef _MEMORY_MANAGER_H
#define _MEMORY_MANAGER_H

#include <stddef.h>
#include <stdint.h>

#include "log.h"

#define MEMORY_MANAGER_PHYSICAL_BASE 0x100000
#define MEMORY_MANAGER_USED_MAGIC 0x44455355

#define MEMORY_MANAGER_HEAP_COUNT 2

typedef struct {
	uint32_t length;
	void * prev_free;
	void * next_free;
} __attribute__((packed)) memory_manager_heap_block_t;

typedef struct {
	void * start;
	uint32_t length;
	uint32_t usage;
	void * first_free;
} memory_manager_heap_t;

typedef struct {
	memory_manager_heap_t heaps[MEMORY_MANAGER_HEAP_COUNT];
} memory_manager_state_t;

extern memory_manager_state_t kernel_memory_manager;

void memory_manager_init(memory_manager_state_t * state);
void memory_manager_add_heap(memory_manager_state_t * state, void * start, uint32_t length);
void * memory_manager_alloc(memory_manager_state_t * state, uint32_t size);
void memory_manager_free(memory_manager_state_t * state, void * pointer);

#endif