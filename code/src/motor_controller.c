#include "motor_controller.h"
#include "hw_abstraction.h"

static MotorDirection_t last_dir = MOTOR_DIR_STOP;
static bool motor_enabled = false;

void MotorController_Init(void)
{
    last_dir = MOTOR_DIR_STOP;
    motor_enabled = false;
    HW_GPIO_Set(/*Motor_IN1_pin*/ 0, false);
    HW_GPIO_Set(/*Motor_IN2_pin*/ 1, false);
    HW_PWM_Set(0, 0); // 0% duty, disabled
}

void MotorController_Run(MotorDirection_t dir)
{
    if (dir != last_dir || !motor_enabled)
    {
        if (dir == MOTOR_DIR_CW)
        {
            HW_GPIO_Set(0, true);    // Motor_IN1
            HW_GPIO_Set(1, false);   // Motor_IN2
        }
        else if (dir == MOTOR_DIR_CCW)
        {
            HW_GPIO_Set(0, false);   // Motor_IN1
            HW_GPIO_Set(1, true);    // Motor_IN2
        }
        else
        {
            HW_GPIO_Set(0, false);   // Motor_IN1
            HW_GPIO_Set(1, false);   // Motor_IN2
        }
        last_dir = dir;
    }
    if (dir == MOTOR_DIR_STOP)
    {
        HW_PWM_Set(0, 0); // 0% duty, disabled
        motor_enabled = false;
    }
    else
    {
        HW_PWM_Set(0, 128); // Example: 50% duty
        motor_enabled = true;
    }
}

void MotorController_Stop(void)
{
    MotorController_Run(MOTOR_DIR_STOP);
}