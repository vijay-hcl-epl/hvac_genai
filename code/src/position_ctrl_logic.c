#include "position_ctrl_logic.h"
#include "feedback_acq_proc.h"
#include "motor_control.h"

static uint8_t current_position = 0;
static uint8_t target_position = 0;

void PositionCtrl_Update(void) {
    current_position = FeedbackAcq_GetPosition();
    if (current_position == target_position) {
        MotorCtrl_Stop();
    } else if (current_position < target_position) {
        MotorCtrl_Set(1, true); // 1 = forward
    } else if (current_position > target_position) {
        MotorCtrl_Set(0, true); // 0 = reverse
    }
}

uint8_t PositionCtrl_GetStatus(void) {
    return current_position;
}

void PositionCtrl_SetTarget(uint8_t pos) {
    target_position = pos;
}

bool PositionCtrl_TargetReached(void) {
    return current_position == target_position;
}
