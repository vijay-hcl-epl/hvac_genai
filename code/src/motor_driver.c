#include "motor_driver.h"
#include "hw_abstraction.h"

static motor_direction_t last_dir = MOTOR_DIRECTION_CW;
static bool enabled = false;

void motor_driver_init(void)
{
    last_dir = MOTOR_DIRECTION_CW;
    enabled = false;
    hw_pwm_disable();
}

void motor_driver_set_direction(motor_direction_t dir)
{
    last_dir = dir;
    if(dir == MOTOR_DIRECTION_CW)
    {
        hw_gpio_set(MOTOR_DIR_PIN, 1);
    }
    else
    {
        hw_gpio_set(MOTOR_DIR_PIN, 0);
    }
}

void motor_driver_enable(void)
{
    enabled = true;
    hw_pwm_enable();
}

void motor_driver_disable(void)
{
    enabled = false;
    hw_pwm_disable();
}
