/* FlapControlLogic.c - Controls the HVAC flap position logic */
#include "FlapControlLogic.h"
#include "MotorDriver.h"
#include "PositionFeedback.h"

static uint8_t currentPosition = 0;
static uint8_t targetPosition = 0;
static bool holding = true;

void FlapControlLogic_Init(void) {
    currentPosition = PositionFeedback_ReadPosition();
    targetPosition = currentPosition;
    holding = true;
}

void FlapControlLogic_SetTarget(uint8_t targetPos) {
    targetPosition = targetPos;
    holding = false;
}

bool FlapControlLogic_Task(void) {
    currentPosition = PositionFeedback_ReadPosition();
    if (!holding && currentPosition != targetPosition) {
        if (currentPosition < targetPosition) {
            MotorDriver_CmdActuate(MOTOR_DIR_UP);
        } else {
            MotorDriver_CmdActuate(MOTOR_DIR_DOWN);
        }
        return true;
    } else {
        MotorDriver_Stop();
        holding = true;
        return false;
    }
}

uint8_t FlapControlLogic_GetStatus(void) {
    return holding ? currentPosition : 255; // 255 = moving/unknown
}
