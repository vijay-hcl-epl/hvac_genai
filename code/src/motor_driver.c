#include "motor_driver.h"
#include <stdio.h> // For hardware stub functions

static bool motor_enabled = false;
static MotorDirection_t motor_direction = MOTOR_FORWARD;

void MotorDriver_Init(void)
{
    // Initialize GPIO/PWM as per HW
    motor_enabled = false;
    motor_direction = MOTOR_FORWARD;
    // HW_Init_Motor(); // Stub placeholder
}

void MotorDriver_Start(void)
{
    // Set GPIO to enable motor driver
    motor_enabled = true;
    // HW_Enable_Motor(motor_direction); // Stub placeholder
}

void MotorDriver_Stop(void)
{
    // Set GPIO to disable motor driver
    motor_enabled = false;
    // HW_Disable_Motor(); // Stub placeholder
}

void MotorDriver_SetDirection(MotorDirection_t dir)
{
    motor_direction = dir;
    // HW_Set_Motor_Direction(dir); // Stub placeholder
}
