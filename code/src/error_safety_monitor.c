#include "error_safety_monitor.h"
#include "motor_control_driver.h"
#include "status_indication.h"

static bool error_flag = false;

void error_safety_monitor_init(void) {
    error_flag = false;
}

void error_safety_monitor_set_error(void) {
    error_flag = true;
    // Stop the motor and put system in safe state
    motor_control_driver_disable();
    // Optionally update error LED(s) here
}

void error_safety_monitor_clear_error(void) {
    error_flag = false;
    // Optionally restore normal indication
}

bool error_safety_monitor_is_error(void) {
    return error_flag;
}
