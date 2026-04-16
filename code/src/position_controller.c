#include "position_controller.h"
#include "motor_actuator.h"
#include "feedback_processor.h"
#include "indicator_manager.h"
#include <stdint.h>

static enum { POS_IDLE = 0, POS_MOVING, POS_ERROR } pos_state = POS_IDLE;
static uint8_t current_pos = 0;
static uint8_t target_pos = 0;
static bool cmd_pending = false;

void PositionController_Init(void) {
    pos_state = POS_IDLE;
    current_pos = FeedbackProcessor_GetPosition();
    target_pos = current_pos;
    cmd_pending = false;
    IndicatorManager_Update(current_pos);
    MotorActuator_Stop();
}

// Returns true if accepted/started move request
bool PositionController_RequestMove(uint8_t tgt_position) {
    if (tgt_position > 5 || pos_state == POS_ERROR)
        return false;
    if (tgt_position == current_pos)
        return false;
    target_pos = tgt_position;
    pos_state = POS_MOVING;
    cmd_pending = true;
    return true;
}

void PositionController_MainLoop(void) {
    switch(pos_state) {
    case POS_IDLE:
        // No action
        break;
    case POS_MOVING: {
        uint8_t feedback = FeedbackProcessor_GetPosition();
        if (feedback == 0xFF) {
            pos_state = POS_ERROR;
            MotorActuator_Stop();
            break;
        }        
        if (feedback == target_pos) {
            MotorActuator_Stop();
            current_pos = feedback;
            IndicatorManager_Update(current_pos);
            pos_state = POS_IDLE;
            break;
        }
        if (feedback < target_pos)
            MotorActuator_Set(DIR_CW, true);
        else
            MotorActuator_Set(DIR_CCW, true);
        IndicatorManager_Update(feedback);
        break;
    }
    case POS_ERROR:
        // Latch error, require reset or new command
        MotorActuator_Stop();
        IndicatorManager_Update(0xFF); // Show error (all LEDs off except power)
        break;
    }
}
