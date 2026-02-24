#include "motor_controller.h"
#include <stdint.h>
#include <stdbool.h>

#define MOTOR_FWD_PIN (1U)
#define MOTOR_REV_PIN (2U)
#define MOTOR_EN_PIN  (3U)

static MotorDirection_t last_direction = MOTOR_DIRECTION_NONE;
static bool motor_active = false;

// Dummy GPIO abstraction for platform independence
static void gpio_write(uint8_t pin, bool value) {
    // Hardware-specific GPIO write function stub
    (void)pin; (void)value;
}

void motor_controller_init(void) {
    last_direction = MOTOR_DIRECTION_NONE;
    motor_active = false;
    gpio_write(MOTOR_FWD_PIN, false);
    gpio_write(MOTOR_REV_PIN, false);
    gpio_write(MOTOR_EN_PIN, false);
}

void set_motor_state(MotorDirection_t direction, bool enable) {
    if (enable && direction == MOTOR_DIRECTION_NONE) {
        // Invalid to enable with no direction
        enable = false;
    }
    // Defensive: never both directions!
    if (direction == MOTOR_DIRECTION_FORWARD) {
        gpio_write(MOTOR_FWD_PIN, enable);
        gpio_write(MOTOR_REV_PIN, false);
    } else if (direction == MOTOR_DIRECTION_REVERSE) {
        gpio_write(MOTOR_FWD_PIN, false);
        gpio_write(MOTOR_REV_PIN, enable);
    } else {
        gpio_write(MOTOR_FWD_PIN, false);
        gpio_write(MOTOR_REV_PIN, false);
    }
    gpio_write(MOTOR_EN_PIN, enable);
    motor_active = enable;
    last_direction = direction;
}
