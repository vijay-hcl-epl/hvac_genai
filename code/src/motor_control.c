#include "motor_control.h"
#include "config_calib.h"
#define GPIO_FORWARD 0
#define GPIO_REVERSE 1
static uint8_t motor_state = 0;
static uint8_t direction = 0;
static uint16_t current_pwm = 0;
void start_motor(uint8_t dir, uint16_t pwm) {
    // Apply bounds check
    if (pwm > get_config_param(MAX_PWM_ID)) {
        pwm = get_config_param(MAX_PWM_ID);
    }
    direction = dir;
    current_pwm = pwm;
    // TODO: Set GPIOs for direction, PWM register
    motor_state = 1;
}
void stop_motor(void) {
    // TODO: Set PWM to 0, disable output
    motor_state = 0;
    current_pwm = 0;
}
