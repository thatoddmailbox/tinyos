#include <stdint.h>

#include "arch/x86/multiboot.h"
#include "init.h"

void x86_boot(unsigned long magic, multiboot_info_t * mb_info, uint32_t initial_stack) {
	kernel_init((const char *) mb_info->cmdline);
}