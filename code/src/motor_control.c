#include "motor_control.h"
#include "hw_interface.h"

static flap_dir_t current_dir;
static int motor_active = 0;

void motor_control_init(void) {
    current_dir = FLAP_UP;
    motor_active = 0;
}

void motor_run(flap_dir_t dir) {
    // Enforce safe control: never set both directions
    gpio_clear(GPIO_MOTOR_CW);
    gpio_clear(GPIO_MOTOR_CCW);
    if (dir == FLAP_UP) gpio_set(GPIO_MOTOR_CW);
    else gpio_set(GPIO_MOTOR_CCW);
    current_dir = dir;
    motor_active = 1;
}

void motor_stop(void) {
    gpio_clear(GPIO_MOTOR_CW);
    gpio_clear(GPIO_MOTOR_CCW);
    motor_active = 0;
}
