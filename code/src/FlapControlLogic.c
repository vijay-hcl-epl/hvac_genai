#include "FlapControlLogic.h"
#include "CommandParser.h"
#include "MotorDriver.h"
#include "FeedbackProcessor.h"
#include "LEDStatusHandler.h"
static FlapControlLogic_State_t fcl_state = FLAP_IDLE;
static uint8_t target_pos = 0xFF;

void FlapControlLogic_Init(void) {
    fcl_state = FLAP_IDLE;
    target_pos = 0xFF;
}

void FlapControlLogic_Task(void) {
    CommandParser_Cmd_t cmd = CommandParser_GetLatestCommand();
    FeedbackProcessor_Data_t feedback = FeedbackProcessor_GetPosition();
    static uint8_t last_pos = 0xFF;

    if (!feedback.valid) {
        fcl_state = FLAP_FAULT;
        MotorDriver_Stop();
        LEDStatusHandler_IndicateError();
        return;
    }
    if ((cmd.valid) && (cmd.command != target_pos)) {
        target_pos = cmd.command;
    }
    uint8_t req_pos = target_pos == 0xFF ? feedback.position : target_pos;
    if (req_pos == feedback.position) {
        fcl_state = FLAP_TARGET_REACHED;
        MotorDriver_Stop();
        LEDStatusHandler_SetPositionLED(feedback.position);
        return;
    }
    fcl_state = FLAP_MOVING;
    if (req_pos > feedback.position) {
        MotorDriver_Drive(MOTOR_DIR_FORWARD, 100);
    } else {
        MotorDriver_Drive(MOTOR_DIR_REVERSE, 100);
    }
}
