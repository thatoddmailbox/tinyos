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
extern x86_boot
_start:
	mov esp, stack_top
	cli

	call x86_boot

.hang:	hlt
	jmp .hang
.end: