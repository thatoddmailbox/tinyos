#include "irq/irq.h"

irq_callback irq_callbacks[IRQ_MAX];
void * irq_states[IRQ_MAX];

void irq_init() {
	for (int i = 0; i < IRQ_MAX; i++) {
		irq_callbacks[i] = NULL;
		irq_states[i] = NULL;
	}
}

void irq_handle(uint8_t number) {
	if (irq_callbacks[number] != NULL) {
		irq_callbacks[number](number, irq_states[number]);
	}
}

void irq_set_handler(uint8_t number, void * state, irq_callback callback) {
	irq_callbacks[number] = callback;
	irq_states[number] = state;
}