#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

void Hal_Init(void) {
    hal_state = STATE_HAL_IDLE;
    hal_motor_state = 0;
    hal_indicator_state = 0;
}

void Hal_SetMotorDirection(int direction) {
    hal_motor_state = direction;
    ElectricalDriver_SetMotor(direction);
    hal_state = STATE_HAL_MOTOR_ACTIVE;
}

void Hal_StopMotor(void) {
    hal_motor_state = 0;
    ElectricalDriver_StopMotor();
    hal_state = STATE_HAL_IDLE;
}

void Hal_SetLedState(int led_id, int state) {
    hal_indicator_state = state;
    ElectricalDriver_SetStatusLed(led_id, state);
    hal_state = STATE_HAL_LED_ACTIVE;
}
