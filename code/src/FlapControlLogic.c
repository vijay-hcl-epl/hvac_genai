#include "FlapControlLogic.h"
#include "MotorDriver.h"
#include "PositionFeedback.h"
#include "StatusIndicator.h"
#include "ErrorHandler.h"
static uint8_t current_position = 0;
static uint8_t target_position = 0;
void FlapControlLogic_Init(void)
{
    current_position = PositionFeedback_GetPosition();
    target_position = current_position;
}
void FlapControlLogic_Process(void)
{
    current_position = PositionFeedback_GetPosition();
    if (current_position < 6 && target_position < 6) {
        if (current_position < target_position)
            MotorDriver_SetMove(1);
        else if (current_position > target_position)
            MotorDriver_SetMove(-1);
        else
            MotorDriver_Stop();
        StatusIndicator_SetPositionLed(current_position);
    } else {
        ErrorHandler_Report(5); // Invalid position
    }
}
void FlapControlLogic_SetTarget(uint8_t position)
{
    if (position < 6)
        target_position = position;
    else
        ErrorHandler_Report(6); // Out of range
}
void FlapControlLogic_OnPositionUpdate(uint8_t position)
{
    current_position = position;
}
