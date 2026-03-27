#include "Electrical_Interface_Driver.h"
// Stub hardware simulation variables
static ElectricalInterfaceDriver_DataType eidData;

int ElectricalDriver_ReadAdc(void) {
    // Simulate ADC (potentiometer)
    return eidData.adcValue;
}

int ElectricalDriver_ReadInput(void) {
    // Simulate command input
    return eidData.inputState;
}

int ElectricalDriver_SetMotor(int state) {
    // Simulate motor control via GPIO/PWM
    eidData.gpioOutputState = state;
    return 0;
}

void ElectricalDriver_StopMotor(void) {
    eidData.gpioOutputState = 0;
}

int ElectricalDriver_SetStatusLed(int state) {
    // Simulate LED control
    return 0;
}
