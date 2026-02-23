#include "control_logic.h"
#include "flap_motor_control.h"
#include "status_indication.h"
#include "position_feedback.h"
#include "command_interface.h"
#include "error_handler.h"
static uint8_t system_state = 0; // 0:IDLE 1:CMD_PENDING 2:MOVING 3:ERROR
static uint8_t cmd_pending = 0;
static uint8_t target = 0;
void ControlLogic_Init(void) {
    system_state = 0;
    cmd_pending = 0;
    target = 0;
}
void ControlLogic_OnCommand(uint8_t position) {
    cmd_pending = 1;
    target = position;
    uint8_t curr = GetCurrentFlapPosition();
    if (curr != target) {
        system_state = 2;
        FlapMotorControl_MoveTo(target);
    } else {
        system_state = 0;
        CommandInterface_CommandComplete();
    }
}
void ControlLogic_OnFeedbackUpdate(void) {
    if (system_state == 2) {
        uint8_t curr = GetCurrentFlapPosition();
        if (curr == target) {
            FlapMotorControl_Stop();
            system_state = 0;
            CommandInterface_CommandComplete();
            StatusIndication_SetPositionLED(curr);
        }
    }
}
