#include "Electrical_Interface_Driver.h"

static ElectricalInterface_Data_t eidData;

int ElectricalDriver_ReadAdc(void) {
    // Dummy sample read (simulate ADC hardware)
    eidData.adcSampleValue = 512;
    return eidData.adcSampleValue;
}

int ElectricalDriver_ReadInput(void) {
    // Dummy digital input (simulate input pin)
    eidData.inputState = 0;
    return eidData.inputState;
}

int ElectricalDriver_SetMotor(int state) {
    // Dummy GPIO output (simulate H-bridge control)
    eidData.gpioOutputState = state;
    return 0;
}

int ElectricalDriver_StopMotor(void) {
    eidData.gpioOutputState = 0;
    return 0;
}

int ElectricalDriver_SetStatusLed(int state) {
    // Dummy LED output
    return 0;
}
