#include "control_logic.h"
#include "command_handler.h"
#include "position_sensing.h"
#include "motor_driver.h"
#include "state_manager.h"

static uint8_t target_position = 0;
static bool move_complete = true;

void ControlLogic_Init(void) {
    move_complete = true;
    target_position = 0;
}

void ControlLogic_Process(void) {
    if (CommandHandler_IsCommandAvailable() && move_complete) {
        target_position = CommandHandler_GetLastCommand();
        move_complete = false;
    }
    uint8_t curr_pos = PositionSensing_GetPosition();
    bool valid = PositionSensing_IsValid();
    if (!move_complete && valid) {
        if (curr_pos != target_position) {
            if (curr_pos < target_position) {
                MotorDriver_Enable(MOTOR_DIRECTION_FWD);
            } else {
                MotorDriver_Enable(MOTOR_DIRECTION_REV);
            }
        } else {
            MotorDriver_Disable();
            move_complete = true;
            StateManager_OnTargetReached();
        }
    } else if (!valid) {
        MotorDriver_Disable();
        move_complete = true;
        StateManager_OnError();
    }
}

bool ControlLogic_IsMoveComplete(void) {
    return move_complete;
}
