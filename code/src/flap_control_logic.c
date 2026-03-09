#include "flap_control_logic.h"
#include "adc_interface.h"
#include "motor_driver_if.h"
#include "error_handler.h"

static uint8_t pos_target = 0;
static uint8_t pos_actual = 0;
static FlapControlState flap_state = FLAP_IDLE;

void FlapControlLogic_Init(void) {
    pos_target = 0;
    pos_actual = 0;
    flap_state = FLAP_IDLE;
}

void FlapControlLogic_MoveTo(uint8_t position) {
    pos_target = position;
}

void FlapControlLogic_Update(void) {
    pos_actual = ADC_Interface_GetPosition();
    if (flap_state == FLAP_ERROR || flap_state == FLAP_SAFE) {
        MotorDriverIF_Off();
        return;
    }
    if (pos_actual < pos_target) {
        MotorDriverIF_Drive(1, 50); // Direction=1, Duty=50%
        flap_state = FLAP_MOVING;
    } else if (pos_actual > pos_target) {
        MotorDriverIF_Drive(0, 50); // Direction=0, Duty=50%
        flap_state = FLAP_MOVING;
    } else {
        MotorDriverIF_Off();
        flap_state = FLAP_IDLE;
    }
    // Error check stub
    if (ErrorHandler_GetError()) {
        flap_state = FLAP_ERROR;
    }
}

FlapControlState FlapControlLogic_GetState(void) {
    return flap_state;
}
