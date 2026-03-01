#include "flap_control.h"
#include "motor_control.h"
#include "feedback_adc.h"
#include "indication_led.h"
static FlapState_t state = FLAP_IDLE;
static uint8_t target_position = 0;
void FlapControl_Init(void) {
    state = FLAP_IDLE;
}
void FlapControl_StartMovement(uint8_t tgt_pos) {
    if ((state == FLAP_IDLE) || (state == FLAP_ERROR)) { target_position = tgt_pos; state = FLAP_MOVING; MotorControl_Start(target_position > Feedback_GetPosition() ? MOTOR_DIR_CW : MOTOR_DIR_CCW); }
}
void FlapControl_StopMovement(void) {
    MotorControl_Stop();
    state = FLAP_IDLE;
}
FlapState_t FlapControl_GetState(void) { return state; }
void FlapControl_PeriodicTask(void) {
    uint8_t current_position = Feedback_GetPosition();
    if (!Feedback_IsValid()) {
        MotorControl_Stop();
        state = FLAP_ERROR;
        IndicationLed_Update(1, 0xFF);
    } else if ((state == FLAP_MOVING) && (current_position == target_position)) {
        MotorControl_Stop();
        state = FLAP_IDLE;
        IndicationLed_Update(1, current_position);
    }
}
