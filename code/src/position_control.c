#include "position_control.h"
#include "motor_controller.h"
#include <stdint.h>
#include <stdbool.h>

static uint8_t current_position = 0u;
static uint8_t target_position = 0u;
static bool position_valid = false;
static bool actuating = false;

void PositionControl_Init(void)
{
    current_position = 0u;
    target_position = 0u;
    actuating = false;
    position_valid = false;
}

void PositionControl_SetTarget(uint8_t position)
{
    if (!position_valid || (position > 5u))
        return;
    if (position == current_position)
        return;
    target_position = position;
    actuating = true;
    // Actuation request will be handled in PositionControl_Process
}

void PositionControl_UpdateCurrent(uint8_t position, bool valid_feedback)
{
    current_position = position;
    position_valid = valid_feedback;
}

void PositionControl_Process(void)
{
    if (!position_valid)
    {
        actuating = false;
        MotorController_Stop();
        return;
    }
    if (actuating)
    {
        if (current_position < target_position)
        {
            MotorController_Run(MOTOR_DIR_CW);
        }
        else if (current_position > target_position)
        {
            MotorController_Run(MOTOR_DIR_CCW);
        }
        else // reached
        {
            MotorController_Stop();
            actuating = false;
        }
    }
}