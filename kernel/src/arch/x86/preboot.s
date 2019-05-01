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
; the kernel's stack
align 16
stack_bottom:
	resb 16384 ; 16 KB of stack
stack_top:

; the page directory and table used to load the kernel into the higher half of memory
align 4096
boot_page_directory:
	resb 4096
boot_page_table1:
	resb 4096

section .text

global _start:function (_start.end - _start)
global gdt_update
global idt_update
global remove_lower_paging
extern x86_boot

gdt_update:
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

idt_update:
	mov eax, [esp + 4]
	lidt [eax]
	ret

_start:
	cli

	mov esp, (stack_top - 0xC0000000)

	; these registers are parameters to x86_boot()
	; we save them now so that we can use these registers in the following code
	push ebx ; pointer to multiboot info struct
	push eax ; multiboot magic

	; map 0xC0000000 to the first 4MB of memory
	; set up the page table to map to the first 4MB of memory
	mov edi, (boot_page_table1 - 0xC0000000)
	mov esi, 1024
	mov ecx, 0
.table_loop:
	mov edx, ecx
	or edx, ((1 << 1) | (1 << 0)) ; these bits mean writable and present
	mov dword [edi], edx

	add ecx, 4 * 1024 ; each page is 4 KiB
	add edi, 4
	dec esi
	jnz .table_loop

	; now, set the first page directory entry to map to that page table (identity mapping)
	mov dword [boot_page_directory - 0xC0000000 + 0], ((boot_page_table1 - 0xC0000000) + ((1 << 1) | (1 << 0)))

	; and do the same for the 768th entry (0xC0000000)
	mov dword [boot_page_directory - 0xC0000000 + (768 * 4)], ((boot_page_table1 - 0xC0000000) + ((1 << 1) | (1 << 0)))

	; enable paging
	mov eax, boot_page_directory - 0xC0000000
	mov cr3, eax

	mov eax, cr0
	or eax, 0x80000001
	mov cr0, eax

	; fix esp to be the virtual address for the stack
	add esp, 0xC0000000

	; this function call will also yeet eip into the upper half, meaning that we'll be ok when the lower mapping is removed
	; (since x86_boot is located above 0xC0000000)
	; however, we have to do this weird indirect call because other nasm does a relative jump
	mov ecx, x86_boot
	call ecx

.hang:	hlt
	jmp .hang
.end:

remove_lower_paging:
	; we can remove the lower mapping safely now
	mov dword [boot_page_directory - 0xC0000000 + 0], 0

	; boonk cr3 so that the cpu clears its cache
	mov eax, cr3
	mov cr3, eax

	ret