/**
 @file flap_control.c
 @brief Implements closed-loop control, direction, and actuator commands.
 @responsibility: Applies logic for position error and motor output (SWE-REQ-005..007, -011) */
#include "flap_control.h"
#include "hw_abstraction.h"
#define POSITION_TOLERANCE (0U)

static bool position_reached = true;
static MotorDirection_t last_direction = MOTOR_DIR_CW;

void FlapControl_Init(void)
{
    HW_Motor_Enable(false);
    position_reached = true;
}

void FlapControl_Process(uint8_t target_position, uint8_t current_position, bool position_valid)
{
    if (!position_valid)
    {
        HW_Motor_Enable(false);
        position_reached = false;
        return;
    }
    if (target_position == current_position)
    {
        HW_Motor_Enable(false);
        position_reached = true;
    }
    else if (target_position > current_position)
    {
        HW_Motor_SetDirection(MOTOR_DIR_CW);
        HW_Motor_Enable(true);
        position_reached = false;
        last_direction = MOTOR_DIR_CW;
    }
    else if (target_position < current_position)
    {
        HW_Motor_SetDirection(MOTOR_DIR_CCW);
        HW_Motor_Enable(true);
        position_reached = false;
        last_direction = MOTOR_DIR_CCW;
    }
    else
    {
        HW_Motor_Enable(false);
        position_reached = true;
    }
}

bool FlapControl_IsPositionReached(void)
{
    return position_reached;
}
