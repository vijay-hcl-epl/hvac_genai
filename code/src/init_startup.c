#include "init_startup.h"
#include "motor_actuation.h"
#include "feedback_acquisition.h"
#include "command_input.h"
#include "status_indication.h"
#include <stdbool.h>

static bool sys_init_done = false;

void system_init(void) {
    // [TBD — Hardware setup: Use only registers, pins, and constants from Infineon TLE9851QXW; not found in PDF extraction]
    // Setup UART, ADC, motor PWM outputs, LED GPIOs
    // All outputs initialized to OFF/state-safe
    // Perform one-time feedback acquisition (potentiometer ADC)
    sys_init_done = true;
    // Synchronize all downstream units if needed
}

bool init_complete(void) {
    return sys_init_done;
}
