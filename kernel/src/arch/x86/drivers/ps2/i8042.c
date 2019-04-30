#include "arch/x86/drivers/ps2/i8042.h"

static void _i8042_handle_irq(uint8_t irq, void * irq_state) {
	driver_t * driver = (driver_t *) irq_state;
	// i8042_state_t

	uint8_t port_number = 0;
	if (irq == I8042_IRQ_PORT1) {
		port_number = 1;
	}

	uint8_t data = inb(I8042_DATA);
	kprintf("i8042: 0x%x\n", data);

	// TODO: send the data somewhere
}

void i8042_init(driver_t * driver) {
	kprintf("i8042: init\n");

	// disable both ports
	outb(I8042_COMMAND, I8042_COMMAND_DISABLE_PORT0);
	outb(I8042_COMMAND, I8042_COMMAND_DISABLE_PORT1);

	// flush output buffer
	inb(I8042_DATA);

	uint8_t can_be_dual = 1;
	uint8_t port_count = 1;

	// read current ccb
	outb(I8042_COMMAND, I8042_COMMAND_READ_BYTE_0);
	// TODO: need to wait for the controller before read?
	uint8_t ccb = inb(I8042_DATA);

	// disable irqs and translation
	ccb &= ~(I8042_CCB_PORT0_IRQ | I8042_CCB_PORT1_IRQ | I8042_CCB_PORT0_TRANSLATION);

	// if port1 clock is not disabled, it ignored the port1 disable command -> only one port
	if ((ccb & I8042_CCB_PORT1_CLOCK_DISABLED) == 0) {
		can_be_dual = 0;
	}

	// write new ccb
	outb(I8042_COMMAND, I8042_COMMAND_WRITE_BYTE_0);
	outb(I8042_DATA, ccb);

	// perform self-test
	outb(I8042_COMMAND, I8042_COMMAND_TEST);
	uint8_t response = inb(I8042_DATA);

	if (response != 0x55) {
		kprintf("i8042: self-test failed!");
		return;
	}

	if (can_be_dual == 1) {
		// if we re-enable port1, does it change the ccb?
		outb(I8042_COMMAND, I8042_COMMAND_ENABLE_PORT1);

		outb(I8042_COMMAND, I8042_COMMAND_READ_BYTE_0);
		uint8_t new_ccb = inb(I8042_DATA);

		if ((new_ccb & I8042_CCB_PORT1_CLOCK_DISABLED) == 0) {
			// port1's clock is enabled now, so it worked
			port_count = 2;
		}
	}

	kprintf("i8042: found controller with %d port(s)\n", port_count);

	outb(I8042_COMMAND, I8042_COMMAND_ENABLE_PORT0);

	// read current ccb
	outb(I8042_COMMAND, I8042_COMMAND_READ_BYTE_0);
	ccb = inb(I8042_DATA);

	ccb |= I8042_CCB_PORT0_IRQ;
	if (port_count > 1) {
		ccb |= I8042_CCB_PORT1_IRQ;
	}

	outb(I8042_COMMAND, I8042_COMMAND_WRITE_BYTE_0);
	outb(I8042_DATA, ccb);

	irq_set_handler(I8042_IRQ_PORT0, driver, &_i8042_handle_irq);
	if (port_count > 1) {
		irq_set_handler(I8042_IRQ_PORT1, driver, &_i8042_handle_irq);
	}
}

void i8042_transmit(driver_t * driver, device_id_t id, uint8_t data) {
	
}

controller_ps2_t i8042_impl = {
	.init = &i8042_init,
	.transmit = &i8042_transmit,
};

driver_t i8042_driver = {
	.name = "Intel 8042 PS/2 Controller",
	.driver_type = DRIVER_TYPE_CONTROLLER,
	.device_bus_type = BUS_TYPE_ARCH_SPECIFIC,
	.device_type = BUS_TYPE_PS2,
	.impl = &i8042_impl,
};