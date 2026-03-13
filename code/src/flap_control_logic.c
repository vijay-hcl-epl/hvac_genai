#include "flap_control_logic.h"
#include "adc_interface.h"
#include "motor_driver_if.h"
#include "status_output_if.h"
#include "error_handler.h"

static uint8_t pos_target = 0;
static uint8_t pos_actual = 0;
static FlapControlState_t state = FLAP_STATE_IDLE;

void FlapControlLogic_Init(void) {
    pos_target = 0;
    pos_actual = 0;
    state = FLAP_STATE_IDLE;
}

void FlapControlLogic_SetTarget(uint8_t position) {
    if(position <= 5) {
        pos_target = position;
    }
}

uint8_t FlapControlLogic_GetTarget(void) {
    return pos_target;
}

uint8_t FlapControlLogic_GetActual(void) {
    return pos_actual;
}

FlapControlState_t FlapControlLogic_GetState(void) {
    return state;
}

void FlapControlLogic_Process(void) {
    pos_actual = ADCInterface_GetPosition();
    if(pos_actual == 0xFF) {
        state = FLAP_STATE_ERROR;
        StatusOutputIF_Set(STATUS_ERROR);
        ErrorHandler_Set(ERR_ADC_OOR);
        MotorDriverIF_Off();
        return;
    }
    if(state == FLAP_STATE_ERROR) {
        MotorDriverIF_Off();
        return;
    }
    if(pos_actual == pos_target) {
        state = FLAP_STATE_IDLE;
        MotorDriverIF_Off();
        StatusOutputIF_Set(STATUS_OK);
    } else if(pos_actual < pos_target) {
        state = FLAP_STATE_MOVING;
        MotorDriverIF_Drive(MOTOR_DIR_CW, 60);
        StatusOutputIF_Set(STATUS_MOVING);
    } else if(pos_actual > pos_target) {
        state = FLAP_STATE_MOVING;
        MotorDriverIF_Drive(MOTOR_DIR_CCW, 60);
        StatusOutputIF_Set(STATUS_MOVING);
    }
}
