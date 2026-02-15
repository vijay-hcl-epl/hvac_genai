#include "motor_ctrl.h"
#include "hal_gpio.h"
#include "hal_pwm.h"

void motor_ctrl_init(void)
{
    hal_gpio_set_dir_output(0U);
    hal_gpio_set_dir_output(1U);
    hal_pwm_init();
}

void motor_ctrl_start(uint8_t dir)
{
    if (dir == MOTOR_DIR_CW) {
        hal_gpio_write(0U, 1U);
        hal_gpio_write(1U, 0U);
    } else {
        hal_gpio_write(0U, 0U);
        hal_gpio_write(1U, 1U);
    }
    hal_pwm_start();
}
void motor_ctrl_stop(void)
{
    hal_pwm_stop();
    hal_gpio_write(0U, 0U);
    hal_gpio_write(1U, 0U);
}
