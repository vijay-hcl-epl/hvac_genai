#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

typedef enum {
    EID_STATE_IDLE,
    EID_STATE_READ,
    EID_STATE_WRITE,
    EID_STATE_ERROR
} EID_State_t;

typedef struct {
    int adcSampleValue;
    int gpioOutputState;
    int inputState;
} ElectricalInterface_Data_t;

int ElectricalDriver_ReadAdc(void);
int ElectricalDriver_ReadInput(void);
int ElectricalDriver_SetMotor(int state);
int ElectricalDriver_StopMotor(void);
int ElectricalDriver_SetStatusLed(int state);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
