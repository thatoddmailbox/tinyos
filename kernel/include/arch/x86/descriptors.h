#ifndef _ARCH_X86_DESCRIPTORS_H
#define _ARCH_X86_DESCRIPTORS_H

#include <stddef.h>
#include <stdint.h>

#define GDT_ACCESS_PRESENT 0b10000000
#define GDT_ACCESS_PRIVILEGE_RING_3 0b01100000
#define GDT_ACCESS_PRIVILEGE_RING_2 0b01000000
#define GDT_ACCESS_PRIVILEGE_RING_1 0b00100000
#define GDT_ACCESS_PRIVILEGE_RING_0 0b00000000
#define GDT_ACCESS_NOT_SYSTEM_SEGMENT 0b00010000
#define GDT_ACCESS_EXECUTABLE 0b00001000
#define GDT_ACCESS_DIRECTION_CONFORMING 0b00000100
#define GDT_ACCESS_READ_OR_WRITE 0b00000010
#define GDT_ACCESS_ACCESSED 0b00000001

#define GDT_FLAG_GRANULARITY 0b1000
#define GDT_FLAG_SIZE 0b0100

typedef struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t flags_limit_high;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdt_pointer_t;

void descriptors_init();
extern void gdt_update(gdt_pointer_t * pointer);

#endif