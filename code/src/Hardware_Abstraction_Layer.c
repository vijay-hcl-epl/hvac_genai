#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

static HardwareAbstractionLayer_DataType halData;

int Hal_SetMotorDirection(int direction) {
    halData.motorState = direction;
    return ElectricalDriver_SetMotor(direction);
}

void Hal_StopMotor(void) {
    halData.motorState = 0;
    ElectricalDriver_StopMotor();
}

int Hal_SetLedState(int state) {
    halData.indicatorState = state;
    return ElectricalDriver_SetStatusLed(state);
}
