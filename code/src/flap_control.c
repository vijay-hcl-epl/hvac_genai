#include "flap_control.h"
#include "motor_driver.h"
#include "feedback_processor.h"
#include "indication_handler.h"

static int target_position = 0;
static int actual_position = 0;
static enum { IDLE, MOVING, ERROR, COMPLETE } move_state = IDLE;

int FlapControl_SetTargetPosition(int pos) {
    if (move_state == ERROR) return -1;
    if (pos == actual_position) return 0; // Already at target
    target_position = pos;
    move_state = MOVING;
    return 1;
}

int FlapControl_FeedbackUpdate(int pos, int is_valid) {
    if (!is_valid) {
        MotorDriver_Stop();
        move_state = ERROR;
        IndicationHandler_Update(actual_position, 1);
        return -1;
    }
    actual_position = pos;
    if (move_state == MOVING && actual_position == target_position) {
        MotorDriver_Stop();
        move_state = COMPLETE;
        IndicationHandler_Update(actual_position, 0);
    }
    return 0;
}

int FlapControl_Service(void) {
    int pos = 0;
    int valid = FeedbackProcessor_GetPosition(&pos);
    if (!valid) {
        FlapControl_FeedbackUpdate(pos, 0);
        return -1;
    }
    if (move_state == MOVING) {
        if (actual_position < target_position) {
            MotorDriver_SetState(1, 1); // Enable, direction=1
        } else if (actual_position > target_position) {
            MotorDriver_SetState(1, 0); // Enable, direction=0
        } else {
            MotorDriver_Stop();
            move_state = COMPLETE;
        }
    }
    return 0;
}
