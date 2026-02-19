#include "motor_driver.h"

void motor_driver_init(motor_driver_t *inst)
{
    if (inst == NULL) { return; }
    inst->enabled = false;
    inst->dir = MOTOR_DIR_STOP;
    inst->pwm_duty = 0U;
}

void motor_drive(motor_driver_t *inst, motor_dir_t dir, bool enable, uint8_t pwm)
{
    if (inst == NULL) { return; }
    inst->dir = dir;
    inst->enabled = enable;
    inst->pwm_duty = pwm;
    /* OUTPUT ACTION: set GPIO/PWM as required */
}

void motor_stop(motor_driver_t *inst)
{
    if (inst == NULL) { return; }
    inst->enabled = false;
    inst->dir = MOTOR_DIR_STOP;
    inst->pwm_duty = 0U;
    /* OUTPUT ACTION: All outputs off */
}

bool motor_driver_status(const motor_driver_t *inst)
{
    if (inst == NULL) { return false; }
    return (inst->enabled);
}
