#include "arch/x86/drivers/manager.h"

void drivers_add_all_arch() {
	drivers_add_driver(&i8042_driver);
}