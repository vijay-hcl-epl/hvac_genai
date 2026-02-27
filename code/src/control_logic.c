#include "control_logic.h"
#include "input_handler.h"
#include "motor_driver.h"
#include "position_feedback.h"
#include "led_status.h"

static uint8_t current_position = 0;
static int8_t target_position = -1;
static bool command_active = false;
static bool movement_in_progress = false;
static CtrlState_t ctrl_state = CTRL_IDLE;

void ControlLogic_Init(uint8_t initial_position)
{
    current_position = initial_position;
    target_position = -1;
    command_active = false;
    movement_in_progress = false;
    ctrl_state = CTRL_IDLE;
}

CtrlStatus_t ControlLogic_SetTargetPosition(int8_t pos)
{
    if (pos < 0 || pos > 5 || movement_in_progress) {
        return CTRL_ERROR_STATE;
    }
    if (pos != current_position) {
        target_position = pos;
        command_active = true;
        ctrl_state = CTRL_MOVING;
        movement_in_progress = true;
        return CTRL_OK;
    } else {
        return CTRL_MOVEMENT_DONE;
    }
}

uint8_t ControlLogic_GetCurrentPosition(void)
{
    return current_position;
}

bool ControlLogic_MovementInProgress(void)
{
    return movement_in_progress;
}

CtrlState_t ControlLogic_GetState(void)
{
    return ctrl_state;
}

void ControlLogic_Task(void)
{
    if (!command_active) {
        if (InputHandler_CommandPending()) {
            int8_t cmd = InputHandler_GetPendingCommand();
            if (cmd >= 0 && cmd <= 5) {
                if (ControlLogic_SetTargetPosition(cmd) == CTRL_OK) {
                    InputHandler_ClearPending();
                }
            } else {
                InputHandler_ClearPending();
            }
        }
        return;
    }
    // Get feedback
    uint8_t feedback = PositionFeedback_GetLogicalPosition();
    if (!PositionFeedback_IsValid()) {
        MotorDriver_Stop();
        ctrl_state = CTRL_IDLE;
        movement_in_progress = false;
        command_active = false;
        return;
    }
    if (feedback != target_position) {
        if (feedback < target_position) {
            MotorDriver_SetDirection(MOTOR_FORWARD);
        } else {
            MotorDriver_SetDirection(MOTOR_REVERSE);
        }
        MotorDriver_Start();
        movement_in_progress = true;
        ctrl_state = CTRL_MOVING;
    } else {
        MotorDriver_Stop();
        ctrl_state = CTRL_IDLE;
        movement_in_progress = false;
        command_active = false;
        current_position = feedback;
        LEDStatus_SetPosition(feedback);
    }
}
