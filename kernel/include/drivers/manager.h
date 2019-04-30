#ifndef _DRIVERS_MANAGER_H
#define _DRIVERS_MANAGER_H

#include "log.h"

#define DRIVERS_MAX 10

#define DRIVER_TYPE_CONTROLLER 0
#define DRIVER_TYPE_DEVICE 1

#define BUS_TYPE_ARCH_SPECIFIC 0
#define BUS_TYPE_PS2 1
#define BUS_TYPE_PCI 2
#define BUS_TYPE_USB 3

#define DEVICE_TYPE_TIMER 0
#define DEVICE_TYPE_KEYBOARD 1
#define DEVICE_TYPE_MOUSE 2

typedef uint8_t device_id_t;

typedef struct {
	const char * name;
	uint8_t driver_type; // if it's a controller or a device
	uint8_t device_bus_type; // the bus the device sits on (a usb controller over pci would get BUS_TYPE_PCI here)
	uint8_t device_type; // if it's a device, DEVICE_TYPE_*, if it's a controller, BUS_TYPE_*
	void * state;
	void * impl;
} driver_t;

void drivers_init();
void drivers_add_driver(driver_t * driver);
void drivers_add_all();
void drivers_setup();

#endif