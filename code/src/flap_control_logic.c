#include "flap_control_logic.h"
#include "uart_command_handler.h"
#include "position_feedback.h"
#include "motor_control.h"
#include "led_handler.h"

static int current_pos = -1;
static int target_pos = -1;
static bool move_pending = false;
static bool error_state = false;

void FlapControlLogic_Init(void) {
    current_pos = -1;
    target_pos = -1;
    move_pending = false;
    error_state = false;
}

void FlapControlLogic_ExecCycle(void) {
    int cmd;
    if (error_state) return;
    if (UART_CommandHandler_GetValidCommand(&cmd)) {
        if (cmd != current_pos && PositionFeedback_IsPositionValid(cmd)) {
            move_pending = true;
            target_pos = cmd;
        } else {
            // invalid command or already at position
        }
    }
    if (move_pending) {
        int fb_pos = PositionFeedback_GetPosition();
        bool valid = PositionFeedback_IsValid();
        if (!valid) {
            error_state = true;
            move_pending = false;
            MotorControl_Stop();
            LEDHandler_IndicateError();
            return;
        }
        if (fb_pos == target_pos) {
            move_pending = false;
            MotorControl_Stop();
            current_pos = fb_pos;
            LEDHandler_IndicatePosition(current_pos);
        } else {
            MotorControl_MoveTo(current_pos, target_pos);
            // LEDHandler_IndicateMoving(current_pos, target_pos); // Optional
        }
    }
}

bool FlapControlLogic_IsBusy(void) {
    return move_pending;
}

bool FlapControlLogic_HasError(void) {
    return error_state;
}

void FlapControlLogic_Reset(void) {
    error_state = false;
    move_pending = false;
    target_pos = -1;
}
