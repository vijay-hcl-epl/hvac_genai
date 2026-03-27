#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

typedef enum {
    STATE_EID_IDLE,
    STATE_EID_READ,
    STATE_EID_WRITE,
    STATE_EID_ERROR
} EID_StateType;

typedef struct {
    int adcValue;
    int gpioOutputState;
    int inputState;
} ElectricalInterfaceDriver_DataType;

int ElectricalDriver_ReadAdc(void);
int ElectricalDriver_ReadInput(void);
int ElectricalDriver_SetMotor(int state);
void ElectricalDriver_StopMotor(void);
int ElectricalDriver_SetStatusLed(int state);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
