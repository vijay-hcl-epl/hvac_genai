#include "state_machine.h"
#include "command_interface.h"
#include "motor_control.h"
#include "adc_feedback.h"
#include "status_indication.h"
#include "error_handler.h"
static FlapState curState = IDLE;
static uint8_t TargetPosition = 0, CurrentPosition = 0;
void IStateMachine_run(void) {
    uint8_t cmd;
    DecodingStatus ds = ICommandDecoder_getCommand(&cmd);
    if (ds == CMD_VALID && curState != MOVING) {
        TargetPosition = cmd;
        curState = MOVING;
        IMotorControl_start(1, 0); // [TBD: direction, pwm from config]
    }
    if (curState == MOVING) {
        int posok = IADCFeedback_getPosition(&CurrentPosition);
        if (posok >= 0 && CurrentPosition == TargetPosition) {
            IMotorControl_stop();
            IStatusUpdate_set(STATUS_POSITION);
            curState = TARGET;
        }
    }
    // Fault/Stop: invoked by error unit, not handled here
}
