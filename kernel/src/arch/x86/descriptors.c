#include "arch/x86/descriptors.h"

gdt_entry_t gdt_entries[5];
gdt_pointer_t gdt_pointer;

static void _gdt_set_gate(uint32_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
	gdt_entries[i].base_high = (base >> 24) & 0xFF;
	gdt_entries[i].base_middle = (base >> 16) & 0xFF;
	gdt_entries[i].base_low = base & 0xFFFF;

	gdt_entries[i].flags_limit_high = (flags << 4) | ((limit >> 16) & 0x0F);
	gdt_entries[i].limit_low = limit & 0xFFFF;

	gdt_entries[i].access = access;
}

void descriptors_init() {
	// set up the gdt
	gdt_pointer.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_pointer.base = (uint32_t) &gdt_entries;

	_gdt_set_gate(0, 0, 0, 0, 0); // null
	_gdt_set_gate(1, 0, 0xFFFFFFFF, GDT_ACCESS_PRESENT | GDT_ACCESS_NOT_SYSTEM_SEGMENT | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_READ_OR_WRITE, GDT_FLAG_GRANULARITY | GDT_FLAG_SIZE); // code
	_gdt_set_gate(2, 0, 0xFFFFFFFF, GDT_ACCESS_PRESENT | GDT_ACCESS_NOT_SYSTEM_SEGMENT | GDT_ACCESS_READ_OR_WRITE, GDT_FLAG_GRANULARITY | GDT_FLAG_SIZE); // data
	_gdt_set_gate(3, 0, 0xFFFFFFFF, GDT_ACCESS_PRESENT | GDT_ACCESS_PRIVILEGE_RING_3 | GDT_ACCESS_NOT_SYSTEM_SEGMENT | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_READ_OR_WRITE, GDT_FLAG_GRANULARITY | GDT_FLAG_SIZE); // usermode code
	_gdt_set_gate(4, 0, 0xFFFFFFFF, GDT_ACCESS_PRESENT | GDT_ACCESS_PRIVILEGE_RING_3 | GDT_ACCESS_NOT_SYSTEM_SEGMENT | GDT_ACCESS_READ_OR_WRITE, GDT_FLAG_GRANULARITY | GDT_FLAG_SIZE); // usermode data

	gdt_update(&gdt_pointer);
}