#include "motor_ctrl.h"
#include "hal_gpio.h"
#include "hal_pwm.h"

void motor_ctrl_init(void) {
    hal_gpio_set_dir_output(0); // Dummy pin
    hal_gpio_set_dir_output(1); // Dummy pin
    hal_pwm_init();
}

void motor_ctrl_start(uint8_t dir) {
    if (dir == MOTOR_DIR_CW) {
        hal_gpio_write(0, 1); // CW
        hal_gpio_write(1, 0);
    } else {
        hal_gpio_write(0, 0); // CCW
        hal_gpio_write(1, 1);
    }
    hal_pwm_start();
}
void motor_ctrl_stop(void) {
    hal_pwm_stop();
    hal_gpio_write(0, 0);
    hal_gpio_write(1, 0);
}
