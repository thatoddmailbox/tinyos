#ifndef _DRIVERS_PS2_CONTROLLER_H
#define _DRIVERS_PS2_CONTROLLER_H

#include <stddef.h>

#include "drivers/manager.h"

typedef struct {
	void (*init)(driver_t *);
	void (*transmit)(driver_t *, device_id_t, uint8_t);
} controller_ps2_t;

#endif