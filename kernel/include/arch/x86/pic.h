#ifndef _ARCH_X86_PIC_H
#define _ARCH_X86_PIC_H

#include "arch/x86/io.h"

#define PIC1			0x20
#define PIC2			0xA0

#define PIC1_COMMAND	PIC1
#define PIC1_DATA		(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA		(PIC2+1)

#define PIC_EOI				0x20

#define PIC_ICW1_ICW4		0x01	/* ICW4 (not) needed */
#define PIC_ICW1_SINGLE		0x02	/* Single (cascade) mode */
#define PIC_ICW1_INTERVAL4	0x04	/* Call address interval 4 (8) */
#define PIC_ICW1_LEVEL		0x08	/* Level triggered (edge) mode */
#define PIC_ICW1_INIT		0x10	/* Initialization - required! */
 
#define PIC_ICW4_8086		0x01	/* 8086/88 (MCS-80/85) mode */
#define PIC_ICW4_AUTO		0x02	/* Auto (normal) EOI */
#define PIC_ICW4_BUF_SLAVE	0x08	/* Buffered mode/slave */
#define PIC_ICW4_BUF_MASTER	0x0C	/* Buffered mode/master */
#define PIC_ICW4_SFNM		0x10	/* Special fully nested (not) */

void pic_init();
void pic_master_eoi();
void pic_slave_eoi();

#endif