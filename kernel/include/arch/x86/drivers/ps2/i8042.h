#ifndef _ARCH_X86_DRIVERS_PS2_I8042_H
#define _ARCH_X86_DRIVERS_PS2_I8042_H

#include <stddef.h>
#include <stdint.h>

#include "arch/x86/io.h"

#include "drivers/ps2/controller.h"

#include "drivers/manager.h"

#include "irq/irq.h"

#include "log.h"

#define I8042_DATA 0x60
#define I8042_STATUS 0x64
#define I8042_COMMAND 0x64

#define I8042_CCB_PORT0_IRQ (1 << 0)
#define I8042_CCB_PORT1_IRQ (1 << 1)
#define I8042_CCB_SYSTEM (1 << 2)
#define I8042_CCB_RESERVED1 (1 << 3)
#define I8042_CCB_PORT0_CLOCK_DISABLED (1 << 4)
#define I8042_CCB_PORT1_CLOCK_DISABLED (1 << 5)
#define I8042_CCB_PORT0_TRANSLATION (1 << 6)
#define I8042_CCB_RESERVED2 (1 << 7)

#define I8042_COMMAND_READ_BYTE_0 0x20
#define I8042_COMMAND_WRITE_BYTE_0 0x60
#define I8042_COMMAND_DISABLE_PORT1 0xA7
#define I8042_COMMAND_ENABLE_PORT1 0xA8
#define I8042_COMMAND_TEST_PORT1 0xA9
#define I8042_COMMAND_TEST 0xAA
#define I8042_COMMAND_TEST_PORT0 0xAB
#define I8042_COMMAND_DUMP_RAM 0xAC
#define I8042_COMMAND_DISABLE_PORT0 0xAD
#define I8042_COMMAND_ENABLE_PORT0 0xAE

#define I8042_IRQ_PORT0 1
#define I8042_IRQ_PORT1 12

#define I8042_STATUS_OUTPUT_BUFFER_FULL (1 << 0)
#define I8042_STATUS_INPUT_BUFFER_FULL (1 << 1)
#define I8042_STATUS_SYSTEM (1 << 2)
#define I8042_STATUS_COMMAND_MODE (1 << 3)
#define I8042_STATUS_RESERVED1 (1 << 4)
#define I8042_STATUS_RESERVED2 (1 << 5)
#define I8042_STATUS_ERROR_TIMEOUT (1 << 6)
#define I8042_STATUS_ERROR_PARITY (1 << 7)

typedef struct {
	uint8_t port_count;
} i8042_state_t;

extern controller_ps2_t i8042_impl;
extern driver_t i8042_driver;

#endif