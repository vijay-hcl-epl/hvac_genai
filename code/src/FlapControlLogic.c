#include "FlapControlLogic.h"
#include "MotorDriver.h"
#include "PositionFeedback.h"
#include "StatusIndicator.h"
#include "ErrorHandler.h"

static enum FlapPosition current = FLAP_POS_0;
static enum FlapPosition target = FLAP_POS_0;
static enum {
    STATE_IDLE,
    STATE_MOVING,
    STATE_REACHED,
    STATE_ERROR_SAFE
} movementState = STATE_IDLE;

void FlapControlLogic_OnCommand(enum FlapPosition newTarget) {
    if(newTarget == current || newTarget >= FLAP_POS_MAX || newTarget <= FLAP_POS_INVALID) return;
    target = newTarget;
    movementState = STATE_MOVING;
    PositionFeedback_Sample();
}

void FlapControlLogic_OnFeedback(enum FlapPosition position) {
    if(movementState == STATE_MOVING) {
        if(!PositionFeedback_IsValid()) {
            movementState = STATE_ERROR_SAFE;
            MotorDriver_Stop();
            ErrorHandler_Trigger(ERROR_INVALID_FEEDBACK);
            return;
        }
        if(position < target) {
            MotorDriver_SetDirection(MOTOR_DIR_FORWARD);
            MotorDriver_Enable(true);
        } else if(position > target) {
            MotorDriver_SetDirection(MOTOR_DIR_REVERSE);
            MotorDriver_Enable(true);
        } else {
            MotorDriver_Stop();
            current = target;
            movementState = STATE_REACHED;
            StatusIndicator_Update(current, true);
        }
    }
}
