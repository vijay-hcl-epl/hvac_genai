#ifndef FLAP_CTRL_H
#define FLAP_CTRL_H
#include <stdint.h>

// Flap control result codes
#define FLAP_CTRL_OK    0
#define FLAP_CTRL_ERROR 1

// Core processing entry point, to exec per loop iteration
int position_controller_execute(void);

#endif // FLAP_CTRL_H
