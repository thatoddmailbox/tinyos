; constants
MULTIBOOT_MAGIC		equ	0x1BADB002

MULTIBOOT_ALIGN		equ	1 << 0	; align loaded modules on page boundaries
MULTIBOOT_MEMINFO	equ	1 << 1	; request memory map

; field values
MULTIBOOT_FLAGS		equ	(MULTIBOOT_ALIGN | MULTIBOOT_MEMINFO)
MULTIBOOT_CHECKSUM	equ	-(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

; create multiboot header
section .multiboot
align 4
	dd MULTIBOOT_MAGIC
	dd MULTIBOOT_FLAGS
	dd MULTIBOOT_CHECKSUM

section .bss
align 16
stack_bottom:
	resb 16384 ; 16 KB of stack
stack_top:

section .text

global _start:function (_start.end - _start)
global gdt_update
extern x86_boot

gdt_update:
	xchg bx, bx
	mov eax, [esp + 4]
	lgdt [eax]

	jmp 0x08:.update_segments
.update_segments
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	ret

_start:
	mov esp, stack_top
	cli

	; pass some important parameters to the c code
	push ebx ; pointer to multiboot info struct
	push eax ; multiboot magic

	call x86_boot

.hang:	hlt
	jmp .hang
.end: