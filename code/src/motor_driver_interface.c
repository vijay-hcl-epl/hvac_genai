#include "motor_driver_interface.h"
#include "configuration_data.h"
#include "error_handling.h"

#include <stdio.h> // For stub/example
static uint8_t pwm_duty = 0;
static motor_dir_t direction = MOTOR_DIR_FORWARD;
static bool motor_enabled = false;

void motor_driver_interface_init(void) {
    motor_enabled = false;
    pwm_duty = 0;
}

void motor_driver_interface_set_motor(motor_dir_t dir, uint8_t duty) {
    direction = dir;
    pwm_duty = duty;
    motor_enabled = true;
    // Simulate HW output
    printf("Motor %s, PWM %u\n", dir == MOTOR_DIR_FORWARD ? "FWD" : "REV", duty);
}

void motor_driver_interface_stop_motor(void) {
    motor_enabled = false;
    pwm_duty = 0;
    printf("Motor STOP\n");
}
