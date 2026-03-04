#include "FlapControlLogic.h"
#include "MotorDriver.h"
#include "PositionFeedback.h"
#include "StatusIndicator.h"
#include "ErrorHandler.h"
#include <stdint.h>

static uint8_t currentPosition = 0xFF;
static uint8_t targetPosition = 0xFF;
static bool movementActive = false;

void FlapControlLogic_Init(void) {
    currentPosition = 0xFF;
    targetPosition = 0xFF;
    movementActive = false;
}

void FlapControlLogic_SetTargetPosition(uint8_t pos) {
    targetPosition = pos;
    movementActive = true;
    StatusIndicator_SetStatus(STATUS_MOVING);
}

void FlapControlLogic_OnPositionFeedback(uint8_t newPos, bool valid) {
    if (!valid) {
        ErrorHandler_Report(ERROR_ADC_OUT_OF_RANGE);
        MotorDriver_Stop();
        StatusIndicator_SetStatus(STATUS_ERROR);
        movementActive = false;
        return;
    }
    currentPosition = newPos;
    StatusIndicator_SetPosition(currentPosition);
    if (movementActive && targetPosition != 0xFF) {
        if (currentPosition == targetPosition) {
            movementActive = false;
            MotorDriver_Stop();
            StatusIndicator_SetStatus(STATUS_REACHED);
        } else {
            // Move flap
            MotorDriver_SetOutput(true, (targetPosition > currentPosition));
        }
    }
}

void FlapControlLogic_Update(void) {
    // Could be invoked periodically or on event; for DEMO, trigger feedback update
    uint8_t pos;
    bool valid = PositionFeedback_GetPosition(&pos);
    FlapControlLogic_OnPositionFeedback(pos, valid);
}
