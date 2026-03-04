#include "FlapControlLogic.h"
#include "MotorDriver.h"
#include "PositionFeedback.h"
#include <stdint.h>

static int8_t current_position = 0;
static int8_t target_position = 0;

void UpdatePosition(void) {
    current_position = GetCurrentPosition();
}

void DriveFlap(void) {
    UpdatePosition();
    if (current_position < target_position) {
        EnableMotor(1);
    } else if (current_position > target_position) {
        EnableMotor(-1);
    } else {
        DisableMotor();
    }
}
