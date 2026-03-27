#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

static HalState hal_state = STATE_HAL_IDLE;

void Hal_SetMotorDirection(int dir) {
    hal_state = STATE_HAL_MOTOR_ACTIVE;
    ElectricalDriver_SetMotor(dir);
    hal_state = STATE_HAL_IDLE;
}

void Hal_StopMotor(void) {
    hal_state = STATE_HAL_MOTOR_ACTIVE;
    ElectricalDriver_StopMotor();
    hal_state = STATE_HAL_IDLE;
}

void Hal_SetLedState(int state) {
    hal_state = STATE_HAL_LED_ACTIVE;
    ElectricalDriver_SetStatusLed(state);
    hal_state = STATE_HAL_IDLE;
}
