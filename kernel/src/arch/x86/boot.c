#include <stdint.h>

#include "arch/x86/multiboot.h"

#include "init.h"
#include "log.h"

#define MULTIBOOT_MEMORY_TYPE_RAM 1
#define MULTIBOOT_MEMORY_TYPE_ACPI 3
#define MULTIBOOT_MEMORY_TYPE_PRESERVE_ON_HIBERNATE 4
#define MULTIBOOT_MEMORY_TYPE_DEFECTIVE 5

typedef struct multiboot_memory_map {
	uint32_t size;
	uint64_t base_addr;
	uint64_t length;
	uint32_t type;
} __attribute__((packed)) multiboot_memory_map_t;

void x86_boot(unsigned long magic, multiboot_info_t * mb_info) {
	kernel_early();

	kprintf("Multiboot memory map:\n");
	multiboot_memory_map_t * mmap = (multiboot_memory_map_t *) mb_info->mmap_addr;
	while ((uint32_t) mmap < (mb_info->mmap_addr + mb_info->mmap_length))
	{
		uint32_t end = mmap->base_addr + mmap->length;
		kprintf("from 0x%x ", mmap->base_addr);
		kprintf("to 0x%x", end);
		kprintf(" | %d bytes | %d\n", (uint32_t) mmap->length, mmap->type);

		mmap = (multiboot_memory_map_t *) ((uint32_t) mmap + mmap->size + sizeof(uint32_t));
	}

	kernel_init((const char *) mb_info->cmdline);
}