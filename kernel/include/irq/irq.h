#ifndef _IRQ_IRQ_H
#define _IRQ_IRQ_H

#include <stddef.h>
#include <stdint.h>

#define IRQ_MAX 255

typedef void (*irq_callback)(uint8_t, void *);

void irq_init();
void irq_handle(uint8_t number);
void irq_set_handler(uint8_t number, void * state, irq_callback callback);

#endif