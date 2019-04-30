#include "arch/x86/descriptors.h"

gdt_entry_t gdt_entries[5];
dt_pointer_t gdt_pointer;
idt_entry_t idt_entries[256];
dt_pointer_t idt_pointer;

static void _gdt_set_gate(uint32_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
	gdt_entries[i].base_high = (base >> 24) & 0xFF;
	gdt_entries[i].base_middle = (base >> 16) & 0xFF;
	gdt_entries[i].base_low = base & 0xFFFF;

	gdt_entries[i].flags_limit_high = (flags << 4) | ((limit >> 16) & 0x0F);
	gdt_entries[i].limit_low = limit & 0xFFFF;

	gdt_entries[i].access = access;
}

static void _idt_set_gate(uint32_t i, uint32_t base, uint16_t selector, uint8_t flags) {
	idt_entries[i].base_high = (base >> 16) & 0xFFFF;
	idt_entries[i].base_low = base & 0xFFFF;

	idt_entries[i].selector = selector;
	idt_entries[i].reserved = 0;

	idt_entries[i].flags = flags;
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

	// set up the idt
	idt_pointer.limit = (sizeof(idt_entry_t) * 256) - 1;
	idt_pointer.base = (uint32_t) &idt_entries;

	// 0x8 == code segment

	// builtin cpu interrupts
	_idt_set_gate(0, (uint32_t) isr0, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(1, (uint32_t) isr1, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(2, (uint32_t) isr2, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(3, (uint32_t) isr3, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(4, (uint32_t) isr4, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(5, (uint32_t) isr5, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(6, (uint32_t) isr6, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(7, (uint32_t) isr7, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(8, (uint32_t) isr8, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(9, (uint32_t) isr9, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(10, (uint32_t) isr10, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(11, (uint32_t) isr11, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(12, (uint32_t) isr12, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(13, (uint32_t) isr13, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(14, (uint32_t) isr14, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(15, (uint32_t) isr15, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(16, (uint32_t) isr16, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(17, (uint32_t) isr17, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(18, (uint32_t) isr18, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(19, (uint32_t) isr19, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(20, (uint32_t) isr20, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(21, (uint32_t) isr21, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(22, (uint32_t) isr22, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(23, (uint32_t) isr23, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(24, (uint32_t) isr24, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(25, (uint32_t) isr25, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(26, (uint32_t) isr26, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(27, (uint32_t) isr27, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(28, (uint32_t) isr28, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(29, (uint32_t) isr29, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(30, (uint32_t) isr30, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(31, (uint32_t) isr31, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);

	// irqs
	_idt_set_gate(32, (uint32_t) irq0, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(33, (uint32_t) irq1, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(34, (uint32_t) irq2, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(35, (uint32_t) irq3, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(36, (uint32_t) irq4, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(37, (uint32_t) irq5, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(38, (uint32_t) irq6, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(39, (uint32_t) irq7, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(40, (uint32_t) irq8, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(41, (uint32_t) irq9, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(42, (uint32_t) irq10, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(43, (uint32_t) irq11, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(44, (uint32_t) irq12, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(45, (uint32_t) irq13, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(46, (uint32_t) irq14, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);
	_idt_set_gate(47, (uint32_t) irq15, 0x8, IDT_FLAG_PRESENT | IDT_FLAG_GATE_TYPE_DEFAULT);

	idt_update(&idt_pointer);
}