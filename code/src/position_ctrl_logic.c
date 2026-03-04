#include "position_ctrl_logic.h"
#include "motor_control.h"
#include "feedback_acq_proc.h"
#include "user_cmd_handler.h"

static uint8_t current_position = 0;
static uint8_t target_position = 0;

void PositionCtrl_Update(void) {
    if (UserCmdHandler_CommandInProgress()) {
        target_position = UserCmdHandler_GetTarget();
    }
    current_position = FeedbackAcq_GetPosition();
    int delta = (int)target_position - (int)current_position;
    if (delta == 0) {
        MotorCtrl_Stop();
        return;
    }
    else if (delta > 0) {
        MotorCtrl_Set(1, true); // 1: move forward
    }
    else {
        MotorCtrl_Set(0, true); // 0: move backward
    }
}

uint8_t PositionCtrl_GetStatus(void) {
    return current_position;
}
