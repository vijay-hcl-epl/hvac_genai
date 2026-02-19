#ifndef INIT_STARTUP_H
#define INIT_STARTUP_H

#include <stdint.h>
#include <stdbool.h>

// Initializes system hardware and peripherals. Returns 0 on success, nonzero on failure.
int init_start(void);

// Signals all units that initialization is completed. Returns 0 on success.
int init_complete_signal(void);

#endif // INIT_STARTUP_H
