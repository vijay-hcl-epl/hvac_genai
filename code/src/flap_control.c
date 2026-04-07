#include "flap_control.h"
#include "motor_driver.h"
#include "position_feedback.h"
#include "status_indicator.h"
static FlapState_t current_state = FLAP_IDLE;
static uint8_t target = 0;
void FlapControl_request(uint8_t tgt) {
    target = tgt;
    current_state = FLAP_MOVING;
    uint8_t actual;
    Status_t ok;
    position_feedback_get(&actual, &ok);
    if (ok && actual != target) {
        int8_t direction = (target > actual) ? 1 : -1;
        MotorDriver_start(direction);
        // pseudo loop: in real code use timer/task, here only logic
        do {
            position_feedback_get(&actual, &ok);
        } while (ok && actual != target);
        MotorDriver_stop();
        current_state = FLAP_TARGET_REACHED;
    } else if (!ok) {
        MotorDriver_stop();
        current_state = FLAP_ERROR;
    }
}
void FlapControl_stop(void) {
    MotorDriver_stop();
    current_state = FLAP_IDLE;
}
void flap_control_init(void) {
    current_state = FLAP_IDLE;
}
