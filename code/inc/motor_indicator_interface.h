#ifndef MOTOR_INDICATOR_INTERFACE_H
#define MOTOR_INDICATOR_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MOTOR_DIRECTION_NONE = 0,
    MOTOR_DIRECTION_FORWARD = 1,
    MOTOR_DIRECTION_REVERSE = 2
} motor_direction_t;

// Initialize motor & indicator HW
void motor_indicator_interface_init(void);
// Drive motor; enable=0 disables
void motor_drive_request(motor_direction_t dir, bool enable);
// Set LEDs for current position + error
void set_led_state(uint8_t position_index, bool error_flag);

#endif // MOTOR_INDICATOR_INTERFACE_H
