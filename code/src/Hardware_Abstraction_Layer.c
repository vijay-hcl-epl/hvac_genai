#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

static Hal_Data_t halData;

int Hal_SetMotorDirection(int direction) {
    if (direction == 1) {
        halData.motorState = 1;
        return ElectricalDriver_SetMotor(1); // Open
    } else if (direction == -1) {
        halData.motorState = -1;
        return ElectricalDriver_SetMotor(-1); // Close
    }
    return -1;
}

int Hal_StopMotor(void) {
    halData.motorState = 0;
    return ElectricalDriver_StopMotor();
}

int Hal_SetLedState(int state) {
    halData.indicatorState = state;
    return ElectricalDriver_SetStatusLed(state);
}
