#include "memory/manager.h"

memory_manager_state_t kernel_memory_manager;

void memory_manager_init(memory_manager_state_t * state) {
	for (int i = 0; i < MEMORY_MANAGER_HEAP_COUNT; i++) {
		state->heaps[i].start = NULL;
		state->heaps[i].length = 0;
		state->heaps[i].usage = 0;
	}
}

void memory_manager_add_heap(memory_manager_state_t * state, void * start, uint32_t length) {
	// find the next heap slot
	for (int i = 0; i < MEMORY_MANAGER_HEAP_COUNT; i++) {
		if (state->heaps[i].length == 0) {
			// this one is free
			state->heaps[i].start = start;
			state->heaps[i].length = length;
			state->heaps[i].usage = 0;
			state->heaps[i].first_free = start;

			// also set up the first free block
			memory_manager_heap_block_t * first_free = ((memory_manager_heap_block_t *) start);
			first_free->length = length - sizeof(memory_manager_heap_block_t);
			first_free->prev_free = NULL;
			first_free->next_free = NULL;

			break;
		}
	}
}

void * memory_manager_alloc(memory_manager_state_t * state, uint32_t size) {
	// TODO: make this suck less - currently it's very prone to fragmentation
	for (int i = 0; i < MEMORY_MANAGER_HEAP_COUNT; i++) {
		memory_manager_heap_t heap = state->heaps[i];

		if ((heap.length - heap.usage) < size) {
			// not enough free space, get out now
			continue;
		}

		// find the first free space
		memory_manager_heap_block_t * block = (memory_manager_heap_block_t *) heap.first_free;

		while (1) {
			// are you big enough to hold this data and handle the addition of a new block with at least a byte of space?
			if (block->length > size + sizeof(memory_manager_heap_block_t) + 1) {
				// monch

				// create a new block directly after this one
				memory_manager_heap_block_t * new_block = (memory_manager_heap_block_t *) (((uint32_t) block) + sizeof(memory_manager_heap_block_t) + size);
				new_block->length = block->length - size - sizeof(memory_manager_heap_block_t);
				new_block->prev_free = block->prev_free;
				new_block->next_free = block->next_free;
				if (state->heaps[i].first_free == block) {
					// the new first free block has changed
					state->heaps[i].first_free = new_block;
				}
				
				// mark this block as used
				block->length = size;
				block->prev_free = (void *) MEMORY_MANAGER_USED_MAGIC;
				block->next_free = (void *) MEMORY_MANAGER_USED_MAGIC;

				for (uint32_t i = 0; i < size; i++) {
					*(uint8_t *)((void *) block + sizeof(memory_manager_heap_block_t) + i) = 'a';
				}

				// update usage counter
				state->heaps[i].usage += size + sizeof(memory_manager_heap_block_t);

				return (void *) block + sizeof(memory_manager_heap_block_t);
			}

			// is there another block?
			if (block->next_free == NULL) {
				break;
			}

			block = (memory_manager_heap_block_t *) block->next_free;
		}
	}

	return NULL;
}

void memory_manager_free(memory_manager_state_t * state, void * pointer) {
	memory_manager_heap_t * heap = NULL;

	// find the heap used for this pointer
	for (int i = 0; i < MEMORY_MANAGER_HEAP_COUNT; i++) {
		if (state->heaps[i].start <= pointer && (state->heaps[i].start + state->heaps[i].length) > pointer) {
			heap = &state->heaps[i];
			break;
		}
	}

	if (heap) {
		memory_manager_heap_block_t * block = (memory_manager_heap_block_t *) (pointer - sizeof(memory_manager_heap_block_t));
		if (block->prev_free != (void *) MEMORY_MANAGER_USED_MAGIC || block->next_free != (void *) MEMORY_MANAGER_USED_MAGIC) {
			return;
		}

		// update usage counter
		heap->usage -= block->length + sizeof(memory_manager_heap_block_t);

		// convert this block to be free, add it to front of list
		memory_manager_heap_block_t * old_first_free = heap->first_free;
		old_first_free->prev_free = block;
		block->prev_free = NULL;
		block->next_free = old_first_free;
		heap->first_free = block;
	}
}