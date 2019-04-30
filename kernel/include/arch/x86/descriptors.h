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

#define IDT_FLAG_PRESENT 0b10000000
#define IDT_FLAG_PRIVILEGE_RING_3 0b01100000
#define IDT_FLAG_PRIVILEGE_RING_2 0b01000000
#define IDT_FLAG_PRIVILEGE_RING_1 0b00100000
#define IDT_FLAG_PRIVILEGE_RING_0 0b00000000
#define IDT_FLAG_GATE_TYPE_DEFAULT 0b00001110

typedef struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t flags_limit_high;
	uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
	uint16_t base_low;
	uint16_t selector;
	uint8_t reserved;
	uint8_t flags;
	uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) dt_pointer_t;

void descriptors_init();

extern void gdt_update(dt_pointer_t * pointer);
extern void idt_update(dt_pointer_t * pointer);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif