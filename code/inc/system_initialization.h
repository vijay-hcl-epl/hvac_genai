#ifndef SYSTEM_INITIALIZATION_H
#define SYSTEM_INITIALIZATION_H
#include <stdbool.h>
void system_init(void);  // Initializes all units
bool system_is_init_ok(void); // Returns if all drivers/units are initialized
#endif
