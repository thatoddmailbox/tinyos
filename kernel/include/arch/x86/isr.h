#ifndef _ARCH_X86_ISR_H
#define _ARCH_X86_ISR_H

#include <stddef.h>
#include <stdint.h>

#include "arch/x86/pic.h"

#include "irq/irq.h"
#include "log.h"

typedef struct {
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} registers_t;


#endif