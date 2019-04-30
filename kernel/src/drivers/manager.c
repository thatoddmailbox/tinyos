#include "drivers/manager.h"

#include "drivers/ps2/controller.h"

driver_t * all_drivers[DRIVERS_MAX];
uint32_t all_drivers_count;
driver_t * enabled_drivers[DRIVERS_MAX];
uint32_t enabled_drivers_count;

void drivers_init() {
	all_drivers_count = 0;
	for (int i = 0; i < DRIVERS_MAX; i++) {
		all_drivers[i] = NULL;
	}

	enabled_drivers_count = 0;
	for (int i = 0; i < DRIVERS_MAX; i++) {
		enabled_drivers[i] = NULL;
	}
}

void drivers_add_driver(driver_t * driver) {
	if (all_drivers_count >= DRIVERS_MAX) {
		return;
	}

	all_drivers[all_drivers_count] = driver;
	all_drivers_count++;
}

void drivers_add_all() {
	// drivers_add_driver()
}

extern void drivers_add_all_arch();

void drivers_setup() {
	drivers_add_all();
	drivers_add_all_arch();

	for (unsigned int i = 0; i < all_drivers_count; i++) {
		driver_t * driver = all_drivers[i];
		if (driver->driver_type == DRIVER_TYPE_CONTROLLER) {
			void * impl = driver->impl;
			if (driver->device_type == BUS_TYPE_PS2) {
				((controller_ps2_t *) impl)->init(driver);
			}
		}
	}
}