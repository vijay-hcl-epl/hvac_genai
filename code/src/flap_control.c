#include "flap_control.h"
#include "adc_if.h"
#include "motor_driver_if.h"
#include "error_handler.h"
#include "status_output_if.h"
#include "configuration.h"
static uint8_t pos_target = 0;
static uint8_t pos_actual = 0;
static FlapControlState state = FLAP_IDLE;
void FlapControl_Init(void) {
    pos_target = 0;
    pos_actual = AdcIf_GetPosition();
    state = FLAP_IDLE;
}
void FlapControl_MoveTo(uint8_t position) {
    if (position > 5) {
        ErrorHandler_SetError(ERROR_INVALID_CMD);
        state = FLAP_ERROR;
        return;
    }
    pos_target = position;
    FlapControl_Update();
}
void FlapControl_Update(void) {
    pos_actual = AdcIf_GetPosition();
    if (state == FLAP_SAFE || state == FLAP_ERROR) return;
    if (pos_actual == pos_target) {
        state = FLAP_IDLE;
        MotorDriver_Off();
        StatusOutputIf_SetStatus(STATUS_TARGET_REACHED);
    } else {
        state = FLAP_MOVING;
        if (pos_actual < pos_target) {
            MotorDriver_Drive(DIR_INC, 50);
        } else if (pos_actual > pos_target) {
            MotorDriver_Drive(DIR_DEC, 50);
        }
        StatusOutputIf_SetStatus(STATUS_IN_MOTION);
    }
}
uint8_t FlapControl_GetStatus(void) {
    return (uint8_t)state;
}
