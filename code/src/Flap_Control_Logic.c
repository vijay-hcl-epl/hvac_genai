#include "Flap_Control_Logic.h"
#include "Command_Parser.h"
#include "Feedback_Processor.h"
#include "Motor_Driver.h"
#include "LED_Status_Handler.h"

static FlapControl_State_t flap_state = FLAP_IDLE;
static uint8_t current_position = 0xFFu;
static uint8_t target_position = 0xFFu;

void FlapControlLogic_Init(void)
{
    flap_state = FLAP_IDLE;
    current_position = 0xFFu;
    target_position = 0xFFu;
}

void FlapControlLogic_Task(void)
{
    uint8_t feedback_pos;
    uint8_t cmd_pos;

    // Update feedback
    FeedbackProcessor_Update();
    if (!FeedbackProcessor_GetPosition(&feedback_pos)) {
        MotorDriver_Stop();
        flap_state = FLAP_FAULT;
        LEDStatusHandler_IndicateError();
        return;
    }

    current_position = feedback_pos;

    // Accept new command if any
    if (CommandParser_GetLatestCommand(&cmd_pos)) {
        // If command = feedback, do nothing
        if (cmd_pos == feedback_pos) {
            MotorDriver_Stop();
            flap_state = FLAP_TARGET_REACHED;
            LEDStatusHandler_SetGreenLED(feedback_pos);
            CommandParser_ClearCommand();
        } else {
            // Move in direction of command
            if (cmd_pos > feedback_pos) {
                MotorDriver_Drive(MOTOR_DIR_FORWARD, true);
                flap_state = FLAP_MOVING;
            } else {
                MotorDriver_Drive(MOTOR_DIR_REVERSE, true);
                flap_state = FLAP_MOVING;
            }
            target_position = cmd_pos;
        }
    } else if (flap_state == FLAP_MOVING) {
        // Check if at target yet
        if (current_position == target_position) {
            MotorDriver_Stop();
            flap_state = FLAP_TARGET_REACHED;
            LEDStatusHandler_SetGreenLED(current_position);
        } else {
            // Keep moving
            if (target_position > current_position) {
                MotorDriver_Drive(MOTOR_DIR_FORWARD, true);
            } else {
                MotorDriver_Drive(MOTOR_DIR_REVERSE, true);
            }
        }
    }
}

FlapControl_State_t FlapControlLogic_GetState(void)
{
    return flap_state;
}
