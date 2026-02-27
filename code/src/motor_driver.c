#include "motor_driver.h"
#include "hw_abstraction.h"
#include "config.h"

static bool motor_on = false;
static motor_direction_t last_dir = MOTOR_DIRECTION_FWD;

void MotorDriver_Init(void) {
    HWAbstraction_SetMotorPWM(0);
    motor_on = false;
}

void MotorDriver_Enable(motor_direction_t dir) {
    if (!motor_on || dir != last_dir) {
        HWAbstraction_SetMotorDirection(dir);
        last_dir = dir;
    }
    HWAbstraction_SetMotorPWM(Config_GetDefaultPWMDuty());
    motor_on = true;
}

void MotorDriver_Disable(void) {
    HWAbstraction_SetMotorPWM(0);
    motor_on = false;
}
